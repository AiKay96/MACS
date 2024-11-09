package mr

import "os"
import "strconv"

type Type string

const (
	Map    Type = "Map"
	Reduce Type = "Reduce"
	Wait   Type = "Wait"
)

type Args struct {
}

type Task struct {
	TaskID            int
	Type              Type
	NReduce           int
	InputFile         string
	OutputFile        string
	IntermediateFiles []string
}

type Report struct {
	TaskID     int
	Type       Type
	OutputFile string
}

func coordinatorSock() string {
	s := "/var/tmp/5840-mr-"
	s += strconv.Itoa(os.Getuid())
	return s
}
