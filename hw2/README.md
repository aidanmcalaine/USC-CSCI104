Aidan McAlaine 
19 February 2021 

In this programming assignment, I worked to model a simplified version of an online retail system (Amazon). Essentially, I worked to create code that would read in a database of products from certain categories as well as users and their information. The program allows a user to search for products, add them to their carts, view their carts, and buy them. 

First, I implemented functions that would allow for the implementation of AND and OR in the search. I created the setIntersection and setUnion functions to do this. These functions continuously either interesected or unioned with themselves to return the appropriate list of corresponding products. In the implementation of these functions, I ensured that they were not running in O(n^2). 

After that, I wrote derived product classes to handle the various types of products that the user would be able to add to their cart. There were three: Book, Clothing, and Movie. Each of these classes supported a few functions, and were similarly written. 

I found that the most daunting part of this assignment was in the implementation of a Derived DataStore class called MyDataStore. This class contained the functions that would actually allow the user to search the database, add products, view their cart and buy the items inside of it. This class took me the longest by far. After completing it, I was able to quickly implement amazon.cpp, which already had good skeleton code laid out. 
