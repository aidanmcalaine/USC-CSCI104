#ifndef MINHEAP_H
#define HEAP_H

#include <stdexcept> 
#include <vector> 
#include <iostream> 
using namespace std; 

template<class T> 
class MinHeap {
public: 
	MinHeap(int d); 
		/* Constructor that builds a d-ary MinHeap 
		   This should work for any d >= 2, 
		   but doesn't have to do anything for a smaller d. 
		*/
	~MinHeap(); 
		//Destructor 
	void add (T item, int priority); 
		//Adds the item to the heap, with the given priority 
	const T & peek () const; 
		/* Returns the element with the smallest priority. 
		   Break ties however you wish. 
		   Throws an exception if the heap is empty. 
		*/
	void remove(); 
		/* Removes the element with the smallest priority. 
		   Break ties however you wish. 
		   Throws an exception if the heap is empty 
		*/
	bool isEmpty(); 
		/* Returns true iff there are no elements on the heap. 
		*/
	//size function 
	int size(); 

private: 
	//whatever you need to naturally store things 
	//You may also add helper functions here 
	void trickleUp(int loc); 
	void trickleDown(int loc); 
	vector<T> nodes; 
	int numChildren; 
}; 

//Implementation 

//Constructor 
template<typename T>
MinHeap<T>::MinHeap(int d) {
	if (d >= 2) {
		numChildren = d; 
	}
}

//Destructor 
template<typename T>
MinHeap<T>::~MinHeap() {
}

//add implementation 
template<typename T>
void MinHeap<T>::add(T item, int priority) {
	//add the item and set the value, then trickleUp to the correct location 
	nodes.push_back(item); 
	nodes[nodes.size()-1] = priority; 
	trickleUp(nodes.size()-1); 
}

//peek implementation 
template<typename T>
const T & MinHeap<T>::peek() const {
	//should just return a reference to the top node 
	if (nodes.size() == 0) {
		throw logic_error("The heap is empty."); 
	}
	return nodes[0]; 
}


//remove implementation 
template<typename T>
void MinHeap<T>::remove() {
	//check if the heap is empty
	if (isEmpty()) {
		throw logic_error("The heap is already empty."); 
	}
	//Otherwise, we need to replace the top node with the last node and reorder
	nodes[0] = nodes.back(); 
	nodes.pop_back(); 
	trickleDown(0); 
}

//isEmpty Implementation 
template<typename T>
bool MinHeap<T>::isEmpty() {
	//returns whether or not the list of nodes is empty 
	return nodes.empty(); 
}

//trickleUp Implementation 
template<typename T>
void MinHeap<T>::trickleUp(int loc) {
	//get parent's position 
	int parent = (loc - 1)/2; 
	//enter the trickleUp loop 
	while (parent >= 0 && nodes[loc] < nodes[parent]) {
		//swap parent and child
		swap(nodes[parent], nodes[loc]); 
		//reassign child and parent nodes 
		loc = parent; 
		parent = (loc - 1)/2; 
	}
}

//trickleDown Implementation 
template<typename T> 
void MinHeap<T>::trickleDown(int loc) {
	//check edge case
	if (2 * loc + 1 >= nodes.size()) {
		return; 
	}
	//start with the left node 
	int smallerChild = 2*loc+1; 
	if (smallerChild + 1 < nodes.size()) {
		int rightChild = smallerChild + 1; 
		//determine which of the child nodes is the smallest
		if (nodes[rightChild] < nodes[smallerChild]) {
			//if rightChild is smaller, assign its value to smallerChild 
			smallerChild = rightChild; 
		}
	}
	//check which is larger
	if (nodes[loc] > nodes[smallerChild]) {
		//if the current node is greater than the smaller child, swap them 
		swap(nodes[loc], nodes[smallerChild]); 
		//recurse to continue trickling down the heap 
		trickleDown(smallerChild); 
	}
}

//size implementation
template<typename T>
int MinHeap<T>::size() {
	return nodes.size(); 
}

#endif
