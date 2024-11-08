/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	qsize = 0;
	currentSize = 32;
	data = new string[currentSize]();
}
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] data;
}
int HeapPriorityQueue::size() {
	return qsize;
}
bool HeapPriorityQueue::isEmpty() {
	return (qsize == 0);;
}
void HeapPriorityQueue::enqueue(string value) {
	if (qsize == currentSize) {
		resize(2*currentSize);
	}
	data[qsize] = value;
	qsize++;
	int temp = qsize;

	while(temp > 1 && data[temp-1] < data[temp/2 - 1]){
		string tempValue = data[temp/2 - 1];
		data[temp/2 - 1] = data[temp - 1];
		data[temp - 1] = tempValue;
		temp = temp/2;
	}
}
void HeapPriorityQueue::resize(int newSize) {
	string* freshData = new string[newSize]();
	for (int i=0; i < currentSize; i++){
		freshData[i] = data[i];
	}
	delete[] data;
	data = freshData;
	currentSize = newSize;
}
string HeapPriorityQueue::peek() {
	if (isEmpty()) {
		error("element not found");
	}else{
		return data[0];
	}
}
string HeapPriorityQueue::dequeueMin() {
	string ans = peek();
	int temp = 1;
	data[temp-1] = data[qsize-1];
	string tempValue;
	while((2*temp-1 <qsize && data[temp-1] > data[2*temp-1]) || (2*temp < qsize && data[temp-1] > data[2*temp])){
		if(2*temp < qsize && data[2*temp-1] > data[2*temp]){
			tempValue = data[2*temp];
			data[2*temp] = data[temp - 1];
			data[temp - 1] = tempValue;
			temp = 2*temp+1;
		}else{
			tempValue = data[2*temp-1];
			data[2*temp-1] = data[temp - 1];
			data[temp - 1] = tempValue;
			temp = 2*temp;
		}
	}
	qsize--;
	return ans;
}