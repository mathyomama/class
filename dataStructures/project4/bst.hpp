#ifndef BST_HPP__
#define BST_HPP__

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
	makeEmpty(root);
}

// copy assignment
template <typename T>
const BST<T>& BST<T>::operator=(const BST &rhs)
{
	BST<T> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// move assignment
template <typename T>
const BST<T>& BST<T>::operator=(BST &&rhs)
{
	std::swap(threshold, rhs.threshold);
	std::swap(root, rhs.root);
	return *this;
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
	std::cout << std::endl;
}

// printLevelOrder, print all elements at a depth before moving to next depth
template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder(root);
	std::cout << std::endl;
}

// NumOfNodes, returns the number of nodes in the tree
template <typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes(root);
}

// height, returns the height of the tree
template <typename T>
int BST<T>::height() const
{
	return height(root);
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
	return contains(v, root);
}

// PRIVATE MEMBER FUNCTIONS, most of them will be implemented using recursion

// printInOrder, recursive, prints in the order left | root | right (infix)
// prints only what is under the node given
template <typename T>
void BST<T>::printInOrder(BSTNode *t) const
{
	if (t != nullptr) {
		// first descend through the left side
		printInOrder(t->left);
		std::cout << t->element << " "; // put a space between each element
		// lastly, descend through the right side
		printInOrder(t->right);
	}
}

// printLevelOrder, prints each level first before moving to the next level
// breadth first search => queue, prints only what is under the node given
template <typename T>
void BST<T>:: printLevelOrder(BSTNode *t) const
{
	std::queue<BSTNode *> printQ;
	if (t != nullptr) {
		printQ.push(t);
	}
	while (!printQ.empty()) {
		BSTNode *cur = printQ.front(); // grab the front item in the queue
		printQ.pop(); // remove the front item
		std::cout << cur->element << " ";
		if (cur->left != nullptr) { // push the left side if not nullptr
			printQ.push(cur->left);
		}
		if (cur->right != nullptr) { // push right side if not nullptr
			printQ.push(cur->right);
		}
	}
}

// makeEmpty, recursive, goes down the tree deleting each node
template <typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
	if (t != nullptr) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
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
	if (t == nullptr) {
		return false;
	} else if (v < t->element) {
		return contains(v, t->left);
	} else if (v > t->element) {
		return contains(v, t->element);
	} else {
		(t->freq)++;
		if (t->freq == threshold) {
			//single rotation
			t->freq = 0;
		}
		return true;
	}
}

// numOfNodes, recursive, returns the number of nodes in given tree
template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
	// first return 0 if the given node is a nullptr
	if (t == nullptr) {
		return 0;
	}
	// use post-order traversal: search left, then right, and add one for the current node
	return numOfNodes(t->left) + numOfNodes(t->right) + 1; // +1 for the node itself
}

// height, recursive, returns the height of the given tree
template <typename T>
int BST<T>::height(BSTNode *t) const
{
	if (t == nullptr) {
		return -1; // counting the links instead of the nodes along the path
	}
	return std::max(height(t->left), height(t->right)) + 1; // +1 for the link itself
}

// clone, recursive, makes a copy of the tree under the node and returns the copy
template <typename T>
typename BST<T>::BSTNode *BST<T>::clone(BSTNode *t) const
{
	if (t != nullptr) {
		return  new BSTNode{t->element, t->freq, clone(t->left), clone(t->right)};
	} else {
		return nullptr;
	}
}

#endif
