package mr

import (
	"log"
	"sync"
	"time"
)
import "net"
import "os"
import "net/rpc"
import "net/http"

type Status string

const (
	Idle       Status = "Idle"
	InProgress Status = "InProgress"
	Completed  Status = "Completed"
)

type Coordinator struct {
	mu                sync.Mutex
	files             []string
	intermediateFiles []string
	statuses          []Status
	phase             Type
	nReduce           int
	done              bool
}

var controlTime = time.Second * 10

func (c *Coordinator) server() {
	rpc.Register(c)
	rpc.HandleHTTP()
	//l, e := net.Listen("tcp", ":1234")
	sockname := coordinatorSock()
	os.Remove(sockname)
	l, e := net.Listen("unix", sockname)
	if e != nil {
		log.Fatal("listen error:", e)
	}
	go http.Serve(l, nil)
}

func (c *Coordinator) TaskRequest(args *Args, task *Task) error {
	c.mu.Lock()
	defer c.mu.Unlock()

	for taskID, status := range c.statuses {
		if status == Idle {
			c.statuses[taskID] = InProgress

			task.TaskID = taskID
			task.Type = c.phase
			task.NReduce = c.nReduce

			if c.phase == Map {
				task.InputFile = c.files[taskID]
			} else {
				task.IntermediateFiles = c.intermediateFiles
			}

			go controlWorker(c, taskID)
			return nil
		}

	}

	task.TaskID = -1
	task.Type = Wait

	return nil
}

func controlWorker(c *Coordinator, taskID int) {
	time.Sleep(controlTime)

	c.mu.Lock()
	defer c.mu.Unlock()

	if c.statuses[taskID] == InProgress {
		c.statuses[taskID] = Idle
	}

}

func (c *Coordinator) TaskReport(args *Report, reply *Args) error {
	c.mu.Lock()
	defer c.mu.Unlock()

	if args.Type != c.phase {
		return nil
	}

	if c.statuses[args.TaskID] == Completed && args.Type == c.phase {
		return nil
	}

	c.statuses[args.TaskID] = Completed

	if args.Type == Map {
		c.intermediateFiles = append(c.intermediateFiles, args.OutputFile)
	}

	if c.allTasksCompleted() {
		if args.Type == Map {
			c.transitionToReducePhase()
		} else {
			c.done = true
		}
	}

	return nil
}

func (c *Coordinator) transitionToReducePhase() {
	c.phase = Reduce

	c.statuses = make([]Status, c.nReduce)
	for i := 0; i < c.nReduce; i++ {
		c.statuses[i] = Idle
	}
}

func (c *Coordinator) allTasksCompleted() bool {
	for _, status := range c.statuses {
		if status != Completed {
			return false
		}
	}
	return true
}

func (c *Coordinator) Done() bool {
	c.mu.Lock()
	defer c.mu.Unlock()

	return c.done
}

func MakeCoordinator(files []string, nReduce int) *Coordinator {
	c := Coordinator{
		files:             files,
		intermediateFiles: []string{},
		statuses:          make([]Status, len(files)),
		phase:             Map,
		nReduce:           nReduce,
		done:              false,
	}

	c.mu.Lock()

	for i := range files {
		c.statuses[i] = Idle
	}

	c.mu.Unlock()

	c.server()
	return &c
}
