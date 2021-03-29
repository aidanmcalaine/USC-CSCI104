#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* node); 
    void rotateRight(AVLNode<Key, Value>* node); 
    void updateHeight(AVLNode<Key, Value>* node); 
    int height(AVLNode<Key, Value>* node) const; 
    int heightDifference(AVLNode<Key, Value>* node) const; 


};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //Replicate bst insert
   	//BinarySearchTree<Key, Value>::insert(new_item);
   	if (this->root_ == NULL) {
		//in this case, create a new node to be the root w/ values from the parameter 
		this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL); 
		return; 
	}
	//Find the node
	Node<Key, Value> *curr = BinarySearchTree<Key, Value>::internalFind(new_item.first); 
	if (curr != NULL) curr->setValue(new_item.second); 
    //The node doesn't already exist:
	else {
		curr = (AVLNode<Key, Value>*)this->root_; 
		AVLNode<Key, Value> *node = new AVLNode<Key, Value>(new_item.first, 
						new_item.second, NULL); 
		bool x = true; 
		while (x) {
    		//walk the tree to find the correct place to insert the node
			if (new_item.first < curr->getKey()) {
    			//we need to move to the left 
				if (curr->getLeft() != NULL) {
    				//we can keep walking 
					curr = curr->getLeft(); 
				}
				else {
    				//we have found the correct place
					curr->setLeft(node); 
					node->setParent(curr);
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
					curr->setRight(node);
					node->setParent(curr);
					x = false; 
				}
			}
		}
	}
	//Create a pointer to the new node and update its height 
   	// Node<Key, Value>* node = BinarySearchTree<Key, Value>::internalFind(new_item.first); 
 	// AVLNode<Key, Value>* node_ = static_cast<AVLNode<Key, Value>*>(this->root_); 
	AVLNode<Key, Value>* n = (AVLNode<Key, Value>*)BinarySearchTree<Key, Value>::internalFind(new_item.first);  
	// AVLNode<Key, Value>* node_ = n; 
	updateHeight(n); 

    //Now that we have our avl node with a pointer and updated height, we need to walk
   	//through the tree to update the height(s) and perform necessary rotations
   	AVLNode<Key, Value>* parent = n->getParent(); 
   	
	while (parent != NULL) {

    	//update the height of each node and check to make sure it remains balanced 
    	//Balance it with helper functions if necessary 
		updateHeight(parent); 
    	//Check the balance of the subtrees
		int currCounter = heightDifference(parent); 

    	//Check the various cases:

    	//First: zig-zig cases
    	//Left rotate zig-zig case:
		if (currCounter < -1 && new_item.first > parent->getRight()->getKey()) {
    		//need to perform a single left rotation
			rotateLeft(parent); 
    		//walk up to the next parent 
			parent = parent->getParent(); 
		}
    	//Right rotate zig-zig case:
		else if (currCounter > 1 && new_item.first < parent->getLeft()->getKey()) {
   			//we need to perform a single right rotation 
			rotateRight(parent); 
    		//walk up to the next parent 
			parent = parent->getParent(); 
		}

    	//Second: zig-zag cases
    	//Left rotate then right rotate zig-zag case:
		else if (currCounter > 1 && new_item.first > parent->getLeft()->getKey()) {
    		//perform the left rotation
			rotateLeft(parent->getLeft()); 
    		//perform the right rotation
			rotateRight(parent); 
    		//walk up to the next parent 
			parent = parent->getParent(); 
		}
    	//Right rotate then left rotate zig-zag case:
		else if (currCounter < -1 && new_item.first < parent->getRight()->getKey()) {
    		//perform the right rotation 
			rotateRight(parent->getRight()); 
    		//perform the left rotation 
			rotateLeft(parent); 
   			//walk up to the next parent 
			parent = parent->getParent(); 
		}
		//Update the parent 
		parent = parent->getParent(); 
	}	
}


template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //Begin by casting the given node to an AVL node 
    AVLNode<Key, Value>* node = dynamic_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key)); 

    //Check the case where the node is not in the tree
	if (node == NULL) return; 

	//Take the necessary steps to remove the node 
	//Either left or right child node
	bool leftChild, rightChild = false; 
	AVLNode<Key, Value>* parent = node->getParent(); 
	if (parent != NULL) {
		if (parent->getLeft() == node) {
			//we have a left child 
			leftChild = true; 
		}
		else {
			rightChild = true; 
		}
	}

	//Remove the node with BST remove 
	BinarySearchTree<Key, Value>::remove(key); 
	//Check to see if our node is the root 
	if (parent != NULL) {
		if (leftChild == true) {
			//reassign our node
			node = parent->getLeft(); 
		}
		else {
			node = parent->getRight(); 
		}
		if (node == 0) node = parent; 
	}
	else {
		node = static_cast<AVLNode<Key, Value>*>(this->root_); 
	}
	//Now update heights 
	if (node != NULL) {
		updateHeight(node->getRight()); 
		updateHeight(node->getLeft()); 
	}

	//Now, we can walk the tree to update heights, check balances, and perform
	//rotations as necessary 
	while (node != NULL) {
		//this will have a very similar implementation to the way I update heights
		//and check balances my insert function 
		updateHeight(node); 
		int currCounter = heightDifference(node); 
		int leftChildCounter = heightDifference(node->getLeft()); 
		int rightChildCounter = heightDifference(node->getRight()); 

		//move into the cases for rotations 
		//First, zig zig cases
		//Left rotate zig-zig case:
		if (currCounter < -1 && rightChildCounter <= 0) {
			//perform one left rotation 
			rotateLeft(node); 
			//advance the node to the parent
			node = node->getParent(); 
		}
		//Right rotate zig-zig case:
		else if (currCounter > 1 && leftChildCounter >= 0) {
			//perform one right rotation 
			rotateRight(node); 
			//advance the node to the parent 
			node = node->getParent(); 
		}

		//Second, zig zag cases
		//Left rotate then right rotate zig-zag case
		else if (currCounter > 1 && leftChildCounter < 0 ) {
			//perform the left rotation 
			rotateLeft(node); 
			//perform the right rotaiton 
			rotateRight(node); 
			//advance the node to the parent
			node = node->getParent(); 
		}
		//Right rotate then left rotate zig-zag case
		else if (currCounter < -1 && rightChildCounter > 0) {
			//perform the right rotation 
			rotateRight(node); 
			//perform the left rotation 
			rotateLeft(node); 
			//advance the node to the parent
			node = node->getParent(); 
		}
		node = node->getParent(); 

	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

//Implementation for the rotateLeft function 
template<class Key, class Value> 
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
	// Zig-zig case
	// For zig zig, we perform a left rotation on the parent node 
	AVLNode<Key, Value>* grandparent = node->getParent(); 
	AVLNode<Key, Value>* right = node->getRight(); 
	//We need to handle the case where the right child becomes the root
	if (node == this->root_) {
		this->root_ = right; 
	}
	//handle the left child of the node that gets dragged to the top 
	//This will either orphan the left child of the right node, or will setRight to NULL
	// if (right != NULL) node->setRight(right->getLeft()); 
	// else node->setRight(NULL); 
	
	// //If we orphan a child, reassign its parent pointer to our current node
	// if (node->getRight() != NULL) {
	// 	//reassign the parent pointer of the orphan 
	// 	node->getRight()->setParent(node); 
	// }
	//Handle orphaning 
	if (right != NULL) {
		node->setRight(right->getLeft());
	}
	else {
		node->setRight(NULL); 
	}
	if (node->getRight() != NULL) {
		node->getRight()->setParent(node); 
	}

	//reassign other pointers 
	node->setParent(right); 
	right->setLeft(node); 
	right->setParent(grandparent); 
	//Now reassign the grandparent's child pointer to the former right child 
	if (grandparent != NULL) {
		//if it were NULL, our right child would have become the root 
		//Check whether we need to assign to the left or right 
		if (grandparent->getLeft() == node) {
			grandparent->setLeft(right); 
		}
		else {
			grandparent->setRight(right); 
		}
	}
}

//Implementation for the rotateRight function 
template<class Key, class Value> 
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
	//Very similar to rotateLeft implementation 
	//Zig-zig case
	//For zig zig, we perform a right rotation on the parent node 
	AVLNode<Key, Value>* grandparent = node->getParent(); 
	AVLNode<Key, Value>* left = node->getLeft(); 
	//We need to handle the case where the left child becomes the root 
	if (node == this->root_) {
		this->root_ = left; 
	}
	//handle the right child of the node that gets dragged to the top 
	//This will either orphan the right child of the left node, or it will setLeft to NULL 
	//*
	// if (left != NULL) node->setLeft(left->getRight()); 
	// else node->setLeft(NULL); 
	// //if we orphan a child, reassign its parent pointer to our current node 
	// if (node->getLeft() != NULL) {
	// 	//reassign the parent pointer of the orphan 
	// 	node->getLeft()->setParent(node); 
	// }
	node->setLeft(left->getRight()); 
	
	if (node->getLeft() != NULL) {
		node->getLeft()->setParent(node); 
	}
	//reassign other pointers 
	left->setRight(node); 
	left->setParent(grandparent); 
	node->setParent(left); 
	//Now reassign the grandparent's child pointer to the former left child  
	if (grandparent != NULL) {
		//if it were NULL, our left child would have become the root 
		//Check whether we need to assign to the left or right 
		if (grandparent->getLeft() == node) {
			grandparent->setLeft(left); 
		}
		else {
			grandparent->setRight(left); 
		}
	}
}

//Implementation for the updateHeight function 
template<typename Key, typename Value> 
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* node) {
	//calculate and set the correct height of the node
	if (node != NULL) {
		int leftHeight = height((AVLNode<Key, Value>*)((node)->getLeft())); 
		int rightHeight = height((AVLNode<Key, Value>*)((node)->getRight())); 
		int formerHeight = std::max(leftHeight, rightHeight); 
		node->setHeight(formerHeight + 1); 
	}
}

//Implementation for the height function 
template<typename Key, typename Value> 
int AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) const {
	//return the height of a given node
	if (node == NULL) {
		return 0; 
	}
	return node->getHeight(); 
}
//Implementation of the heightDifference function 
template<typename Key, typename Value> 
int AVLTree<Key, Value>::heightDifference(AVLNode<Key, Value>* node) const {
	//return the difference between heights of the left/right children 
	if (node == NULL) {
		return 0;
	}
	return height((AVLNode<Key, Value>*)(node->getLeft())) - height((AVLNode<Key, Value>*)(node->getRight())); 
}


#endif
