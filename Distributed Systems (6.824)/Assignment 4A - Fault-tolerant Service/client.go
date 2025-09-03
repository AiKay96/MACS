package kvraft

import (
	"6.5840/labrpc"
	"time"
)
import "crypto/rand"
import "math/big"

type Clerk struct {
	servers   []*labrpc.ClientEnd
	clientID  int64
	requestID int
	leaderID  int
}

func nrand() int64 {
	max := big.NewInt(int64(1) << 62)
	bigx, _ := rand.Int(rand.Reader, max)
	x := bigx.Int64()
	return x
}

func MakeClerk(servers []*labrpc.ClientEnd) *Clerk {
	ck := new(Clerk)
	ck.servers = servers
	ck.clientID = nrand()
	ck.requestID = 0
	ck.leaderID = 0
	return ck
}

// fetch the current value for a key.
// returns "" if the key does not exist.
// keeps trying forever in the face of all other errors.
//
// you can send an RPC with code like this:
// ok := ck.server.Call("KVServer.Get", &args, &reply)
//
// the types of args and reply (including whether they are pointers)
// must match the declared types of the RPC handler function's
// arguments. and reply must be passed as a pointer.
func (ck *Clerk) Get(key string) string {
	ck.requestID++
	args := GetArgs{
		Key:       key,
		ClientID:  ck.clientID,
		RequestID: ck.requestID,
	}

	for {
		reply := GetReply{}
		ok := ck.servers[ck.leaderID].Call("KVServer.Get", &args, &reply)

		if ok && !reply.WrongLeader {
			return reply.Value
		}

		ck.leaderID++
		ck.leaderID %= len(ck.servers)
		time.Sleep(100 * time.Millisecond)
	}
}

// shared by Put and Append.
//
// you can send an RPC with code like this:
// ok := ck.server.Call("KVServer."+op, &args, &reply)
//
// the types of args and reply (including whether they are pointers)
// must match the declared types of the RPC handler function's
// arguments. and reply must be passed as a pointer.
func (ck *Clerk) PutAppend(key string, value string, op string) {
	ck.requestID++
	args := PutAppendArgs{
		Key:       key,
		Value:     value,
		Op:        op,
		ClientID:  ck.clientID,
		RequestID: ck.requestID,
	}

	for {
		reply := PutAppendReply{}
		ok := ck.servers[ck.leaderID].Call("KVServer."+op, &args, &reply)

		if ok && !reply.WrongLeader {
			return
		}

		ck.leaderID++
		ck.leaderID %= len(ck.servers)
		time.Sleep(100 * time.Millisecond)
	}
}

func (ck *Clerk) Put(key string, value string) {
	ck.PutAppend(key, value, "Put")
}

// Append value to key's value and return that value
func (ck *Clerk) Append(key string, value string) {
	ck.PutAppend(key, value, "Append")
}
