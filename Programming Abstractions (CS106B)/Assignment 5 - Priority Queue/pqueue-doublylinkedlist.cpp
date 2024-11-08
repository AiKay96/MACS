/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = new Node;
	tail = new Node;
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
	qsize=0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* prevNode;
	while (head != NULL) {
		prevNode = head;
		head = head->next;
		delete prevNode;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return qsize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (qsize == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* addValue = new Node;
	addValue->value = value;
	addValue->prev = head;
	addValue->next = head->next;
	Node* nextNode = head->next;
	head->next = addValue;
	nextNode->prev = addValue;
	qsize++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("element not found, front");
	}else{
		Node* temp = head->next;
		nodeValue = head->next;
		while(true){
			if(temp->next == tail){
				break;
			}
			if(temp->next->value < nodeValue->value){
				nodeValue = temp->next;
			}
			temp = temp->next;
		}
		return nodeValue->value;
	}
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string ans = peek();
	nodeValue->prev->next = nodeValue->next;
	nodeValue->next->prev = nodeValue->prev;
	delete nodeValue;
	qsize--;
	return ans;
}

