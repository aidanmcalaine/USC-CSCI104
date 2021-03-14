#include <map> 
#include <set>
#include <vector> 
#include <string> 
#include <iostream> 
#include <fstream>
#include <sstream> 

using namespace std; 

//Function Prototypes 
bool isValid(map<char, int> colorList, map<char, set<char>> adj_list, char currLetter);
bool color(map<char, set<char>> adj_list, vector<char> countryList, int location); 
//Data Structures 
map<char, set<char>> adj_list; 
map<char, int> colorList; 
vector<char> countryList; 

//main function 
int main(int argc, char* argv[]) {

	//necessary data members
	int rows; 
	int cols; 
	int countries; 

	//create the empty map - max of 80 x 80
	char countryMap[80][80]; 
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			countryMap[i][j] = ' '; 
		}
	}

	//read in the characters to the map 
	ifstream iFile; 
	//open the file 
	iFile.open(argv[1]); 
	if (iFile.fail()) {
		cout << "Could not open the file." << endl; 
		return 1; 
	}

	//take the input into the variables, eliminating white space 
	iFile >> ws >> countries >> ws >> rows >> ws >> cols; 

	//fill up the countryMap with the appropriate map 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			char countryLetter; 
			iFile >> countryLetter; 
			countryMap[i][j] = countryLetter; 
		}
	}
	
	//Create the adjacency matrix 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			//check edge cases
			char top, right, bottom, left; 
			
			//top edge
			if (i == 0) top = ' '; 
			else top = countryMap[i-1][j];

			//right edge
			if (j >= cols) right = ' '; 
			else right = countryMap[i][j+1];

			//bottom edge
			if (i >= rows) bottom = ' '; 
			else bottom = countryMap[i+1][j];

			//left edge
			if (j == 0) left = ' ';
			else left = countryMap[i][j-1]; 
			
			//create the adjacency matrix 
			char currLetter = countryMap[i][j]; 

			//check if the current letter is not in the map: 
			map<char, set<char>>::iterator it = adj_list.find(currLetter); 
			
			if (it == adj_list.end()) {
				adj_list[countryMap[i][j]].insert(' '); 
			}
			//check the top, right, bottom, and left locations
			if (top != countryMap[i][j] && top != ' ') {
				//we have found a different country, add it to adj_list
				adj_list[currLetter].insert(top); 
			}
			if (right != countryMap[i][j] && right != ' ') {
				//we have found a different country, add it to adj_list
				adj_list[currLetter].insert(right);  
			}
			if (bottom != countryMap[i][j] && bottom != ' ') {
				//we have found a different country, add it to adj_list
				adj_list[currLetter].insert(bottom);  
			}
			if (left != countryMap[i][j] && left != ' ') {
				//we have found a different country, add it to adj_list
				adj_list[currLetter].insert(left); 
			}
			
			//Now create a map to assign a country to a certain int 
			map<char, int>::iterator it_ = colorList.find(currLetter); 
			if (it_ != colorList.end()) {
				continue; 
			}
			else {
				colorList[currLetter] = 0; 
				countryList.push_back(currLetter); 
			}

		}
	}
	// //Adjacency list test
	// for (map<char, set<char>>::iterator it = adj_list.begin(); it != adj_list.end(); ++it) {
	// 	cout << "Country: " << it->first << " borders: "; 
	// 	for (set<char>::iterator it1 = it->second.begin(); it1 != it->second.end(); ++it1) {
	// 		cout << *it1 << " "; 
	// 	}
	// 	cout << endl; 
	// }
	iFile.close(); 
	//call the color function to update colors 
	color(adj_list, countryList, 0); 
	//print the output
	for (map<char, int>::iterator it1 = colorList.begin(); it1 != colorList.end(); ++it1) {
		cout << it1->first << " " << it1->second << endl; 
	}
	//close the file 
}

//isValid function
bool isValid(map<char, int> colorList, map<char, set<char>> adj_list, char currLetter) {
	//iterate through the adjacency list at a given country
	set<char> adjacent = adj_list[currLetter]; 
	for (set<char>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
		//assign a temporary letter
		char temp = *it; 
		if (colorList[temp] == colorList[currLetter]) {
			return false; 
		}
	}
	return true; 
}

//color function - where recursion/backtracking occurs
bool color(map<char, set<char>> adj_list, vector<char> countryList, int location) {
	//base case
	unsigned int loc = location; 
	if (loc == colorList.size()) return true; 
	//recurse through the map
	//need four colors: 
	char curr = countryList[location]; 
	for (int i = 1; i <= 4; i++) {
		//color the current country 
		colorList[curr] = i; 
		if (isValid(colorList, adj_list, curr)) {
			//cout << location << endl; 
			//recurse
			if (color(adj_list, countryList, loc+1)) {
				//we have correctly colored the whole map 
				return true; 
			}
		}
		colorList[curr] = 0; 
	}
	//we failed to color the map
	return false; 
}


