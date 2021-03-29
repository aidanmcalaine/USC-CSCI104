#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    bool isBalancedHelperFunc(Node<Key, Value> *node) const; 
    int getHeight(Node<Key, Value> *node) const; 
    static Node<Key, Value>* successor(Node<Key, Value>* current); 


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO -
    current_ = ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO -
    current_ = NULL; 
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO -
    if (this->current_ == rhs.current_) {
    	return true; 
    }
    return false; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO -
    if (this->current_ != rhs.current_) {
    	return true; 
    }
    return false; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO - 
    //take the successor with the helper function 
    current_ = successor(current_); 
    return *this; 
    
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO - 
    root_ = NULL; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO - 
    clear();  

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO -
    //check if the root is NULL
	if (root_ == NULL) {
		//in this case, create a new node to be the root w/ values from the parameter 
		root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
        //At this point we're done for this case
	}
	else {
        //The root is not null 
		//find the correct location 
		Node<Key, Value> *curr = internalFind(keyValuePair.first); 
		//check if the node already exists 
        //If the node already exists, just set its value to the value given by KeyValuePair 
		if (curr != NULL) curr->setValue(keyValuePair.second); 
		//The node doesn't already exist: 
		else {
			curr = root_; 
            bool x = true;  
			while (x) {
				//Walk the tree to find the correct place to insert the node 
				if (keyValuePair.first < curr->getKey()) {
					//we need to move to the left 
					if (curr->getLeft() != NULL) {
						//we can keep walking 
						curr = curr->getLeft(); 
					}
					else {
						//we have found the correct place 
						Node<Key, Value> *node = new Node<Key, Value>(keyValuePair.first, 
							keyValuePair.second, curr); 
						curr->setLeft(node); 
						x = false;  
					}
				}
				//Handle the case where we walk to the right 
				else {
					if (curr->getRight() != NULL) {
						//we can keep walking 
						curr = curr->getRight(); 
					}
					else {
						//we have found the correct place
						Node<Key, Value> *node = new Node<Key, Value>(keyValuePair.first, 
							keyValuePair.second, curr); 
						curr->setRight(node); 
						x = false; 
                    }
				}
			}
		}
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //First find the node 
    Node<Key, Value> *curr = internalFind(key); 
    //check to make sure the node is in the tree
    if (curr == NULL) return; 
    else {
    	//The node is present 
    	//We'll need to distinguish between the different removal cases
    	//Start by finding the number of child nodes
    	Node<Key, Value> *parent = curr->getParent(); 
    	Node<Key, Value> *leftChild = curr->getLeft(); 
    	Node<Key, Value> *rightChild = curr->getRight(); 
    	int counter = 0; 
    	if (leftChild != NULL) counter++; 
    	if (rightChild != NULL) counter++; 
    	//Begin the cases
    	//Case 1: no children, leaf node 
    	if (counter == 0) {
    		//check for parent
    		if (parent != NULL) {
    			//we can reassign pointers
    			if (parent->getLeft() == curr) {
    				//our current node is a left child
    				parent->setLeft(NULL); 
    			}
    			else {
    				//our current node is a right child 
    				parent->setRight(NULL); 
    			}
    		}
    		else {
    			//we are dealing with the root node 
    			root_ = NULL; 
    		}
    	}
    	//Case 2: one child
    	else if (counter == 1) {
    		//need to promote the child 
    		Node<Key, Value> *child; 
    		//determine if the child is left or right 
    		if (leftChild != NULL) child = leftChild; 
    		else child = rightChild; 
    		//check to see which child we need to reset
            if (parent == NULL) {
                //If we don't have a parent, the child becomes the root 
                root_ = child; 
                child->setParent(NULL); 
            }
            else {
                //We need to find which child we are dealing with 
                //Set right child 
                if (parent->getRight() == curr) parent->setRight(child); 
                //Set left child 
                else parent->setLeft(child); 
                //Set parent 
                child->setParent(parent); 
            }			
    	}
    	//Case 3: two children 
    	else if (counter == 2) {
    		//we'll need to swap the value with its predecessor and then remove it 
    		nodeSwap(curr, predecessor(curr)); 
    		//reassign pointers 
    		parent = curr->getParent(); 
    		leftChild = curr->getLeft(); 
    		rightChild = curr->getRight();
    		Node<Key, Value>* node = NULL;  
    		//See whether we have a left or right child 
    		if (leftChild != NULL) node = leftChild; 
    		else if (rightChild != NULL) node = rightChild; 
    		//Check whether parent is NULL 
    		if (node != NULL) {
    			//Set as NULL
    			if (parent->getRight() == curr) parent->setRight(node); 
    			else parent->setLeft(node); 
    			node->setParent(parent); 
    		}
    		//Case where node is present in the tree
    		else if (parent != NULL) {
    			if (parent->getRight() == curr) parent->setRight(NULL); 
    			else parent->setLeft(NULL);  
    		}
    	}
    	delete curr; 
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO -
    //create a node to walk through the tree
    Node<Key, Value>* walker = current; 
    //First check to make sure the parameter wasn't NULL
    if (walker != NULL) {
        //Case one
    	if (walker->getLeft() != NULL) {
    		//The first step is going to the left side of the tree, one step down
    		walker = walker->getLeft(); 
    		//Now walk as far right as possible 
    		while (walker->getRight() != NULL) {
    			walker = walker->getRight(); 
    		}
    	}
        //Case two - where the node to the left is NULL
   		else {
    		//The parameter was NULL
    		bool foundPredecessor = false; 
            //We need to walk up the parents 
    		while (walker->getParent() != NULL) {
    			//walk up the parents 
    			if (walker->getParent()->getRight() == walker) {
    				//The final case where we get to the top of the parents 
    				foundPredecessor = true; 
    				//Step up one more time 
    				walker = walker->getParent(); 
    				break; 
    			} 
    			else {
    				//we need to continue walking up the parents 
    				walker = walker->getParent(); 
    			}
    		}
    		//if we never find the predecessor, just return NULL
    		if (!foundPredecessor) return NULL; 
    	}
    }
    return walker; 
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO -
    //Create an iterator at the smallest node in the tree
    BinarySearchTree<Key, Value>::iterator it(getSmallestNode()); 
    //Iterate until we reach the end of the tree
    while (it != this->end()) {
    	//get the value for the current key, then advance the iterator and remove the key
    	Key currKey = it->first; 
    	++it; 
    	remove(currKey); 
    }
    //Final step is to set the root to NULL
    root_ = NULL; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO -
    //Move through the left side of the tree to find the last node and then return it
    Node<Key, Value> *currNode = root_; 
    //If there are no nodes in the tree, just return NULL
    if (currNode == NULL) {
    	//there are no nodes in the tree
    	return NULL; 
    }
    //Otherwise we need to walk all the way to the left to find the node 
    while (currNode->getLeft() != NULL) {
    	//walk the left side of the tree
    	currNode = currNode->getLeft(); 
    }
    //return the smallest node
    return currNode; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO - 
    //Walk the tree to find the node, then return a pointer to the node with
    //the specified key 
    //Start by walking at the root 
    Node<Key, Value> *currNode = root_;
    //If the root is NULL or if we are already there, we can just skip this loop and return
    while (currNode != NULL && currNode->getKey() != key) {
    	//step through the tree
    	if (key > currNode->getKey()) {
    		//if the key is bigger than the current key, move to the right 
    		currNode = currNode->getRight(); 
    	}
    	else {
    		//we know we need to move to the left
    		currNode = currNode->getLeft(); 
    	}
    }
    //should return node if the key doesn't exist 
    return currNode; 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO -
    //Just return the helper function with the root node as a parameter 
    return isBalancedHelperFunc(root_); 
}

//HELPER FUNCTIONS

//create a helper function so that we can pass in the parameter for a node and recurse 
template <typename Key, typename Value> 
bool BinarySearchTree<Key, Value>::isBalancedHelperFunc(Node<Key, Value> *node) const {
	
    //The base case
    if (node == NULL) return true; 

    //The recursive case
    //additional cases - establish left and right child nodes
    Node<Key, Value> *leftNode = node->getLeft();
    Node<Key, Value> *rightNode = node->getRight();
    //check the height at this level between the present subtrees
    //and recurse through the the lower levels of the tree
    if (std::abs(getHeight(rightNode) - getHeight(leftNode)) <= 2 && 
    	isBalancedHelperFunc(rightNode) && isBalancedHelperFunc(leftNode)) {
        //The entire tree is balanced 
    	return true; 
    }
    //The tree is not balanced 
    return false; 
}

//getHeight helper function implementation 
//Get the height at a given node 
template <typename Key, typename Value> 
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value> *node) const {
	//check if the node is NULL
	if (node == NULL) return 0; 
	else {
		//obtain the heights of the right/left subtrees recursively 
        //Add one each time for each level of the tree
		int leftHeight = getHeight(node->getLeft()) + 1; 
		int rightHeight = getHeight(node->getRight()) + 1; 
		//take the max of the heights plus one for the root 
		int maxHeight = std::max(leftHeight, rightHeight) + 1; 
        //return the height 
		return maxHeight; 
	}
}

//successor helper function 
template <class Key, class Value> 
Node<Key, Value> *
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) {
	//implement the same way we did predecessor 
	//create a node to walk through the tree
	Node<Key, Value>* walker = current; 
	//First check to make sure the parameter wasn't NULL
	if (walker != NULL) {
        //Case one
		if (walker->getRight() != NULL) {
			//The first step is going to the right side of the tree, one step down 
			walker = walker->getRight(); 
			//now walk as far left as possible
			while (walker->getLeft() != NULL) {
				walker = walker->getLeft(); 
			}
		}
        //Case two 
		else {
			//The parameter was NULL - need to walk up the parent nodes
			bool foundSuccessor = false; 
			while (walker->getParent() != NULL) {
				//walk up the parents
				if (walker->getParent()->getLeft() == walker) {
					//The final case where we get to the top of the parents 
					foundSuccessor = true; 
					walker = walker->getParent(); 
					break; 
				}
				else {
					//walk up the parents 
					walker = walker->getParent(); 
				}
			}
			//If we never find the successor, just return NULL
			if (!foundSuccessor) return NULL; 
		} 
	}
	return walker; 
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}


/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
