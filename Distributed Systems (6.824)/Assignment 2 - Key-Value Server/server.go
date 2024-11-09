package kvsrv

import (
	"log"
	"sync"
)

const Debug = false

func DPrintf(format string, a ...interface{}) (n int, err error) {
	if Debug {
		log.Printf(format, a...)
	}
	return
}

type RequestValue struct {
	RequestID int
	Value     string
}

type KVServer struct {
	mu              sync.Mutex
	data            map[string]string
	lastReturnValue map[int64]RequestValue
}

func (kv *KVServer) Get(args *GetArgs, reply *GetReply) {
	kv.mu.Lock()
	defer kv.mu.Unlock()

	value, exists := kv.data[args.Key]
	if !exists {
		value = ""
	}
	reply.Value = value
}

func (kv *KVServer) Put(args *PutAppendArgs, reply *PutAppendReply) {
	kv.mu.Lock()
	defer kv.mu.Unlock()

	kv.data[args.Key] = args.Value
}

func (kv *KVServer) Append(args *PutAppendArgs, reply *PutAppendReply) {
	kv.mu.Lock()
	defer kv.mu.Unlock()

	if kv.lastReturnValue[args.ClientID].RequestID >= args.RequestID {
		reply.Value = kv.lastReturnValue[args.ClientID].Value
		return
	}

	value, exists := kv.data[args.Key]
	if !exists {
		value = ""
	}
	reply.Value = value

	kv.lastReturnValue[args.ClientID] = RequestValue{args.RequestID, value}
	kv.data[args.Key] += args.Value
}

func StartKVServer() *KVServer {
	kv := new(KVServer)
	kv.data = make(map[string]string)
	kv.lastReturnValue = make(map[int64]RequestValue)
	return kv
}
