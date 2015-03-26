#ifndef BST_H__
#define BST_H__


#include <iostream>
#include <string>
#include <queue>


#define DEFAULT_THRESHOLD_VALUE 1

namespace cop4530 {

template <typename T>
class BST {
	private:
		// private node structure which will be used in the implementation of the BST
		struct BSTNode {
			T element;
			unsigned int freq;
			BSTNode *left;
			BSTNode *right;

			BSTNode(const T &newElement, unsigned int frequency, BSTNode *ll, BSTNode *rl) :
				element{newElement}, freq{frequency}, left{ll}, right{rl} {}
			BSTNode(const T &&newElement, unsigned int frequency, BSTNode *ll, BSTNode *rl) :
				element{std::move(newElement)}, freq{frequency}, left{ll}, right{rl} {}
		};

		// private functions which will be implemented recursively
		void printInOrder(BSTNode *t) const;
		void printLevelOrder(BSTNode *t) const;
		void makeEmpty(BSTNode* &t);
		void insert(const T& v, BSTNode* &t);
		void insert(T&& v, BSTNode* &t);
		void remove(const T& v, BSTNode* &t);
		bool contains(const T& v, BSTNode* &t, BSTNode* &p); // p is the parent node
		int numOfNodes(BSTNode *t) const;
		int height(BSTNode *t) const;
		BSTNode *clone(BSTNode *t) const; // clone all nodes in the subtree t, used by operator= and constructor
		BSTNode *findMin(BSTNode *t) const; // find the smallest value in the subtree, used by remove

		// private member variables
		BSTNode *root;
		int threshold;

	public:
		// constructors
		explicit BST(int th=DEFAULT_THRESHOLD_VALUE); // default constructor
		BST(const std::string input, int th=DEFAULT_THRESHOLD_VALUE); // constructor from input string
		BST(const BST &rhs); // Copy Constructor
		BST(BST &&rhs); // Move Constructor
		
		// destructor, assignment
		~BST(); // destructor
		const BST& operator=(const BST &rhs); // copy assignment
		const BST& operator=(BST &&rhs); // move assignment

		// public member functions
		void buildFromInputString(const std::string input);
		bool empty();

		// functions which are essentially wrappers around private functions
		void printInOrder() const; // printing the tree, in-order traversal
		void printLevelOrder() const; // printint the tree, level-order traversal
		int numOfNodes() const; // return the number of nodes in the tree
		int height() const; // return the height of the tree
		void makeEmpty(); // clear the tree by deleting all the nodes
		void insert(const T& v); // insert the given value into the tree, copy
		void insert(T&& v); // insert the given value into the tree, move
		void remove(const T& v); // remove the given value from the tree
		bool contains(const T& v); // checks if the given value is in the tree
};

// include the implementation file
#include "bst.hpp"

}

#endif
