//
//  book.cpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//
#include <iostream>
#include <sstream>
#include "book.hpp"
#include "util.h"
#include "product.h"
#include <string>
using namespace std;

//Constructor
Book::Book(const std::string category, const std::string name, double price, int qty, string isbn, string author):
    //call the Product class
Product(category, name, price, qty) {
    //set data members
    isbn_ = isbn;
    author_ = author;
}

//Destructor
Book::~Book() {
}

//Function Implementations
std::set<std::string> Book::keywords() const {
    //returns a set of keywords
    set<string> bookKeywords;
    //put in author and ISBN
    bookKeywords = parseStringToWords(name_);
    bookKeywords.insert(isbn_);
    //create a new set for the author
    set<string> authorKeywords;
    authorKeywords = parseStringToWords(author_);
    //insert the author keywords into book keywords
    bookKeywords.insert(authorKeywords.begin(), authorKeywords.end());
    //return the set
    return bookKeywords;
}

std::string Book::displayString() const {
    string word = "";
    //add the name
    word = word + name_;
    //add the line break
    word = word + "\n";
    //add line two
    word = word + "Author: " + author_ + " ISBN: " + isbn_;
    //add the line break
    word = word + "\n";
    //add the final line
    word = word + to_string(price_) + " " + to_string(qty_) + " left.";
    //return word
    return word;
}
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
