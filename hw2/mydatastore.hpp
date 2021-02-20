#ifndef mydatastore_hpp
#define mydatastore_hpp
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <string>
#include <array>
#include <queue>

using namespace std;

class MyDataStore : public DataStore {
public:
   
    //constructor
    MyDataStore();
    //destructor
    ~MyDataStore();
    //member functions
    void addProduct(Product* p);
    void addUser(User* u);
    vector <Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    
    //Additional Functions
    //add to cart
    void addToCart(std::string user, Product* p);
    //view cart
    void viewCart(std::string user);
    //buy cart 
    void buyCart(std::string user);
    
private:
    //Data structures
    //map username to vector of products
    map<string, vector<Product*>> userCarts;
    //map username to their user data
    map<string, User*> userData;
    //vector for all the products
    set<Product*> allProducts;
    //map keywords to the products
    map<string, set<Product*>> keyMap;
   
}; 
#endif
