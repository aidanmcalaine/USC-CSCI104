#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
using namespace std; 

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    //create intersection set
    set<T> intersection;
    //declare an iterator for the set
    typename set<T>::iterator it;
    
    //iterate through s1
    for (it = s1.begin(); it != s1.end(); ++it) {
        //check to see if the element is shared
        if (s2.find(*it) != s2.end()) {
            //the element is present in s2
            intersection.insert(*it);
        }
    }
    return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    //create union set
    set<T> unionSet;
    //declare an iterator for the set
    typename set<T>::iterator it;
    
    //iterate through s1 and add everything to union
    for (it = s1.begin(); it != s1.end(); ++it) {
        unionSet.insert(*it);
    }
    //iterate through s2 and add everything not in s1
    for (it = s2.begin(); it != s2.end(); ++it) {
        //if the element is not in union, add it
        if (unionSet.find(*it) == unionSet.end()) {
            //the element is not unionSet
            //add the element
            unionSet.insert(*it);
        }
    }
    return unionSet;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
