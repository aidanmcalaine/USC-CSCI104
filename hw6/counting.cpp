//Aidan McAlaine 
//Hw6
#include "HashTable.h"
#include "HashTable.cpp"
#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <map> 
#include <string>
#include <cstdlib>
using namespace std; 

int main(int argc, char* argv[]) {
	
	clock_t start; 
	double duration; 
	//first create the hash table
	HashTable ht = new HashTable(false, 0); 
	map<string, int> mapper; 

	// //input file at 1, output file at 2, x at 3, d at 4, r at 5

	// set the x value for probing 
	int n = atoi(argv[3]); 
	ht.setProbe(n);

	// //set the debug value 
	if (argv[4]) {
		ht.setDebug(true); 
	}   

	//set the r value 
	int n2 = atoi(argv[5]); 
	int r = n2; 

	//open the input file 
	ifstream ifile; 
	ifile.open(argv[1]); 
	if (ifile.fail()) {
		std::cout << "Unable to open the input file" << std::endl; 
		return 0; 
	}
	string word;
	vector<string> prunedWords; 

	//Need to get each word by word, strip the word, then hash it
	while (ifile >> word) {
		//For each word, we need to strip it and put it in lowercase
		for (int i = 0, len = word.size(); i < len; i++) {
			if (ispunct(word[i])) {
				word.erase(i--, 1); 
				len = word.size(); 
			}

		}
		//put the entire word in lowercase
		transform(word.begin(), word.end(), word.begin(), ::tolower); 
		
		//put the pruned words into a vector of strings
		prunedWords.push_back(word); 
		
	}

	//start the timing
	start = clock(); 
	//Insert all of the words 
	if (n == 3) {
		//avl trees
		//check if its already in there - if it is, increment the value 
		//otherwise just insert it into the map with a value of 1
		for (int i = 0; i < r; i++) {
			for (unsigned int j = 0; j < prunedWords.size(); j++) {
				map<string, int>::iterator it; 
				//see if the current word is in the map 
				it = mapper.find(prunedWords[j]); 
				if (it == mapper.end()) {
					mapper.insert(pair<string, int>(prunedWords[j], 1)); 
				}
				else {
					it->second++; 
				}
			}
		}
		

	}
	else {
		for (int i = 0; i < r; i++) {
			for (unsigned int i = 0; i < prunedWords.size(); i++) {
				ht.add(prunedWords[i]); 
			}
		}
	}
	
	//Repeat with stl map 

	duration = (clock() - start) / (double) CLOCKS_PER_SEC; 
	//use two duration variables 

	double timePerCycle = duration / r; 
	double timePerOperation = timePerCycle / prunedWords.size(); 
	//formatting for output file: 
	ofstream ofile; 
	ofile.open(argv[2]); 
	ofile << "Hash Table Analysis"; 
	ofile << endl; 
	if (n == 0) {
		ofile << "Linear Probing" << endl; 
	}
	else if (n == 1) {
		ofile << "Quadratic Probing" << endl; 
	}
	else if (n == 2) {
		ofile << "Double Hashing" << endl; 
	}
	else {
		//n = 3
		ofile << "AVL Trees" << endl; 
	}
	ofile << "Size Of Input Cases " << prunedWords.size()*r << endl; 
	ofile << "Total R Cycles Took: " << duration << " seconds" << endl; 
	ofile << "Average Time It Took For One Cycle: " << timePerCycle << " seconds" << endl; 
	ofile << "Runtime Per Single Operation: " << timePerOperation << " seconds" << endl;
	ofile << endl; 

	if (n == 3) {
		map<string, int>::iterator it; 
		for (it = mapper.begin(); it != mapper.end(); ++it) {
			ofile << it->first << " " << it->second << endl; 
		}
	}
	else {
		ht.reportAll(ofile);  
	}
	
	ofile.close(); 

	std::cout << duration/r << endl; 

	return 0; 
}