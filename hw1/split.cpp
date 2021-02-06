/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <iostream>
using namespace std;

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
    //base case
    if (in == NULL) {
        //There are no nodes in the linked list
        //Set the ends to null and return
        odds = NULL;
        evens = NULL;
        in = NULL;
        return;
    }
    else {
        //recursive case
        
        //check if even
        if (in->value % 2 == 0) {
            //the value is even, needs to be added to evens LL
            //set even node
            evens = in;
            in = in->next;
            //call
            split(in, odds, evens->next);
            
        }
        else {
            //the value is odd
            //set odd node
            odds = in;
            in = in->next;
            
            //call
            split(in, odds->next, evens);
        }
    }
}

/* If you needed a helper function, write it here */
