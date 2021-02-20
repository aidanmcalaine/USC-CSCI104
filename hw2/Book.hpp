//
//  book.hpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//
#ifndef book_hpp
#define book_hpp
#include <iostream>
#include "product.h"
#include <stdio.h>
#include <string>


class Book : public Product {
public:
    //Constructor
    Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
    
    //Pure virtual prototypes
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    //Destructor
    ~Book();

    
protected:
    std::string isbn_;
    std::string author_;
};

#endif /* book_hpp */
