//
//  mydatastore.cpp
//  
//
//  Created by Aidan McAlaine on 2/17/21.
//
#include "mydatastore.hpp"
#include "util.h"
#include "datastore.h"
#include <string>
#include <set>
#include <vector>
#include <stdio.h>
#include <map>
#include "product.h"
#include "user.h"
using namespace std;

//Constructor
MyDataStore::MyDataStore() {
}

//Destructor
MyDataStore::~MyDataStore() {
    //need to delete the dynamically allocated users and products
    for (set<Product*>::iterator it = allProducts.begin(); it != allProducts.end(); ++it) {
        delete (*it);
    }
    for (map<string, User*>::iterator it = userData.begin(); it != userData.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    //create a set for the p keywords
    set<string> key = p->keywords();
    //add the product to the allProducts vector for later use
    allProducts.insert(p);
    //iterate through
    for (set<string>::iterator it = key.begin(); it != key.end();++it) {
        string term = (*it);
        transform(term.begin(), term.end(), term.begin(), ::tolower);
        //if it is in there, insert it into the map
        if (keyMap.find(term) != keyMap.end()) {
            keyMap[term].insert(p);
        }
        else {
            //key does not exist
            //create a new set and push back the item
            keyMap[term] = set<Product*>();
            keyMap[term].insert(p);
        }
    }
}
    
void MyDataStore::addUser(User* u) {
    //create a string for the user name
    //add the user to the userData
    string name = u->getName();
    userData[name] = u; 
}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    //create a set for our terms
    set<Product*> keySet = keyMap[terms[0]];
    //iterate through
    for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        if (keyMap.find(*it) != keyMap.end()) {
            //if the type is 0, we have an intersection
            if (type == 0) {
                //continually intersect the set
                keySet = setIntersection(keyMap[*it], keySet);
            }
            //if type is 1, it is a union
            else {
                //continually union the set
                keySet = setUnion(keyMap[*it], keySet);
            }
        }
    }
    //we need to change the set to a vector and return it
    vector<Product*> returnedSet;
    returnedSet.assign(keySet.begin(), keySet.end());
    return returnedSet;
}
    
void MyDataStore::dump(ostream& ofile) {
    
    //loop through the products and dump them
    //create header for products
    ofile << "<products>" << endl;
    for (set<Product*>::iterator it = allProducts.begin(); it != allProducts.end(); ++it) {
        //dump the products into the output file
        (*it) -> dump(ofile);
    }
    //create the footer for products
    ofile << "</products>" << endl;
    
    //loop through the users and dump them
    //create header for users
    ofile << "<users>" << endl;
    for(map<string, User*>::iterator it = userData.begin(); it != userData.end(); ++it) {
        //dump the users into the output file
        it -> second -> dump(ofile);
    }
    //create the footer for users
    ofile << "</users>"; 
}
    
void MyDataStore::addToCart(string user, Product* p) {
    //if the user is not in the database, we cannot add the product to their cart
    if (userData.find(user) == userData.end()) {
        cout << "Invalid Username" << endl;
        return;
    }
    //add the product to the user's cart
    userCarts[user].push_back(p);
}

void MyDataStore::viewCart(string user) {
    //check to see if the user is in the database
    if (userCarts.find(user) != userCarts.end()) {
        int counter = 1;
        for (vector<Product*>::iterator it = userCarts[user].begin(); it !=userCarts[user].end(); ++it) {
            //iterate through the items in the cart and print them out
            cout << "Item " << counter++ << endl;
            cout << (*it)-> displayString() << endl;
        }
    }
    else {
        //if the user does not exist, print out this line 
        cout << "Invalid Username" << endl;
    }
}

void MyDataStore::buyCart(string user) {
    //check to see if the user is in the database
    if (userCarts.find(user) != userCarts.end()) {
        //the user exists
        for (vector<Product*>::iterator it = userCarts[user].begin(); it != userCarts[user].end();) {
            //iterate through the items in the cart for purchase
            if ((*it)->getQty() >= 1 && userData[user]->getBalance() >= (*it)->getPrice()) {
                //there is an item available purchase and the user has enough money to cover the price
                //Buy the item:
                //Subtract 1 quantity
                (*it)->subtractQty(1);
                //deduce the amount from the user's balance
                userData[user]->deductAmount((*it)->getPrice());
                //remove the item from the cart
                userCarts[user].erase(it);
            }
            else {
                ++it;
            }
        }
    }
    else {
        cout << "Invalid Username" << endl;
    }
}
