package mr

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"sort"
	"time"
)
import "log"
import "net/rpc"
import "hash/fnv"

type KeyValue struct {
	Key   string
	Value string
}
type withKey []KeyValue

func (a withKey) Len() int {
	return len(a)
}
func (a withKey) Less(i, j int) bool {
	return a[i].Key < a[j].Key
}
func (a withKey) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}

var WaitTime = time.Second

func ihash(key string) int {
	h := fnv.New32a()
	h.Write([]byte(key))
	return int(h.Sum32() & 0x7fffffff)
}

func Worker(mapf func(string, string) []KeyValue,
	reducef func(string, []string) string) {

	for {
		task := RequestTask()

		if task.Type == Map {
			MapTask(mapf, task)
		} else if task.Type == Reduce {
			ReduceTask(reducef, task)
		} else if task.Type == Wait {
			WaitTask()
		} else {
			break
		}
	}
}

func RequestTask() Task {
	args := Args{}
	task := Task{}

	call("Coordinator.TaskRequest", &args, &task)
	return task
}

func ReportTask(taskId int, taskType Type, filename string) {
	args := Report{taskId, taskType, filename}
	reply := Args{}

	call("Coordinator.TaskReport", &args, &reply)
}

func MapTask(mapf func(string, string) []KeyValue, task Task) {
	data := read(task.InputFile)
	mapped := mapf(task.InputFile, data)
	filename := encode(mapped, task)

	ReportTask(task.TaskID, task.Type, filename)
}

func ReduceTask(reducef func(string, []string) string, task Task) {
	data := collectData(task)
	sorted := sortData(data)
	keys, groupedValues := groupData(sorted)
	filename := reduce(reducef, keys, groupedValues, task)

	ReportTask(task.TaskID, task.Type, filename)
}

func WaitTask() {
	time.Sleep(WaitTime)
}

func read(filename string) string {
	file, _ := os.Open(filename)
	data, _ := ioutil.ReadFile(filename)
	err := file.Close()
	if err != nil {
		return ""
	}
	return string(data)
}

func encode(data []KeyValue, task Task) string {
	ofile, _ := os.CreateTemp(".", "map")

	enc := json.NewEncoder(ofile)
	for _, pair := range data {
		err := enc.Encode(&pair)
		if err != nil {
			return ""
		}
	}

	err := ofile.Close()
	if err != nil {
		return ""
	}
	filename := fmt.Sprintf("mr-map-%v", task.TaskID)
	err = os.Rename(ofile.Name(), filename)
	if err != nil {
		return ""
	}

	return filename
}

func collectData(task Task) []KeyValue {
	var data []KeyValue

	for _, filename := range task.IntermediateFiles {

		file, err := os.Open(filename)
		if err != nil {
			return nil
		}
		defer file.Close()

		dec := json.NewDecoder(file)
		for {
			var pair KeyValue
			err = dec.Decode(&pair)
			if err != nil {
				break
			}
			if ihash(pair.Key)%task.NReduce == task.TaskID {
				data = append(data, pair)
			}
		}
	}

	return data
}

func sortData(data []KeyValue) []KeyValue {
	sort.Sort(withKey(data))

	return data
}

func groupData(data []KeyValue) ([]string, [][]string) {
	var keys []string
	var groupedValues [][]string

	if len(data) == 0 {
		return keys, groupedValues
	}

	keys = append(keys, data[0].Key)
	groupedValues = append(groupedValues, []string{data[0].Value})

	for i := 1; i < len(data); i++ {
		lastIndex := len(keys) - 1
		if data[i].Key == keys[lastIndex] {
			groupedValues[lastIndex] = append(groupedValues[lastIndex], data[i].Value)
		} else {
			keys = append(keys, data[i].Key)
			groupedValues = append(groupedValues, []string{data[i].Value})
		}
	}

	return keys, groupedValues
}

func reduce(reducef func(string, []string) string, keys []string, values [][]string, task Task) string {
	filename := fmt.Sprintf("mr-out-%v", task.TaskID)
	ofile, _ := os.CreateTemp(".", "reduce")
	for i := range keys {
		output := reducef(keys[i], values[i])
		fmt.Fprintf(ofile, "%v %v\n", keys[i], output)
	}
	err := ofile.Close()
	if err != nil {
		return ""
	}
	err = os.Rename(ofile.Name(), filename)
	if err != nil {
		return ""
	}

	return filename
}

func call(rpcname string, args interface{}, reply interface{}) bool {
	sockname := coordinatorSock()
	c, err := rpc.DialHTTP("unix", sockname)
	if err != nil {
		log.Fatal("dialing:", err)
	}
	defer c.Close()

	err = c.Call(rpcname, args, reply)
	if err == nil {
		return true
	}

	fmt.Println(err)
	return false
}
