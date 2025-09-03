package kvraft

import (
	"6.5840/labgob"
	"6.5840/labrpc"
	"6.5840/raft"
	"bytes"
	"log"
	"sync"
	"sync/atomic"
	"time"
)

const Debug = false

func DPrintf(format string, a ...interface{}) (n int, err error) {
	if Debug {
		log.Printf(format, a...)
	}
	return
}

type Op struct {
	Type      string
	Key       string
	Value     string
	ClientID  int64
	RequestID int
}

type KVServer struct {
	mu      sync.Mutex
	me      int
	rf      *raft.Raft
	applyCh chan raft.ApplyMsg
	dead    int32 // set by Kill()

	maxraftstate int // snapshot if log grows this big
	persister    *raft.Persister
	lastApplied  int

	kvStore      map[string]string
	lastReturned map[int64]int
	waitCh       map[int]chan Op
}

func (kv *KVServer) saveSnapshot(index int) {
	if kv.maxraftstate == -1 {
		return
	}

	w := new(bytes.Buffer)
	e := labgob.NewEncoder(w)
	err := e.Encode(kv.kvStore)
	if err != nil {
		return
	}
	err = e.Encode(kv.lastReturned)
	if err != nil {
		return
	}
	kv.rf.Snapshot(index, w.Bytes())
}

func (kv *KVServer) readSnapshot(snapshot []byte) {
	if snapshot == nil || len(snapshot) < 1 {
		return
	}

	r := bytes.NewBuffer(snapshot)
	d := labgob.NewDecoder(r)
	var kvStore map[string]string
	var lastReturned map[int64]int

	if d.Decode(&kvStore) != nil ||
		d.Decode(&lastReturned) != nil {
		log.Fatal("Error")
	} else {
		kv.kvStore = kvStore
		kv.lastReturned = lastReturned
	}
}

func (kv *KVServer) submitOp(op Op) bool {
	index, term, isLeader := kv.rf.Start(op)
	if !isLeader {
		return false
	}

	ch := kv.getChannel(index)

	select {
	case committedOp := <-ch:
		currentTerm, isStillLeader := kv.rf.GetState()
		if !isStillLeader || term != currentTerm ||
			committedOp.ClientID != op.ClientID ||
			committedOp.RequestID != op.RequestID {
			return false
		}
		return true
	case <-time.After(500 * time.Millisecond):
		return false
	}
}

func (kv *KVServer) Get(args *GetArgs, reply *GetReply) {
	kv.mu.Lock()
	if lastReq, exists := kv.lastReturned[args.ClientID]; exists && lastReq >= args.RequestID {
		reply.Value = kv.kvStore[args.Key]
		kv.mu.Unlock()
		return
	}
	kv.mu.Unlock()

	op := Op{
		Type:      "Get",
		Key:       args.Key,
		ClientID:  args.ClientID,
		RequestID: args.RequestID,
	}

	if !kv.submitOp(op) {
		reply.WrongLeader = true
		return
	}

	kv.mu.Lock()
	reply.Value = kv.kvStore[op.Key]
	kv.mu.Unlock()
}

func (kv *KVServer) Put(args *PutAppendArgs, reply *PutAppendReply) {
	op := Op{
		Type:      "Put",
		Key:       args.Key,
		Value:     args.Value,
		ClientID:  args.ClientID,
		RequestID: args.RequestID,
	}

	if !kv.submitOp(op) {
		reply.WrongLeader = true
	}
}

func (kv *KVServer) Append(args *PutAppendArgs, reply *PutAppendReply) {
	op := Op{
		Type:      "Append",
		Key:       args.Key,
		Value:     args.Value,
		ClientID:  args.ClientID,
		RequestID: args.RequestID,
	}

	if !kv.submitOp(op) {
		reply.WrongLeader = true
	}
}

func (kv *KVServer) getChannel(index int) chan Op {
	kv.mu.Lock()
	defer kv.mu.Unlock()

	ch, exists := kv.waitCh[index]
	if !exists {
		ch = make(chan Op, 1)
		kv.waitCh[index] = ch
	}
	return ch
}

func (kv *KVServer) applier() {
	for !kv.killed() {
		msg := <-kv.applyCh
		if msg.SnapshotValid {
			kv.mu.Lock()
			if msg.SnapshotIndex > kv.lastApplied {
				kv.readSnapshot(msg.Snapshot)
				kv.lastApplied = msg.SnapshotIndex
			}
			kv.mu.Unlock()
		} else if msg.CommandValid {
			kv.mu.Lock()
			if msg.CommandIndex > kv.lastApplied {
				op := msg.Command.(Op)
				lastReq, exists := kv.lastReturned[op.ClientID]
				if !exists || lastReq < op.RequestID {
					if op.Type == "Put" {
						kv.kvStore[op.Key] = op.Value
					} else if op.Type == "Append" {
						kv.kvStore[op.Key] += op.Value
					}
					kv.lastReturned[op.ClientID] = op.RequestID
				}
				ch, ok := kv.waitCh[msg.CommandIndex]
				if ok {
					ch <- op
					delete(kv.waitCh, msg.CommandIndex)
				}
				kv.lastApplied = msg.CommandIndex
				if kv.maxraftstate != -1 && kv.persister.RaftStateSize() >= kv.maxraftstate {
					kv.saveSnapshot(msg.CommandIndex)
				}
			}
			kv.mu.Unlock()
		}
	}
}

// the tester calls Kill() when a KVServer instance won't
// be needed again. for your convenience, we supply
// code to set rf.dead (without needing a lock),
// and a killed() method to test rf.dead in
// long-running loops. you can also add your own
// code to Kill(). you're not required to do anything
// about this, but it may be convenient (for example)
// to suppress debug output from a Kill()ed instance.
func (kv *KVServer) Kill() {
	atomic.StoreInt32(&kv.dead, 1)
	kv.rf.Kill()
	// Your code here, if desired.
}

func (kv *KVServer) killed() bool {
	z := atomic.LoadInt32(&kv.dead)
	return z == 1
}

// servers[] contains the ports of the set of
// servers that will cooperate via Raft to
// form the fault-tolerant key/value service.
// me is the index of the current server in servers[].
// the k/v server should store snapshots through the underlying Raft
// implementation, which should call persister.SaveStateAndSnapshot() to
// atomically save the Raft state along with the snapshot.
// the k/v server should snapshot when Raft's saved state exceeds maxraftstate bytes,
// in order to allow Raft to garbage-collect its log. if maxraftstate is -1,
// you don't need to snapshot.
// StartKVServer() must return quickly, so it should start goroutines
// for any long-running work.
func StartKVServer(servers []*labrpc.ClientEnd, me int, persister *raft.Persister, maxraftstate int) *KVServer {
	// call labgob.Register on structures you want
	// Go's RPC library to marshall/unmarshall.
	labgob.Register(Op{})

	kv := new(KVServer)
	kv.me = me
	kv.maxraftstate = maxraftstate

	kv.kvStore = make(map[string]string)
	kv.lastReturned = make(map[int64]int)
	kv.waitCh = make(map[int]chan Op)

	kv.applyCh = make(chan raft.ApplyMsg)
	kv.rf = raft.Make(servers, me, persister, kv.applyCh)

	kv.persister = persister
	kv.readSnapshot(persister.ReadSnapshot())

	go kv.applier()
	return kv
}
