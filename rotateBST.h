#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"
#include <set>

template<typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value> { 
public:
	rotateBST();
	virtual ~rotateBST();
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
private:
	void linkedList(Node<Key,Value>* root, rotateBST& t2) const;
	void transformHelper(Node<Key,Value>* root, Node<Key,Value>* t2_root,
						rotateBST& t2) const;
	Node<Key, Value>* smallestSubtree(Node<Key,Value>* r) const;
};

/**
* Calls the constructor for a BST.
*/
template<typename Key, typename Value>
rotateBST<Key,Value>::rotateBST():BinarySearchTree<Key,Value>() { }

template<typename Key, typename Value>
rotateBST<Key,Value>::~rotateBST() { }

/**
* Iterates through both BST's and inserts their keys into sets,
* returns true if they equate.
*/
template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const 
{
	std::set<Key> one;
	std::set<Key> two;

	typename rotateBST<Key, Value>::iterator it(this->getSmallestNode());
	typename rotateBST<Key, Value>::iterator end(nullptr);

	for(; it != end; ++it) {
		one.insert(it->first);
	}

	typename rotateBST<Key, Value>::iterator jt(t2.getSmallestNode());
	
	for(; jt != end; ++jt) {
		two.insert(jt->first);
	}

	return one == two;
}

/**
* Calls the helper function that does the transformation. 
*/
template<typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const 
{
	if(!sameKeys(t2)) return;
	transformHelper(this->mRoot, t2.mRoot, t2);
}

/** 
* Performs the right rotations that create a linked list 
* we can then shape. 
*/
template<typename Key, typename Value>
void rotateBST<Key,Value>::linkedList(Node<Key,Value>* t2_root, rotateBST& t2) const 
{
	if(t2_root == nullptr) {
		return;
	}

	while(t2_root->getLeft()) 
	{
		t2.rightRotate(t2_root);
		t2_root = t2_root->getParent();
	}
	linkedList(t2_root->getRight(), t2);
}

/** 
* Calls left left rotate recursively on each child of each node 
* eventually equating the values. 
*/
template<typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper(Node<Key,Value>* root, 
	Node<Key,Value>* t2_root, rotateBST& t2) const {

	if(t2_root == nullptr && root == nullptr) {
		return;
	}

	Node<Key,Value>* subRoot = smallestSubtree(t2_root);
	linkedList(t2_root, t2);
	t2_root = subRoot;

	while(t2_root->getKey() != root->getKey()) 
	{
		t2.leftRotate(t2_root);
		if(t2_root->getParent()) {
			t2_root = t2_root->getParent();
		} else {
			break;
		}
	}
	transformHelper(root->getRight(), t2_root->getRight(), t2);
	transformHelper(root->getLeft(), t2_root->getLeft(), t2);
}

/**
* Function that finds the smallest value in a given subtree.
*/
template<typename Key, typename Value>
Node<Key, Value>* rotateBST<Key,Value>::smallestSubtree(Node<Key,Value>* r) const 
{
	while(r->getLeft()) {
		r = r->getLeft();
	}
	return r;
}

/**
* Performs a left rotate on a given node.
*/
template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value>* r) 
{
	if(!r->getRight()) {
		return;
	}

	Node<Key, Value>* new_parent = r->getRight();
	r->setRight(new_parent->getLeft());

	if(new_parent->getLeft()) {
		new_parent->getLeft()->setParent(r);
	}

	new_parent->setParent(r->getParent());
	if(!r->getParent()) {

		this->mRoot = new_parent;

	} else if(r == r->getParent()->getLeft()) {

		r->getParent()->setLeft(new_parent);

	} else {

		r->getParent()->setRight(new_parent);

	}

	new_parent->setLeft(r);
	r->setParent(new_parent);
}

/**
* Performs a right rotate on a given node.
*/
template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key,Value>* r) 
{
	if(!r->getLeft()) {
		return;
	} 
 
	Node<Key, Value>* new_parent = r->getLeft();
	r->setLeft(new_parent->getRight());

	if(new_parent->getRight()) {
		new_parent->getRight()->setParent(r);
	}

	new_parent->setParent(r->getParent());
	if(!r->getParent()) {

		this->mRoot = new_parent;

	} else if(r == r->getParent()->getLeft()) {

		r->getParent()->setLeft(new_parent);

	} else {

		r->getParent()->setRight(new_parent);

	}

	new_parent->setRight(r);
	r->setParent(new_parent);
}
#endif 