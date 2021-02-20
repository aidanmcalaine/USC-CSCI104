//
//  movie.cpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//
#include <iostream>
#include <sstream>
#include <string>
#include "movie.hpp"
#include "util.h"
#include "product.h"

using namespace std;

//Constructor
Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) :
    //call the Product class
Product(category, name, price, qty) {
    //set data members
    genre_ = genre;
    rating_ = rating;
}

//Destructor
Movie::~Movie() {
}

//Function Implementations
std::set<std::string> Movie::keywords() const {
    //returns a set of keywords
    set<string> movieKeywords;
    //put in author and ISBN
    movieKeywords = parseStringToWords(name_);
    //create a new set for the author
    set<string> genreKeywords;
    genreKeywords = parseStringToWords(genre_);
    //insert the author keywords into book keywords
    movieKeywords.insert(genreKeywords.begin(), genreKeywords.end());
    //return the set
    return movieKeywords;
}

std::string Movie::displayString() const {
    string word = "";
    //add the name
    word = word + name_;
    //add the line break
    word = word + "\n";
    //add line two
    word = word + "Genre: " + genre_ + " Rating: " + rating_;
    //add the line break
    word = word + "\n";
    //add the final line
    word = word + to_string(price_) + " " + to_string(qty_) + " left.";
    //return word
    return word;
}
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}
