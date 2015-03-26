#include <iostream>
#include <string>


// PUBLIC MEMBER FUNCTIONS

// constructor, default value for threshold is 1
template <typename T>
BST<T>::BST(int th) :
	threshold{th}, root{nullptr}
{
}

// constructor, takes an input string, default value for threshold is 1
// input string is a space separated string, conversion can be made to int
template <typename T>
BST<T>::BST(std::string input, int th) :
	threshold{th}, root{nullptr}
{
	buildFromInputString(input);
}

// copy constructor
template <typename T>
BST<T>::BST(const BST &rhs) :
	threshold{rhs.threshold}, root{nullptr}
{
	BSTNode *root = new BSTNode;
	root = clone(rhs.root);
}

// move constructor
template <typename T>
BST<T>::BST(BST &&rhs) :
	threshold{rhs.threshold}, root{rhs.root}
{
	rhs.threshold = 0;
	rhs.root = nullptr;
}

// destructor
template <typename T>
BST<T>::~BST()
{
	deleteTree(root); // private function not part of required functions
}

// copy assignment
template <typename T>
BST<T>::BST BST<T>::operator=(const BST &rhs)
{
	BST<T> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// move assignment
template <typename T>
BST<T>::BST BST<T>::operator=(BST &&rhs)
{
	std::swap(threshold, rhs.threshold);
	std::swap(root, rhs.root);
}

// buildFromInputString, take a string and organize values in BST
template <typename T>
void buildFromInputString(const std::string input)
{
}

// empty, check if the BST is empty
template <typename T>
bool BST<T>::empty()
{
	if (root == nullptr) {
		return true;
	} else {
		return false;
	}
}

// printInOrder, left | root | right
template <typename T>
void BST<T>::printInOrder() const
{
	printInOrder(root);
}

// printLevelOrder, print all elements at a depth before moving to next depth
template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder(root);
}

// NumOfNodes, returns the number of nodes in the tree
template <typename T>
int BST<T>::numOfNodes() const
{
	numOfNodes(root);
}

// height, returns the height of the tree
template <typename T>
int BST<T>::height() const
{
	height(root);
}

// makeEmpty, clears the BST of all the values
template <typename T>
void BST<T>::makeEmpty()
{
	makeEmpty(root);
}

// insert, with copy semantics
template <typename T>
void BST<T>::insert(const T &v)
{
	insert(v, root);
}

// insert, with move semantics
template <typename T>
void BST<T>::insert(T &&v)
{
	insert(v, root);
}

// remove, delete the node with the given value
template <typename T>
void BST<T>::remove(const T &v)
{
	remove(v, root);
}

// contains, checks if the given value is in the tree
template <typename T>
bool BST<T>::contains(const T &v)
{
	contains(v, root);
}

// PRIVATE MEMBER FUNCTIONS, most of them will be implemented using recursion

// printInOrder, recursive, prints in the order left | root | right (infix)
template <typename T>
void BST<T>::printInOrder(BSTNode *t)
{
}

// printLevelOrder, prints each level first before moving to the next level
template <typename T>
void BST<T>:: printLevelOrder(BSTNode *t)
{
}

// makeEmpty, recursive, goes down the tree deleting each node
template <typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
}

// insert, recursive, copy version, goes down tree and inserts at the bottom of tree
template <typename T>
void BST<T>::insert(const T &v, BSTNode* &t)
{
}

// insert, recursive, move version, goes down tree and inserts at the bottom of tree
template <typename T>
void BST<T>::insert(T &&v, BSTNode* &t)
{
}

// remove, recursive, remove the value from the tree
template <typename T>
void BST<T>::remove(const T &v, BSTNode* &t)
{
}

// contains, recursive, checks if the value is in the tree
template <typename T>
bool BST<T>::contains(const T &v, BSTNode* &t)
{
}

// numOfNodes, recursive, returns the number of nodes in given tree
template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
}

// height, recursive, returns the height of the given tree
int BST<T>::height(BSTNode *t) const
{
}

// clone, recursive, makes a copy of the tree under the node and returns the copy
BST<T>::BSTNode *BST<T>::clone(BSTNode *t)
{
}
