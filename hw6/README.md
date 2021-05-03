Aidan McAlaine
Hw6 Analysis 

Summary: 

For this homework assignment, I wrote the implementation for a hash table that could use linear probing, quadratic probing, or double hashing to handle collisions based on the command line arguments. I also wrote code to allow the user to store the data in the STL map as an alternative. As a whole, the program takes in a 

Question Responses: 

1. 
I used varying sizes for my input cases, but for the purposes of this analysis, I used the first 1000 lines of the text of Hamlet, which gives an input size of 6796. 

2. 
I used the STL map for the fourth option.

3. 
For the four approaches: (non debug mode, 1 repetition)
Linear Probing: 0.2944 seconds
Quadratic Probing: 0.2939 seconds
Double Hashing: 0.2954 seconds
STL map: 0.0046 seconds 

Time per operation: 
Linear Probing: 4.33202e-05 seconds
Quadratic Probing: 4.32487e-05 seconds
Double Hashing: 4.34713e-05 seconds
STL map: 6.74956e-07 seconds

4. 
I was definitely a bit surprised by my results- I expected there to be more of a difference between linear and quadratic probing, and I also expected double hashing to be faster than both linear and quadratic probing- which it was not. I was also surprised to see that the operations on the STL map were significantly faster- I think this is because the map did not need to keep track of a loading factor, and thus did not need to resize when the loading factor exceeds 0.5. I think that with a larger input size, the difference between linear and quadratic probing would grow, and I think double hashing would near the same level as quadratic probing. 