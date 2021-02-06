/* Write your test code for the ULListStr in this file */

#include "ulliststr.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
    //allocate node
    ULListStr* tester = new ULListStr();
    
    //Different cases
    
    //Push back a number into an empty node
    tester->push_back(to_string(1));
    tester->print();
    //should print out 1
    
    //push back three more values
    tester->push_back(to_string(2));
    tester->push_back(to_string(3));
    tester->push_back(to_string(4));
    tester->print();
    
    //pop back
    tester->pop_back();
    //should print 1 2 3
    tester->print();
    
    //pop front
    tester->pop_front();
    //should print 2 3
    tester->print();
    
    //push front
    tester->push_front(to_string(1));
    //should print 1 2 3
    tester->print();
    
    //push front into a new node
    tester->push_front(to_string(9));
    //should print 2 different items with 9 in the first and 1 2 3 in the second
    tester->print();
    
    //pop front and delete the first item
    tester->pop_front();
    //should print item 1 with 1 2 3
    tester->print();
    
    //Test the back edge cases
    //fill up the rest of the array
    tester->push_back(to_string(4));
    tester->push_back(to_string(5));
    tester->push_back(to_string(6));
    tester->push_back(to_string(7));
    tester->push_back(to_string(8));
    tester->push_back(to_string(9));
    tester->push_back(to_string(10));
    //print out a full array
    tester->print();
    
    //add a number to the back, creating a new node
    tester->push_back(to_string(1));
    //should print out two nodes with only the value 1 in the back
    tester->print();
    
    //remove that item, deleting the second node
    tester->pop_back();
    //should print out only one node
    tester->print();
    
    //Check to see that back and front work (they should point to the front/back)
    //Should print out 10 and 1
    cout << tester->back() << endl;
    cout << tester->front() << endl;
    cout << "\n";
    
    //Test get function by getting the first index
    //should print 1
    cout << tester->get(0) << endl;
    tester->clear();
    cout << "\n";
    //clear the list
   
    tester->print();
   
    //Push front into an empty list
    tester->push_front(to_string(1));
    //should print 1
    tester->print();
    
    //pop the item with pop_front
    tester->pop_front();
    //should print no values
    tester->print();
    
    tester->push_front(to_string(2));
    //should print 2
    tester->print();
    
    tester->pop_back();
    //should print nothing because the list is clear
    cout << tester->get(0);
    
    //delete memory 
    delete tester;
    return 0;
   
    
    
    
    
    
    
    
}
