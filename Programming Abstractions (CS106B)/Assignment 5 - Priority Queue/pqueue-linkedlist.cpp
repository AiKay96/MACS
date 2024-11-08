/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->next = NULL;
	qsize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node* prevNode;
	while (head != NULL) {
		prevNode = head;
		head = head->next;
		delete prevNode;
	}
}

int LinkedListPriorityQueue::size() {
	return qsize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (qsize == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* temp = head;
	while(temp->next->value < value){
		if(temp->next == tail){
			break;
		}
		temp = temp->next;
	}
	Node* addValue = new Node;
	addValue->value = value;
	addValue->next = temp->next;
	temp->next = addValue;
	qsize++;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("element not found");
	}else{
		return head->next->value;
	}
}

string LinkedListPriorityQueue::dequeueMin() {
	string ans = peek();
	Node* temp = head->next->next;
	delete head->next;
	head->next = temp;
	qsize--;
	return ans;
}

