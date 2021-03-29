#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
//typedef std::map<int, Rectangle> InputMapType;
//typedef std::map<int, std::pair<int, int> > OutputMapType;
typedef AVLTree<int, Rectangle> InputMapType; 
typedef AVLTree<int, std::pair<int, int> > OutputMapType; 

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}

//HELPER FUNCTIONS 

//Helper function: Overlap
//Test if two files placed on the floor overlap 
bool overlap(const Rectangle& rec, int recx1, int recy1, vector<vector<bool>>& grid) {

    //First check to see if we are placing in a valid grid space
    if (n < rec.length + recx1 || m < rec.height + recy1) {
        //bad location 
        return true; 
    }
    //Now check for overlap 
    for (int i = recx1; i < recx1 + rec.length; i++) {
        for (int j = recy1; j < recy1 + rec.height; j++) {
            if (grid[i][j]) {
                //if there is any place where it is true, then the other rectangle is present
                return true; 
            }
        }
    }
    return false; 
}

// //Helper function: insert 
// void insert (const Rectangle& rec, vector<vector<bool>>& grid, int row, int col, OutputMapType op) {
//     //iterate from the current location to the size dimensions of the rectangle to be added
//     for (int i = row; i < row + rec.length; i++) {
//         for (int j = col; j < rec.height; j++) {
//             //insert the rectangle into the grid 
//             grid[i][j] = true; 
//         }
//     }
//     //find the rectangle id 
//     op.find(rec.ID)->second = std::make_pair(row, col); 

// }

// //Helper function: remove 
// void remove(const Rectangle& rec, vector<vector<bool>>& grid, int row, int col) {
//     for (int i = row; i < row + rec.length; i++) {
//         for (int j = col; j < col + rec.height; j++) {
//             grid[i][j] = false; 
//         }
//     }
// }

void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}



// TODO: Write your backtracking search function here
//Algorithm 
//use a for loop iterating through the spaces on a grid
//place the first rectangle in a given spot 
//move through the grid, calling overlap to try to find a place for the second rectangle 
    //if it initially doesn't work, rotate it and check again 

bool solver(vector<vector<bool>>& grid, int x1, int y1, InputMapType::iterator it,
    InputMapType& input, OutputMapType& output) {

    //Base case 1
    //we have iterated through the map correctly 
    if (it == input.end()) { 
        return true; 
    }

    //Base case 2
    if (grid[x1][y1]) {
        return solver(grid, x1, y1+1, it, input, output); 
    }

    //Base case 3
    //Ensure the dimensions are correct 
    if (x1 == m) return false; 
    if (y1 == n) {
        y1 = 0; 
        x1++; 
    }

    //Recursive Case
    else {
        for (int i = x1; i < m; i++) {
            for (int j = y1; j < n; j++) {
                //Check to make sure there's no overlap 
                if (!overlap(it->second, i, j, grid)) {

                    //Flip the tiles, effectively inserting it  
                    flip(i, j, it->second, grid); 

                    //Insert the rectangle into the output map 
                    output.insert(std::make_pair(it->second.ID, std::make_pair(i, j)));

                    //Attempt to insert the rectangle 
                    InputMapType::iterator n = it; 
                    ++n; 
                    //Place the second rectangle 
                    if (solver(grid, 0, 0, n, input, output)) {
                        //We have successfully placed both rectangles 
                        return true; 
                    }
                    //Backtrack 
                    flip(i, j, it->second, grid); 
                    //output.erase(it->second.ID); 
                    output.remove(it->second.ID); 
                    
                }

                //rotate the rectangle and try again 
                int tempLength = it->second.length; 
                it->second.length = it->second.height; 
                it->second.height = tempLength; 

                //Effectively the same code as before, but with a rotated rectangle
                //Check to make sure there's no overlap 
                if (!overlap(it->second, i, j, grid)) {

                    //Flip the tiles, effectively inserting it
                    flip(i, j, it->second, grid); 

                    //Insert the rectangle into the output map 
                    output.insert(std::make_pair(it->second.ID, std::make_pair(i, j))); 
                    
                    //Attempt to insert the rectangle 
                    InputMapType::iterator n = it; 
                    ++n; 
                    //Place the second rectangle 
                    if (solver(grid, 0, 0, n, input, output)) {
                        //We have successfully placed both rectangles 
                        return true; 
                    }
                    //Backtrack 
                    flip(i, j, it->second, grid); 
                    //output.erase(it->second.ID); 
                    output.remove(it->second.ID); 
                    
                }

                //rotate the rectangle again 
                tempLength = it->second.length; 
                it->second.length = it->second.height; 
                it->second.height = tempLength; 
            }
        }
    }
    //There are no solutions 
    return false; 
}



int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;
    // TODO:  Call your backtracking search function here
    // std::cout << "n " << n << " m " << m << std::endl; 
    solution_exists = solver(grid, 0, 0, it, input, output); 
    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}