/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include "vector.h"

VectorPriorityQueue::VectorPriorityQueue() {
	
}

VectorPriorityQueue::~VectorPriorityQueue() {
	v.clear();
}

int VectorPriorityQueue::size() {
	return v.size();
}

bool VectorPriorityQueue::isEmpty() {
	if(v.size()==0){
		return true;
	}
	return false;
}

void VectorPriorityQueue::enqueue(string value) {
	v.add(value);
}

string VectorPriorityQueue::peek() {
	if (isEmpty()) {
		error("element not found");
	}else{
		index = 0;
		string ans = v[0];
		for(int i = 1; i < v.size(); i++){
			if(ans > v[i]){
				ans = v[i];
				index = i;
			}
		}
		return ans;
	}
}

string VectorPriorityQueue::dequeueMin() {
	string ans = peek();
	v.remove(index);
	return ans;
}

