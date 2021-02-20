//
//  clothing.cpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//
#include <iostream>
#include <sstream>
#include <string>
#include "clothing.hpp"
#include "util.h"
#include "product.h"

using namespace std;

//Constructor
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) :
    //call the Product class
Product(category, name, price, qty) {
    //set data members
    size_ = size;
    brand_ = brand;
}

//Destructor
Clothing::~Clothing() {
}

//Function Implementations
std::set<std::string> Clothing::keywords() const {
    //returns a set of keywords
    set<string> clothingKeywords;
    //put in author and ISBN
    clothingKeywords = parseStringToWords(name_);
    //create a set for brand
    set<string> brandKeywords;
    brandKeywords = parseStringToWords(brand_);
    clothingKeywords.insert(brandKeywords.begin(), brandKeywords.end());
    //return the set
    return clothingKeywords;
}

std::string Clothing::displayString() const {
    string word = "";
    //add the name
    word = word + name_;
    //add the line break
    word = word + "\n";
    //add line two
    word = word + "Size: " + size_ + " Brand: " + brand_;
    //add the line break
    word = word + "\n";
    //add the final line
    word = word + to_string(price_) + " " + to_string(qty_) + " left.";
    //return word
    return word;
}
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
