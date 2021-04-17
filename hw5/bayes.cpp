//Aidan McAlaine 
//hw5
#include <vector>
#include <map> 
#include <set>
#include <list>
#include <iostream> 
#include <string>
#include <fstream> 
#include <sstream> 

using namespace std; 

//calculator function 
void calculator(map<string, map<string, int>>& fruitAttributes, map<string, int>& fruitCount, map<int, set<string>>& classifiers, 
	int& numFruits, vector<string>& finalFruits) {
	
	//Necessary data for later comparisons 
	double totalFruit = (double)numFruits; 
	map<int, map<string, double>> probabilityMap; 

	//need to iterate through the map so we can compare the probabilities against each other 
	for (map<string, int>::iterator it = fruitCount.begin(); it!= fruitCount.end(); ++it) {

		int lineCounter = 0;

		//iterate through the criteria set 
		for (map<int, set<string>>::iterator it_ = classifiers.begin(); it_ != classifiers.end(); ++it_) {
			
			//increment the line number
			lineCounter++; 

			//For calculating the numerator/denominator of each fruit 
			list<double> numerator; 
			list<double> denominator; 

			//Calculate the numerator/denominator 

			for (set<string>::iterator it1 = it_->second.begin(); it1 != it_->second.end(); ++it1) {
				
				//Handle the denominator calculation 
				double occ_ = 0.0; 
				for (map<string, int>::iterator it2 = fruitCount.begin(); it2 != fruitCount.end(); ++it2) {
					//Add the the other trais up except for the one previously calculated
					if (it2 != it) {
						//add it 
						occ_ += fruitAttributes[it2->first][*it1]; 
					}
				}

				//account for Laplacian smoothing: add 1.0
				occ_ += 1.0; 

				//Numerator calculation 

				//Laplacian smoothing incorporated 
				double occ = fruitAttributes[it->first][*it1]; 
				occ += 1.0;  
				double num = it->second; 
				num += 1.0; 

				//Calculate the probability of the denominator 
				double a = totalFruit - it->second + 1.0; 

				//Calculate an arbitrary trait and push it back 
				numerator.push_back((occ/num)); 
				denominator.push_back(occ_/a); 
			}

			//BAYES CALCULATION

			//calculate the probability of the individual fruit 
			double fruit = it->second/totalFruit; 
			//calculate the probability of not the individual fruit 
			double notFruit = 1 - fruit; 

			//Calculation

			//take the first numerator/denominator in the vectors 
			double m = numerator.front();  
			double n = denominator.front(); 

			list<double>::iterator listIt; 
			for (listIt = numerator.begin(); listIt != numerator.end(); ++listIt) {
				m *= (*listIt); 
			}
			list<double>::iterator listIt2; 
			for (listIt2 = denominator.begin(); listIt2 != denominator.end(); ++listIt2) {
				n *= (*listIt2); 
			}

			//Bayes Theorem!
			double finalProb = (m*fruit)/((m*fruit)+(n*notFruit)); 
			//Now insert this into our probability map for later checking 
			probabilityMap[lineCounter].insert(pair<string, double>(it->first, finalProb));	 
		}
	}

	//Use the probabilityMap to compare probabilities per line
	//This is where we will actually find the most probable fruit 
	for (map<int, map<string, double>>::iterator it3 = probabilityMap.begin(); it3 != probabilityMap.end(); ++it3) {
		string givenFruit; 
		double maxValue = 0; 
		for (map<string, double>::iterator it4 = it3->second.begin(); it4 != it3->second.end(); ++it4) {
			//iterate through the fruit, probability (key value pair) and find the fruit with the largest probability 
			if (it4->second > maxValue) {
				givenFruit = it4->first;  
				maxValue = it4->second; 
			}
		}

		//Once we have the max fruit and its paired probability, we can push them back in the appropriate structure
		finalFruits.push_back(givenFruit); 
	}
}

int main(int argc, char* argv[]) {

	//Necessary data structures

	//map from a fruit to a map from characteristic to occurences 
	map<string, map<string, int>> fruitAttributes; 
	//map from a fruit to the number of that fruit 
	map<string, int> fruitCount; 
	//map from the line number in classify to the attributes listed 
	map<int, set<string>> classifiers; 
	//vector to hold the fruits we predict - we will use this for the output file 
	vector<string> finalFruits; 

	//read in train.txt and get the data into the map
	ifstream inFile; 
	//open the file 
	inFile.open(argv[1]); 
	//Make sure it did not fail 
	if (inFile.fail()) {
		cout << "Unable to open train.txt." << endl; 
		return 0; 
	}

	//take in the first line from train.txt
	int numFruits; 
	inFile >> numFruits; 

	int counter = 0; 
	string line; 
	while (counter < numFruits) {

		//read in the first line: the fruit 
		string first; 
		inFile >> first; 

		//Insert the fruit into our fruitCount map 
		if (fruitCount.find(first) != fruitCount.end()) {
			//the fruit is already in the map, so we can just increment its value 
			fruitCount[first]++; 
		}
		else {
			//we need to actually insert the fruit into the fruitCount map
			//insert 1 because this will be the first occurence of the fruit 
			fruitCount.insert(pair<string, int>(first, 1)); 
		}

		//now we need to handle the other map, so we can get the entire line 
		getline(inFile, line); 
		stringstream temp(line); 
		string contents; 

		//Handle duplicates of the same attribute by using a set: 
		set<string> wordList; 

		//While there are still words on the line, insert them into the set
		while (temp >> contents) {
			wordList.insert(contents); 
		}

		//Now iterate through the set and add them to our fruitAttributes map 
		for (set<string>::iterator fruitIt = wordList.begin(); fruitIt != wordList.end(); ++fruitIt) {
			if (fruitAttributes[first].find(*fruitIt) != fruitAttributes[first].end()) {
				//the fruit is already in the map
				//Check if the characteristic is already in the map 
				if (fruitAttributes[first].find(*fruitIt) != fruitAttributes[first].end()) {
					//the characteristic is in the map, so just increment its number
					fruitAttributes[first][*fruitIt]++; 
				}
				else {
					//we need to insert the characteristic 
					fruitAttributes[first].insert(pair<string, int>(*fruitIt, 1)); 
				}
			}
			else {
				//the fruit is not in the map, so we need to insert the fruit and the attributes
				fruitAttributes[first].insert(pair<string, int>(*fruitIt, 1)); 
			}
		}
		counter++; 
	}
	

	//iterate through classify.txt to get the data 

	//read in classify.txt and get the data into a new map 
	ifstream inFile_; 
	//open the file 
	inFile_.open(argv[2]); 
	//make sure the file did not fail 
	if (inFile_.fail()) {
		cout << "Unable to open classify.txt" << endl; 
		return 0; 
	}
	//take in the first line from classify.txt
	int numClassifiers; 
	inFile_ >> numClassifiers; 
	//get rid of the remainder of the first line 
	string x; 
	getline(inFile_, x); 

	//iterate through the rest of classify.txt to get all of the data input 
	int countClassifiers = 1; 
	string line_; 
	while (countClassifiers <= numClassifiers) {
		//get the line from the arbitrary classify line 
		getline(inFile_, line_); 
		stringstream temp(line_); 
		string contents_; 
		
		//While there are still words left 
		while (temp >> contents_) {

			//Insert the words into our set (duplicates will be handled)  
			classifiers[countClassifiers].insert(contents_); 
		}
		countClassifiers++; 
	}

	//call our bayes calculator function 
	calculator(fruitAttributes, fruitCount, classifiers, numFruits, finalFruits); 

	//Need to handle the output file:  
	ofstream outputFile; 
	outputFile.open(argv[3]);
	if (outputFile.fail()) {
		cout << "Unable to open output file" << endl; 
		return 0; 
	} 
	//Iterate through the final fruits vector 
	for (unsigned int i = 0; i < finalFruits.size(); i++) {
		//Insert our predictions into the output file 
		outputFile << finalFruits[i] << endl; 
	}

	//close the files 
	inFile.close(); 
	inFile_.close(); 
	outputFile.close(); 

}





