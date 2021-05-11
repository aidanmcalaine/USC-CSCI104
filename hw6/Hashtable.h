//Aidan McAlaine
//Hw6

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector> 
#include <map>
using namespace std; 

class Hashtable {
public: 

	Hashtable(bool debug = false, unsigned int probing = 0); 
	/* Hash table constructor
	probing will always be 0, 1, or 2.0 
	0 - linear probing
	1 - quadratic probing 
	2 - double hashing 
	*/

	~Hashtable(); 
	//Destructor 

	void add(string k); 
	//add a given string to the hashtable 

	int count(string k); 
	//return the int associated with k

	void reportAll(ostream& ofile) const; 
	//output every (key, value) pair in the hashtable 

	//getters
	void setProbe(int x); 
	void setDebug(bool y); 


private: 

	void resize(); 
	/* approximately doubles the number of indices available 
	called when we insert into a hash table w/ a load factor >= 0.5
	*/

	int hash(string k) const; 
	//outputs a pseudo-random index to store the string at 

	int h(string w) const; 
	//second hash function 

	int findVal(string k); 

	//array of <string, int> pairs for the hashtable 
	std::pair<string, int>** table;

	//array to store prime numbers for resizing 
	int primeNumbers[28]; 

	//store current prime number index
	int primeNumberIndex; 

	//store table sizes 
	int sizes[28]; 

	//table size
	int m ;  
	//number of keys in the table 
	int numKeys;  
	//store loading factor 
	double loadingFactor; 
	//store probing number
	int probe; 
	//store debug flag 
	bool debugger; 

	//random numbers 
	int r1, r2, r3, r4, r5; 
	int v1, v2, v3, v4, v5; 
}; 

#endif
