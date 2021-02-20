//
//  movie.hpp
//  
//
//  Created by Aidan McAlaine on 2/15/21.
//

#ifndef movie_hpp
#define movie_hpp
#include <iostream>
#include "product.h"
#include <stdio.h>
#include <string>

class Movie : public Product {
public:
    
    //Constructor
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    
    //Pure virtual prototypes
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    
    //Destructor
    ~Movie();

protected:
    std::string genre_;
    std::string rating_;
};

#endif /* movie_hpp */
