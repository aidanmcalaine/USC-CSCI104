#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>
using namespace std;

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

//Implemetation of the push_back function
void ULListStr::push_back(const std::string& val) {
    //First check to make sure there are not zero nodes
    if (head_ == NULL) {
        //allocate a new node
        Item* node = new Item();
        head_ = node;
        tail_ = node;
        head_->next = NULL;
        //assign the value
        head_->val[0] = val;
        head_->first = 0;
        head_->last = 1;
        return;
    }
    //There are nodes
    //Check to see if there is room in the back of the list
    if (head_->last != ARRSIZE) {
        //we can insert the element into the array
        head_->val[head_->last] = val;
        //Move last back
        head_->last++;
        //update size
        size_++;
    }
    else {
        //The array is full
        //Create a new item, point it in both directions
        Item* node = new Item();
        node->next = NULL;
        node->prev = tail_;
        //Point current tail to the next tail
        tail_->next = node;
        tail_ = node;
        //Set first and last values of the new node
        tail_->first = 0;
        tail_->last = 1;
        //Fill the first index of the new array
        tail_->val[0] = val;
        //update the size
        size_++;
    }
}

//Implementation of the push_front function
void ULListStr::push_front(const std::string& val) {
    //First check to make sure there are not zero nodes
    if (head_ == NULL) {
        //allocate a new node
        Item* node = new Item();
        head_ = node;
        tail_ = node;
        //assign the value
        head_->val[9] = val;
        head_->first = 9;
        head_->last = 10;
        return;
    }
    //Check to see if there is room in the front of the list
    if (head_->first != 0) {
        //There is room - decrement first and insert the element into the array
        head_->first--;
        head_->val[head_->first] = val;
        size_++;
    }
    else {
        //There is not room in the current node
        //Allocate a new node and point it towards the previous
        Item* node = new Item();
        node->next = head_;
        head_->prev = node;
        head_ = node;
        //Set first and last values of the new node
        head_->first = ARRSIZE-1;
        head_->last = ARRSIZE;
        //Assign the value to the back of the new node's array
        head_->val[head_->first] = val;
        //update the size
        size_++;
    }
}
//Implementation of the pop_back function
void ULListStr::pop_back() {
    if (head_ == NULL) {
        //no nodes
        cout << "empty list popback" << endl;
        return;
    }
    else if (tail_->last - tail_->first == 1) {
        //there is one element in the tail
        tail_ = tail_->prev;
        delete tail_->next;
        tail_->next = NULL;
        size_--;
    }
    else if (head_ == tail_ && head_->last - head_->first == 1) {
        //there is one element in the array
        delete head_;
        //set both to null
        head_ = NULL;
        size_--;
    }
    else {
        //Simple decrement
        tail_->last--;
        size_--;
    }
    
}
//Implementation of the pop_front function
void ULListStr::pop_front() {
    if (head_ == NULL) {
        //no nodes
        return;
    }
    else if (head_->last - head_->first == 1) {
        //there is one element in the head
        head_ = head_->next;
        delete head_->prev;
        head_->prev = NULL;
        size_--;
    }
    else if (head_ == tail_ && head_->last - head_->first == 1) {
        //there is one element in the array
        delete head_;
        //set both to null
        head_ = NULL;
        size_--;
    }
    else {
        //simple increment
        head_->first++;
        size_--;
    }
   
}
//Implementatiom of the back function
std::string const & ULListStr::back() const {
    //decrement last to get to the last index
    tail_->last--;
    //return the const reference to the back element
    return tail_->val[tail_->last];
}
//Implementation of the front function
std::string const & ULListStr::front() const {
    //return the const reference to the front element
    return head_->val[head_->first];
}
//Implementation of the getValAtLoc function
std::string* ULListStr::getValAtLoc(size_t loc) const {
    //returs a pointer to the node at index, loc
    //Check to see if loc is a valid index
    int index = loc;
    Item* node = head_;
    if (loc >= 0 && loc < ARRSIZE) {
        //loc is valid
        //create node to work with
     
        while (node != NULL) {
            int n = node->last - node->first;
            if (index < n) {
                //the index is within the bounds of this node - no need to traverse
                return & node->val[node->first + index];
            }
            else {
                //we need to traverse the list
                node = node->next;
                index -= n;
                //we can then go back through the loop
            }
        }
    }
    return NULL;
}
//Implementation of the print function for the tester file
void ULListStr::print() {
    //create a current element and set it to head
    Item* curr = head_;
    if (curr == NULL) {
        //check to see if the list is empty
        cout << "Inside Empty List" << endl;
        return;
    }
    int n = 1;
    while (curr != NULL) {
        //Print out current item
        cout << "Current Item " << n << ":" << endl;
        //Increment the item
        n++;
        for (size_t i = curr->first; i < curr->last; i++) {
            //print out the values in the array
            cout << curr->val[i] << " ";
        }
        cout << endl;
        curr = curr->next;
        cout << endl;
    }
}

