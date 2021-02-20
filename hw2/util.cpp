#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    
    //create the set of words to be returned and a holder string
    set<string> returnedWords;
    string word = "";
    
    //check to make sure the length is greater than 2
    if (rawWords.size() < 2) {
        //no possible keywords - return empty set
        return returnedWords;
    }
    
    //iterate through the string and break up the words with substring, placing them in the set
    
    for (unsigned int i = 0; i < rawWords.size(); i++) {
        if (isalpha(rawWords[i])) {
            //if it is a letter, add it to our holder
            word = word + rawWords[i];
        }
        else {
            //not a letter, we've reached a delimiter
            //check to see if our current word can be added
            if (word.size() >= 2) {
                //greater than 2 characters so we can add it
                returnedWords.insert(word);
            }
            word = "";
        }
    }
    return returnedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
