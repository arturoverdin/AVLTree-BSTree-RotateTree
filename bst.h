#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters
* for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, 
* such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
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
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
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
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
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
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}
	private:
		void insertHelper(const std::pair<Key, Value>& keyValuePair,
		Node<Key,Value>* root);
		Node<Key, Value>* internalFindHelper(const Key& key,
		Node<Key,Value>* root) const;
		Node<Key, Value>* getPredecessor(Node<Key,Value>* root);
		int checkHeight(Node<Key,Value>* root) const;
		void helpClear(Node<Key,Value>* root);
		bool returnBalanced(Node<Key,Value>* root) const;
		void swapPred(Node<Key,Value>* remove ,Node<Key,Value>* pred);
		void removeHelper(const Key& key, Node<Key,Value>* root);
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
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
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}
/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(nullptr);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if(mRoot == nullptr) 
	{
		Node<Key,Value>* leaf = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
		mRoot = leaf;
		
	} else {
		insertHelper(keyValuePair, mRoot);
	}
}

/**
* A helper method that recursively finds the node at which to insert,
* creates a node, and sets the parents/children accordingly. 
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insertHelper(const std::pair<Key, Value>& keyValuePair, Node<Key,Value>* root) 
{
	if(keyValuePair.first < root->getKey()) 
	{
		if(root->getLeft() == nullptr) 
		{
			Node<Key,Value>* leaf = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, root);
			root->setLeft(leaf);

		} else {

			insertHelper(keyValuePair, root->getLeft());
		}
	} 
	else if(keyValuePair.first > root->getKey()) 
	{
		if(root->getRight() == nullptr) 
		{
			Node<Key,Value>* leaf = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, root);
			root->setRight(leaf);
		} 
		else 
		{
			insertHelper(keyValuePair, root->getRight());
		}
	} 
	else 
	{
		root->setValue(keyValuePair.second);
	}
}

/**
* A remove method to remove a specific key from 
* a Binary Search Tree. The tree may not remain 
* balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{	
	Node<Key,Value>* to_remove = internalFind(key);
 	removeHelper(key, to_remove);
}

/** 
 * Helper function for remove that takes in the 
 * node directly and decides how to remove it.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(const Key& key, Node<Key,Value>* to_remove) 
{

	if(to_remove == nullptr) {
		return;
	}

	if(!to_remove->getRight() && !to_remove->getLeft()) 
	{
		if(mRoot == to_remove) 
		{
			mRoot = nullptr;

		} else { 	

			if(to_remove->getParent()->getLeft() == to_remove) 
			{
				to_remove->getParent()->setLeft(nullptr);

			} else {

				to_remove->getParent()->setRight(nullptr);
			}
		}
		delete to_remove;
	} 
	else if(!to_remove->getRight()) 
	{

		Node<Key,Value>* parent = to_remove->getParent();
		if(parent == nullptr) 
		{
			Node<Key,Value>* child = to_remove->getLeft();
			to_remove->setLeft(nullptr);
			mRoot = child;
			child->setParent(nullptr);
			
		}
		else if(parent->getLeft() == to_remove) 
		{
			parent->setLeft(to_remove->getLeft());
			parent->getLeft()->setParent(parent);

		} else {

			parent->setRight(to_remove->getLeft());
			parent->getRight()->setParent(parent);
		}

		delete to_remove;
	} 
	else if(!to_remove->getLeft()) 
	{
		Node<Key,Value>* parent = to_remove->getParent();
		if(parent == nullptr) 
		{
			Node<Key,Value>* child = to_remove->getRight();
			to_remove->setRight(nullptr);
			mRoot = child;
			child->setParent(nullptr);

		} else {

			if(parent->getLeft() == to_remove) 
			{
				parent->setLeft(to_remove->getRight());
				parent->getLeft()->setParent(parent);

			} else {

				parent->setRight(to_remove->getRight());
				parent->getRight()->setParent(parent);	
			}
		}

		delete to_remove;

	} else {

		Node<Key,Value>* predecessor = getPredecessor(to_remove);
		swapPred(to_remove, predecessor);
		removeHelper(key, to_remove);
	}

}

/** 
 * Swaps a node with it's predecessor.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::swapPred(Node<Key,Value>* remove , Node<Key,Value>* pred)
{

	bool root = false;
	bool remove_right = false;
	bool remove_left = false;

	Node<Key,Value>* new_pred_parent = remove->getParent();
    Node<Key,Value>* new_pred_left = remove->getLeft();
    Node<Key,Value>* new_pred_right = remove->getRight();
    Node<Key,Value>* new_remove_parent = pred->getParent();
    Node<Key,Value>* new_remove_left = pred->getLeft();
    Node<Key,Value>* new_remove_right = nullptr;

    if(pred->getParent() == remove) {
		new_remove_parent = pred;
		new_pred_left = remove; 
	}
	
	if(remove->getParent()) {
		if(remove->getParent()->getRight() == remove) 
		{
			remove_right = true;

		} else {

			remove_left = true;
		}
	} else {

		root = true;
	}

	remove->setParent(new_remove_parent);
	remove->setLeft(new_remove_left);
	remove->setRight(new_remove_right);

	if(pred->getParent()->getRight() == pred) {
		
		remove->getParent()->setRight(remove);
		
	} else if(pred->getParent()->getLeft() == pred) {

		remove->getParent()->setRight(remove);
	}

	if(remove->getLeft()) 
	{
		remove->getLeft()->setParent(remove);
	}

	pred->setParent(new_pred_parent);
	pred->setLeft(new_pred_left);
	pred->setRight(new_pred_right);
	pred->getLeft()->setParent(pred);
	pred->getRight()->setParent(pred);

	if(remove_right) {
		pred->getParent()->setRight(pred);
	} else if(remove_left) {
		pred->getParent()->setLeft(pred);
	}
	
	if(root) {
		mRoot = pred;
	} 
} 

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{	
	helpClear(mRoot);
	mRoot = nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::helpClear(Node<Key,Value>* root)
{
	if(root == nullptr) 
	{
		return;
	}
	helpClear(root->getRight());
	helpClear(root->getLeft());

	delete root;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	if(mRoot == nullptr) 
	{
		return nullptr;

	} else {

		Node<Key, Value>* temp = mRoot;
		while(temp->getLeft() != NULL) {
			temp = temp->getLeft();
		}
		return temp;
	}
}

/** 
 * Function that returns the predecessor of a given node.
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getPredecessor(Node<Key,Value>* root) {
	Node<Key,Value>* temp = root->getLeft();
	if(temp == nullptr) {
		return nullptr;
	}
	while(temp->getRight()) 
	{
		temp = temp->getRight();
	}
	return temp;
}

/** 
 * Find function that returns a pointer to 
 * a node with the specified key. 
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	if(mRoot == nullptr || mRoot->getKey() == key) {
		return mRoot;
	}
	return internalFindHelper(key, mRoot);
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFindHelper(const Key& key, Node<Key,Value>* root) const
{
	if(root == nullptr || root->getKey() == key) {
		return root;
	}
	
	if(key < root->getKey()) 
	{
		return internalFindHelper(key, root->getLeft());
	}  
	else 
	{
		return internalFindHelper(key, root->getRight());	
	}
}

/**
* Returns the height of the tree rooted
* at a specific node.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::checkHeight(Node<Key,Value>* root) const
{
	if(root == nullptr) return 0;

	int left = checkHeight(root->getLeft());
	int right = checkHeight(root->getRight());

	if(left > right) 
	{
		return 1+left;

	} else {

		return 1+right;

	}
}


/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	return returnBalanced(mRoot);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::returnBalanced(Node<Key,Value>* root) const
{
	if(root == nullptr) {
		return true;
	}

	int left = checkHeight(root->getLeft());
	int right = checkHeight(root->getRight());

	if(abs(left-right) <= 1 && returnBalanced(root->getRight()) 
		&& returnBalanced(root->getLeft())) 
	{
		return true;
	}
	return false;
}

/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII grremovehics format.
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
