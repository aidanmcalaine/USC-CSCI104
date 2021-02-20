//
//  clothing.hpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//
#ifndef clothing_hpp
#define clothing_hpp
#include <iostream>
#include "product.h"
#include <stdio.h>
#include <string>

class Clothing : public Product {
public:
    
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    
    //Pure virtual prototypes
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    //Destructor
    ~Clothing();

protected:
    std::string size_;
    std::string brand_;
};
#endif /* clothing_hpp */

