package kvraft

const (
	OK             = "OK"
	ErrNoKey       = "ErrNoKey"
	ErrWrongLeader = "ErrWrongLeader"
)

type Err string

// Put or Append
type PutAppendArgs struct {
	Key       string
	Value     string
	Op        string
	ClientID  int64
	RequestID int
}

type PutAppendReply struct {
	Err         Err
	WrongLeader bool
}

type GetArgs struct {
	Key       string
	ClientID  int64
	RequestID int
}

type GetReply struct {
	Err         Err
	Value       string
	WrongLeader bool
}
