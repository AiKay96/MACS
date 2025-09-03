package raft

import (
	"bytes"
	"math"
	"math/rand"
	"sync"
	"sync/atomic"
	"time"

	"6.5840/labgob"
	"6.5840/labrpc"
)

type ApplyMsg struct {
	CommandValid bool
	Command      interface{}
	CommandIndex int

	SnapshotValid bool
	Snapshot      []byte
	SnapshotTerm  int
	SnapshotIndex int
}

type ServerState int

const (
	FOLLOWER ServerState = iota
	CANDIDATE
	LEADER
)

type LogEntry struct {
	Term    int
	Command interface{}
}

// A Go object implementing a single Raft peer.
type Raft struct {
	mu        sync.Mutex
	peers     []*labrpc.ClientEnd
	persister *Persister
	me        int
	dead      int32

	// Persistent all
	currentTerm int
	votedFor    int
	log         []LogEntry

	// Volatile all
	commitIndex int
	lastApplied int

	// Volatile lead
	nextIndex  []int
	matchIndex []int

	// Election
	state           ServerState
	electionTimeout time.Time

	applyCh chan ApplyMsg
}

// return currentTerm and whether this server
// believes it is the leader.
func (rf *Raft) GetState() (int, bool) {
	rf.mu.Lock()
	defer rf.mu.Unlock()
	return rf.currentTerm, rf.state == LEADER
}

// save Raft's persistent state to stable storage,
// where it can later be retrieved after a crash and restart.
// see paper's Figure 2 for a description of what should be persistent.
// before you've implemented snapshots, you should pass nil as the
// second argument to persister.Save().
// after you've implemented snapshots, pass the current snapshot
// (or nil if there's not yet a snapshot).
func (rf *Raft) persist() {
	w := new(bytes.Buffer)
	e := labgob.NewEncoder(w)
	e.Encode(rf.currentTerm)
	e.Encode(rf.votedFor)
	e.Encode(rf.log)
	data := w.Bytes()
	rf.persister.Save(data, nil)
}

// restore previously persisted state.
func (rf *Raft) readPersist(data []byte) {
	if data == nil || len(data) < 1 { // bootstrap without any state?
		return
	}
	r := bytes.NewBuffer(data)
	d := labgob.NewDecoder(r)
	var currentTerm int
	var votedFor int
	var log []LogEntry
	if d.Decode(&currentTerm) != nil ||
		d.Decode(&votedFor) != nil ||
		d.Decode(&log) != nil {
		return
	}
	rf.currentTerm = currentTerm
	rf.votedFor = votedFor
	rf.log = log
}

// the service says it has created a snapshot that has
// all info up to and including index. this means the
// service no longer needs the log through (and including)
// that index. Raft should now trim its log as much as possible.
func (rf *Raft) Snapshot(index int, snapshot []byte) {
	// Your code here (3D).

}

// example RequestVote RPC arguments structure.
// field names must start with capital letters!
type RequestVoteArgs struct {
	Term         int
	CandidateId  int
	PrevLogIndex int
	PrevLogTerm  int
}

// example RequestVote RPC reply structure.
// field names must start with capital letters!
type RequestVoteReply struct {
	Term        int
	VoteGranted bool
}

type AppendEntriesArgs struct {
	Term         int
	LeaderId     int
	PrevLogIndex int
	PrevLogTerm  int
	Entries      []LogEntry
	LeaderCommit int
}

type AppendEntriesReply struct {
	Term    int
	Success bool
	XTerm   int
	XIndex  int
	XLen    int
}

// example RequestVote RPC handler.
func (rf *Raft) RequestVote(args *RequestVoteArgs, reply *RequestVoteReply) {
	rf.mu.Lock()
	defer rf.mu.Unlock()
	defer rf.persist()

	reply.Term = rf.currentTerm
	reply.VoteGranted = false

	if args.Term < rf.currentTerm {
		return
	}

	if args.Term > rf.currentTerm {
		rf.currentTerm = args.Term
		rf.state = FOLLOWER
		rf.votedFor = -1
	}

	prevLogIndex := len(rf.log) - 1
	prevLogTerm := -1
	if prevLogIndex >= 0 {
		prevLogTerm = rf.log[prevLogIndex].Term
	}

	if (rf.votedFor == -1 || rf.votedFor == args.CandidateId) &&
		(args.PrevLogTerm > prevLogTerm ||
			(args.PrevLogTerm == prevLogTerm && args.PrevLogIndex >= prevLogIndex)) {
		reply.VoteGranted = true
		rf.votedFor = args.CandidateId
		rf.resetElectionTimeout()
	}
}

func (rf *Raft) AppendEntries(args *AppendEntriesArgs, reply *AppendEntriesReply) {
	rf.mu.Lock()
	defer rf.mu.Unlock()
	defer rf.persist()

	reply.Term = rf.currentTerm
	reply.Success = false
	reply.XTerm = -1
	reply.XIndex = -1
	reply.XLen = len(rf.log)

	if args.Term < rf.currentTerm {
		return
	}

	if args.Term > rf.currentTerm {
		rf.currentTerm = args.Term
		rf.state = FOLLOWER
		rf.votedFor = -1
	}

	rf.resetElectionTimeout()

	if args.PrevLogIndex >= len(rf.log) {
		reply.Success = false
		return
	}

	if args.PrevLogIndex >= 0 && rf.log[args.PrevLogIndex].Term != args.PrevLogTerm {
		reply.Success = false
		reply.XTerm = rf.log[args.PrevLogIndex].Term
		for i := args.PrevLogIndex; i >= 0; i-- {
			if rf.log[i].Term == reply.XTerm {
				reply.XIndex = i
			} else if rf.log[i].Term < reply.XTerm {
				break
			}
		}
		return
	}

	if len(args.Entries) > 0 {
		newIndex := args.PrevLogIndex + 1
		if newIndex < len(rf.log) {
			if rf.log[newIndex].Term != args.Entries[0].Term {
				rf.log = rf.log[:newIndex]
			}
		}

		if newIndex >= len(rf.log) {
			rf.log = append(rf.log, args.Entries...)
		} else {
			for i, entry := range args.Entries {
				if newIndex+i >= len(rf.log) {
					rf.log = append(rf.log, args.Entries[i:]...)
					break
				}
				if rf.log[newIndex+i].Term != entry.Term {
					rf.log = rf.log[:newIndex+i]
					rf.log = append(rf.log, args.Entries[i:]...)
					break
				}
			}
		}
	}

	if args.LeaderCommit > rf.commitIndex {
		lastNewIndex := args.PrevLogIndex + len(args.Entries)

		lastMatchingIndex := lastNewIndex
		for i := lastNewIndex; i >= 0; i-- {
			if i < len(rf.log) && rf.log[i].Term == args.Term {
				lastMatchingIndex = i
				break
			}
		}
		rf.commitIndex = int(math.Min(float64(args.LeaderCommit), float64(lastMatchingIndex)))
		go rf.applyCommitted()
	}

	reply.Success = true
}

// example code to send a RequestVote RPC to a server.
// server is the index of the target server in rf.peers[].
// expects RPC arguments in args.
// fills in *reply with RPC reply, so caller should
// pass &reply.
// the types of the args and reply passed to Call() must be
// the same as the types of the arguments declared in the
// handler function (including whether they are pointers).
//
// The labrpc package simulates a lossy network, in which servers
// may be unreachable, and in which requests and replies may be lost.
// Call() sends a request and waits for a reply. If a reply arrives
// within a timeout interval, Call() returns true; otherwise
// Call() returns false. Thus Call() may not return for a while.
// A false return can be caused by a dead server, a live server that
// can't be reached, a lost request, or a lost reply.
//
// Call() is guaranteed to return (perhaps after a delay) *except* if the
// handler function on the server side does not return.  Thus there
// is no need to implement your own timeouts around Call().
//
// look at the comments in ../labrpc/labrpc.go for more details.
//
// if you're having trouble getting RPC to work, check that you've
// capitalized all field names in structs passed over RPC, and
// that the caller passes the address of the reply struct with &, not
// the struct itself.
func (rf *Raft) sendRequestVote(server int, args *RequestVoteArgs, reply *RequestVoteReply) bool {
	ok := rf.peers[server].Call("Raft.RequestVote", args, reply)
	return ok
}

func (rf *Raft) sendAppendEntriesRPC(server int, args *AppendEntriesArgs, reply *AppendEntriesReply) bool {
	ok := rf.peers[server].Call("Raft.AppendEntries", args, reply)
	return ok
}

func (rf *Raft) Start(command interface{}) (int, int, bool) {
	rf.mu.Lock()
	defer rf.mu.Unlock()

	if rf.state != LEADER {
		return -1, rf.currentTerm, false
	}

	entry := LogEntry{
		Term:    rf.currentTerm,
		Command: command,
	}

	rf.log = append(rf.log, entry)
	rf.matchIndex[rf.me] = len(rf.log) - 1
	rf.nextIndex[rf.me] = len(rf.log)
	rf.persist()

	if len(rf.log) == 1 {
		go rf.sendHeartbeats()
	}

	return len(rf.log) - 1, rf.currentTerm, true
}

func (rf *Raft) Kill() {
	atomic.StoreInt32(&rf.dead, 1)
}

func (rf *Raft) killed() bool {
	z := atomic.LoadInt32(&rf.dead)
	return z == 1
}

func (rf *Raft) resetElectionTimeout() {
	rf.electionTimeout = time.Now().Add(time.Duration(150+rand.Intn(150)) * time.Millisecond)
}

func (rf *Raft) ticker() {
	for rf.killed() == false {
		rf.mu.Lock()
		var electionTime = time.Now().After(rf.electionTimeout) && rf.state != LEADER
		rf.mu.Unlock()

		if electionTime {
			rf.startElection()
		}

		time.Sleep(10 * time.Millisecond)
	}
}

func (rf *Raft) startElection() {
	rf.mu.Lock()
	rf.currentTerm++
	rf.state = CANDIDATE
	rf.votedFor = rf.me
	rf.persist()
	prevLogTerm := -1
	if len(rf.log)-1 >= 0 {
		prevLogTerm = rf.log[len(rf.log)-1].Term
	}
	rf.resetElectionTimeout()

	args := &RequestVoteArgs{
		Term:         rf.currentTerm,
		CandidateId:  rf.me,
		PrevLogIndex: len(rf.log) - 1,
		PrevLogTerm:  prevLogTerm,
	}

	rf.mu.Unlock()

	voteCh := make(chan bool, len(rf.peers))
	for i := range rf.peers {
		if i != rf.me {
			go rf.askVoteReply(i, args, voteCh)
		}
	}

	go rf.countVotes(len(rf.peers)-1, args.Term, voteCh)
}

func (rf *Raft) askVoteReply(peer int, args *RequestVoteArgs, voteCh chan bool) {
	reply := &RequestVoteReply{}

	if rf.sendRequestVote(peer, args, reply) {
		rf.mu.Lock()
		defer rf.mu.Unlock()

		if rf.state != CANDIDATE || rf.currentTerm != args.Term {
			voteCh <- false
			return
		}

		if reply.Term > rf.currentTerm {
			rf.state = FOLLOWER
			rf.currentTerm = reply.Term
			rf.votedFor = -1
			rf.persist()
			rf.resetElectionTimeout()
			voteCh <- false
			return
		}

		voteCh <- reply.VoteGranted
	} else {
		voteCh <- false
	}
}

func (rf *Raft) countVotes(expectedVotes int, term int, voteCh chan bool) {
	votes := 1

	for i := 0; i < expectedVotes; i++ {
		if <-voteCh {
			votes++
			if votes > len(rf.peers)/2 {
				rf.mu.Lock()
				if rf.state == CANDIDATE && rf.currentTerm == term {
					rf.becomeLeader()
				}
				rf.mu.Unlock()
				return
			}
		}
	}
}

func (rf *Raft) becomeLeader() {
	rf.state = LEADER
	rf.nextIndex = make([]int, len(rf.peers))
	rf.matchIndex = make([]int, len(rf.peers))
	for i := range rf.peers {
		rf.nextIndex[i] = len(rf.log)
		rf.matchIndex[i] = 0
	}
	go rf.sendHeartbeats()
}

func (rf *Raft) sendHeartbeats() {
	for rf.killed() == false {
		rf.mu.Lock()
		if rf.state != LEADER {
			rf.mu.Unlock()
			return
		}
		rf.mu.Unlock()

		for i := range rf.peers {
			if i != rf.me {
				go rf.sendHeartbeat(i)
			}
		}

		time.Sleep(100 * time.Millisecond)
	}
}

func (rf *Raft) sendHeartbeat(peer int) {
	rf.mu.Lock()
	if rf.state != LEADER {
		rf.mu.Unlock()
		return
	}

	prevLogIndex := rf.nextIndex[peer] - 1
	var prevLogTerm int
	if prevLogIndex >= 0 {
		prevLogTerm = rf.log[prevLogIndex].Term
	}

	entries := make([]LogEntry, len(rf.log[rf.nextIndex[peer]:]))
	copy(entries, rf.log[rf.nextIndex[peer]:])

	args := &AppendEntriesArgs{
		Term:         rf.currentTerm,
		LeaderId:     rf.me,
		PrevLogIndex: prevLogIndex,
		PrevLogTerm:  prevLogTerm,
		Entries:      entries,
		LeaderCommit: rf.commitIndex,
	}
	rf.mu.Unlock()

	reply := &AppendEntriesReply{}
	if ok := rf.peers[peer].Call("Raft.AppendEntries", args, reply); ok {
		rf.mu.Lock()
		defer rf.mu.Unlock()

		if reply.Term > rf.currentTerm {
			rf.state = FOLLOWER
			rf.currentTerm = reply.Term
			rf.votedFor = -1
			rf.persist()
			rf.resetElectionTimeout()
			return
		}

		if rf.state != LEADER || args.Term != rf.currentTerm {
			return
		}

		if reply.Success {
			rf.matchIndex[peer] = prevLogIndex + len(entries)
			rf.nextIndex[peer] = rf.matchIndex[peer] + 1
			rf.updateCommitIndex()
		} else {
			if reply.XTerm == -1 {
				rf.nextIndex[peer] = reply.XLen
			} else {
				lastIndex := -1
				for i := len(rf.log) - 1; i >= 0; i-- {
					if rf.log[i].Term == reply.XTerm {
						lastIndex = i
						break
					}
				}

				if lastIndex == -1 {
					rf.nextIndex[peer] = reply.XIndex
				} else {
					rf.nextIndex[peer] = lastIndex + 1
				}
			}
		}
	}
}

func (rf *Raft) updateCommitIndex() {
	for n := len(rf.log) - 1; n > rf.commitIndex; n-- {
		if n < 0 || n >= len(rf.log) {
			continue
		}
		if rf.log[n].Term == rf.currentTerm {
			count := 1
			for peer := range rf.peers {
				if peer != rf.me && rf.matchIndex[peer] >= n {
					count++
				}
			}
			if count > len(rf.peers)/2 {
				rf.commitIndex = n
				go rf.applyCommitted()
				break
			}
		}
	}
}

func (rf *Raft) applyCommitted() {
	rf.mu.Lock()
	defer rf.mu.Unlock()

	lastIndex := len(rf.log) - 1
	for i := rf.lastApplied + 1; i <= rf.commitIndex && i <= lastIndex; i++ {
		msg := ApplyMsg{
			CommandValid: true,
			Command:      rf.log[i].Command,
			CommandIndex: i,
		}
		rf.applyCh <- msg
		rf.lastApplied = i
	}
}

func Make(peers []*labrpc.ClientEnd, me int,
	persister *Persister, applyCh chan ApplyMsg) *Raft {
	rf := &Raft{}
	rf.peers = peers
	rf.persister = persister
	rf.me = me
	rf.applyCh = applyCh

	rf.currentTerm = 0
	rf.votedFor = -1
	rf.log = make([]LogEntry, 0)
	rf.log = append(rf.log, LogEntry{Term: 0})

	rf.commitIndex = 0
	rf.lastApplied = 0

	rf.state = FOLLOWER
	rf.nextIndex = make([]int, len(peers))
	rf.matchIndex = make([]int, len(peers))

	rf.readPersist(persister.ReadRaftState())
	rf.resetElectionTimeout()

	go rf.ticker()

	return rf
}
