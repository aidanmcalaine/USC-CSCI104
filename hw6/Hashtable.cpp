//Aidan McAlaine
//Hw6 - Hash Tables
#include "Hashtable.h"
#include <iostream>
#include <string> 
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std; 

HashTable::HashTable(bool debug, unsigned int probing) {

	//Initialize prime number array 
	primeNumbers[0] = 11, primeNumbers[1] = 23, primeNumbers[2] = 47, primeNumbers[3] = 97,
	primeNumbers[4] = 197, primeNumbers[5] = 397, primeNumbers[6] = 797, primeNumbers[7] = 1597,
	primeNumbers[8] = 3203, primeNumbers[9] = 6421, primeNumbers[10] = 12853, primeNumbers[11] = 25717, 
	primeNumbers[12] = 51437, primeNumbers[13] = 102877, primeNumbers[14] = 205759, primeNumbers[15] = 411527,
	primeNumbers[16] = 823117, primeNumbers[17] = 1646237, primeNumbers[18] = 3292489, primeNumbers[19] = 6584983,
	primeNumbers[20] = 13169977, primeNumbers[21] = 26339969, primeNumbers[22] = 52679969, primeNumbers[23] = 105359969,
	primeNumbers[24] = 210719881, primeNumbers[25] = 421439783, primeNumbers[26] = 842879579, primeNumbers[27] = 1685759167, 

	//Initialize table sizes array
	sizes[0] = 7, sizes[1] = 19, sizes[2] = 43, sizes[3] = 89, sizes[4] = 193, sizes[5] = 389, 
	sizes[6] = 787, sizes[7] = 1583, sizes[8] = 3191, sizes[9] = 6397, sizes[10] = 12841, sizes[11] = 25703, 
	sizes[12] = 51431, sizes[13] = 102871, sizes[14] = 205721, sizes[15] = 411503, sizes[16] = 823051, sizes[17] = 1646221, 
	sizes[18] = 3292463, sizes[19] = 6584957, sizes[20] = 13169963, sizes[21] = 26339921, sizes[22] = 52679927, sizes[23] = 105359939,
	sizes[24] = 210719881, sizes[25] = 421439749, sizes[26] = 842879563, sizes[27] = 1685759113; 
	
	//create r values for a non-debug 
	r1 = rand() % (m-1); 
	r2 = rand() % (m-1); 
	r3 = rand() % (m-1); 
	r4 = rand() % (m-1); 
	r5 = rand() % (m-1);

	//create v values for debug mode
	v1 = 983132572; 
	v2 = 62337998; 
	v3 = 552714139; 
	v4 = 984953261; 
	v5 = 261934300; 

	//Initialize other variables
	primeNumberIndex = 0; 
	m = 11; 
	numKeys = 0; 
	loadingFactor = 0;
	probe = probing; 
	debugger = debug; 

	//Create the table
	this->table = new pair<string, int>*[primeNumbers[primeNumberIndex]];  
}

HashTable::~HashTable() {

}

void HashTable::add(string k) { 
	
	 
	//we first need to check if k is in the hashtable 
	for (int i = 0; i < m; i++) {

		//check each index for the string 

		if (table[i] != NULL) {
			if (table[i]->first.compare(k) == 0) {
				//we have found it 
				//increment the value
				table[i]->second++; 
				return; 
			}
		}
	}

	//At this point in the control flow, we know that the string does not exist in the hash table
	//we need to hash it and add it to the hash table with a value of one. 
	
	
	//check if we need to resize or not 
	

	if (loadingFactor >= 0.5) {
		resize(); 

	}
	loadingFactor = (double)numKeys/(double)m; 
	numKeys++; 
	//now just add the new string 
	
	//hash function making it seg fault 
	int hashNum = hash(k);  
	//probing / double hashing
	if (table[hashNum] != NULL) {
		//there is already an element in this index, so we can probe it
		if (probe == 0) {
			//linear probing
			while (table[hashNum] != NULL) {
				hashNum++; 
				//account for wrapping around 
				if (hashNum == m) {
					hashNum = 0; 
				}
			}
			//insert it
			table[hashNum] = new pair<string, int>(k, 1);
			return;  
		}
		else if (probe == 1) {			
			//quadratic probing 
			int counter = 0; 
			int quadratic = pow(counter, 2); 
			int spacer = (hashNum + quadratic) % m; 
			while (table[spacer] != NULL) {
				counter++; 
				quadratic = pow(counter, 2); 
				spacer = (hashNum + quadratic) % m; 
			}
			//Insert it
			table[spacer] = new pair<string, int>(k, 1); 
			return; 
		}
		else {
			//double hashing
			int stepsize = h(k); 
			int multiplier = 1; 
			int currIndex = (hashNum + (stepsize*multiplier)) % m; 
			//we know h1(k) will already be occupied at this point
			while (table[currIndex] != NULL) {
				currIndex = (hashNum + stepsize*multiplier) % m; 
				multiplier++; 
			}
			//we have found an open spot 
			//Insert it
			table[currIndex] = new pair<string, int>(k, 1);
			return; 
		}
	}
	else {
		//the index is already free, so we can just insert it 	
		table[hashNum] = new pair<string, int>(k, 1);
		return; 
	} 
}

int HashTable::count(string k) {
	//we need to check if k is in the hash table 
	for (int i = 0; i < m; i++) {
		//check each index for the string 
		if (table[i]->first == k) {
			//we have found it so just return its value 
			return table[i]->second; 
		}
	}
	return 0; 
}

void HashTable::reportAll(ostream& ofile) const {
	//output every key value pair to an ostream in the order they appear in the hash table 
	for (int i = 0; i < m; i++) {
		if (table[i] != NULL) {
			//cout << table[i]->first << " " << table[i]->second << endl; 
			ofile << table[i]->first << " " << table[i]->second << endl; 
		}
	}
}

void HashTable::resize() {

	//first need to create a new HashTable

	primeNumberIndex++; 
	vector<string> oldWords; 
	vector<int> oldNums; 
	std::pair<string, int>** oldTable = table; 
	int oldM = m; 
	m = primeNumbers[primeNumberIndex]; 
	table = new pair<string, int>*[primeNumbers[primeNumberIndex]]; 
	numKeys = 0; 
	
	for (int i = 0; i < oldM; i++) {
		if (oldTable[i] != NULL) {
			oldWords.push_back(oldTable[i]->first); 
			oldNums.push_back(oldTable[i]->second); 
			numKeys++; 
		}
	}

	//Now we need to rehash all the words and put them in the new table
	//initialize new Table to have NULL pointers
	for (int i = 0; i < m; i++) {
		table[i] = NULL; 
	}
	for (unsigned int i = 0; i < oldWords.size(); i++) {
		int numToInsert = oldNums[i]; 
		if (numToInsert > 1) {
			//cout << oldWords[i] << endl; 
			for (int j = 0; j < numToInsert-1; j++) {
				add(oldWords[i]); 
				
			}

		}
		add(oldWords[i]);  

	}

}

//hash function 
int HashTable::hash(string k) const {

	//First, we need to translate each letter into a value between 0 and 25
	unsigned long long int stringVal = 0; 
	int exponent = 0; 
	unsigned long long int arr[4]; 

	//Run the calculation and put the values into an array 
	if (k.length() > 6) {
		//determine how many times the loop will need to run 
		int counter = k.length() / 6; 
		unsigned int count = 0; 
		//cout << "counter " << counter << endl; 
		for (int i = counter; i >= 0; i--) {
			unsigned int n = k.length() - 6; 
			//cout << "n" << " " << n << endl; 
			for (unsigned int j = k.length() - 1; j >= n && j >= 0; j--) {
				count++; 
				char curr = k[i]; 
				int charI = (int)curr; 
				//i is the number for the character in the string 
				stringVal += (charI * pow(26, exponent)); 
				exponent++; 
				//break out of the loop 
				if (count == k.length()) {
					break; 
				}
			}
			//Now we need to insert it into the array 
			arr[i] = stringVal; 
			stringVal = 0; 
			n -= 6; 
		}
		
	}
	//otherwise the string length is less than 6
	else {
		//we need to perform the calculation once and put it into the last index of the array
		for (int i = k.length()-1; i >= 0; i--) {
			char curr = k[i]; 
			int charI = (int)curr; 
			stringVal += (charI * pow(26, exponent)); 
			exponent++; 
		}
		arr[4] = stringVal; 
		//need to fill the rest of the array with zeros
		for (int i = 0; i < 4; i++) {
			arr[i] = 0; 
		}
	}
	if (debugger == false) {
		//generate five random numbers between 0 and m-1 inclusive and set r values
		unsigned long long int hashVal = ((arr[0]*r1) + (arr[1]*r2) + (arr[2]*r3) + (arr[3]*r4) + (arr[4]*r5)) % m; 
		return hashVal; 
	}
	else {
		//debug-mode hashtable 
		//Now that we have what we need, we can hash the word
		unsigned long long int hashVal = ((arr[0]*v1) + (arr[1]*v2) + (arr[2]*v3) + (arr[3]*v4) + (arr[4]*v5)) % m; 
		return hashVal; 
	}
}

int HashTable::h(string w) const {

	//Much of the code will be similar to the last hash function (getting the w values)

	//First, we need to translate each letter into a value between 0 and 25
	unsigned long long int stringVal = 0; 
	int exponent = 0; 
	int arr[4]; 

	//Run the calculation and put the values into an array 
	if (w.length() > 6) {
		//determine how many times the loop will need to run 
		int counter = w.length() / 6; 
		unsigned int count = 0; 
		for (int i = counter; i >= 0; i--) {
			unsigned int n = w.length() - 6; 
			
			for (unsigned int j = w.length() - 1; j >= n && j >= 0; j--) {
				count++; 
				char curr = w[i]; 
				int charI = (int)curr; 
				//i is the number for the character in the string 
				stringVal += (charI * pow(26, exponent)); 
				//cout << stringVal << endl; 
				exponent++; 
				//break out of the loop 
				if (count == w.length()) {
					break; 
				}
			}
			//Now we need to insert it into the array 
			arr[i] = stringVal; 
			stringVal = 0; 
			n -= 6; 
		}
		
	}
	//otherwise the string length is less than 6
	else {
		//we need to perform the calculation once and put it into the last index of the array
		for (int i = w.length()-1; i >= 0; i--) {
			char curr = w[i]; 
			int charI = (int)curr; 
			stringVal += (charI * pow(26, exponent)); 
			exponent++; 
		}
		arr[4] = stringVal; 
		//need to fill the rest of the array with zeros
		for (int i = 0; i < 4; i++) {
			arr[i] = 0; 
		}
	}

	//use primeNumberIndex as the placeholder for which value of p we will use
	int p = sizes[primeNumberIndex]; 
	long long int sum = 0; 
	for (int i = 0; i < 4; i++) {
		sum += arr[i]; 
	}
	int h = p - ((sum) % p); 
	return h; 
}

void HashTable::setDebug(bool x) {
	debugger = x; 
}

void HashTable::setProbe(int y) {
	probe = y; 
}

int HashTable::findVal(string k) {
	//find the value that a string will be inserted at
	int hashNum = hash(k); 

	if (table[hashNum] != NULL) {
		//there is already an element in this index, so we can probe it
		if (probe == 0) {
			//linear probing
			hashNum++; 
			while (table[hashNum] == NULL) {
				hashNum++; 
				hashNum %= m; 
				//account for wrapping around 
			}
			return hashNum; 
		}
		else if (probe == 1) {
			//quadratic probing 
			hashNum++; 
			int counter = 1; 
			int quadratic = pow(counter, 2); 
			int spacer = (hashNum + quadratic) % m; 
			while (table[spacer] == NULL) {
				counter++; 
				quadratic = pow(counter, 2); 
				spacer = (hashNum + quadratic) % m; 
			}
			return hashNum; 
		}
		else {
			//double hashing
			int stepsize = h(k); 
			int multiplier = 1; 
			int currIndex = hashNum; 
			//we know h1(k) will already be occupied at this point
			while (table[(hashNum + stepsize*multiplier) % m] == NULL) {
				currIndex = (hashNum + stepsize*multiplier) % m; 
				multiplier++; 
			}
			return currIndex; 
		}
	}
	else {
		return hashNum; 
	} 
	
}




