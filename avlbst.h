#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "rotateBST.h"

using namespace std;
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
    int getHeight() const;
    void setHeight(int height);
    
    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
    void insertHelper(const std::pair<Key, Value>& keyValuePair, AVLNode<Key,Value>* root);
    void rebalanceNode(AVLNode<Key,Value>* root);
    bool returnBalanced(AVLNode<Key,Value>* root) const;
    void updateHeight(AVLNode<Key,Value>* root);
    void removeHelper(const Key& key, AVLNode<Key,Value>* root);
    AVLNode<Key, Value>* getPredecessor(AVLNode<Key,Value>* root);
    void swapPred(AVLNode<Key,Value>* remove , AVLNode<Key,Value>* pred);

	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    insertHelper(keyValuePair, dynamic_cast<AVLNode<Key,Value>*>(this->mRoot));  
}

/** 
* Helper function for remove that recursively finds where the location to insert  
* the node. Once found it inserts and on it's way back up updates each node's 
* height, constantly checking to see if the node is unbalanced or not. If 
* unbalanced it calls the rebalance function which rebalnces the tree. 
* */
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertHelper(const std::pair<Key, Value>& keyValuePair, AVLNode<Key,Value>* root) 
{      
    if(this->mRoot == nullptr) {

        AVLNode<Key,Value>* leaf = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second,nullptr);
        leaf->setHeight(1);
        this->mRoot = leaf;
        return;

    } else if(keyValuePair.first < root->getKey()) {

        if(root->getLeft() == nullptr) 
        {
            AVLNode<Key,Value>* leaf = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, root);
            root->setLeft(leaf);
            leaf->setHeight(1);

        } else {

            insertHelper(keyValuePair, root->getLeft());
        }
    } 
    else if(keyValuePair.first > root->getKey()) 
    {
        if(root->getRight() == nullptr) 
        {
            AVLNode<Key,Value>* leaf = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, root);
            root->setRight(leaf);
            leaf->setHeight(1);
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

    if(root->getRight() && root->getLeft()) {
        root->setHeight((std::max(root->getRight()->getHeight(), root->getLeft()->getHeight()))+1);
    } else if(root->getRight()) {
        root->setHeight(root->getRight()->getHeight() + 1);
    } else if(root->getLeft()) {
        root->setHeight(root->getLeft()->getHeight() + 1);
    }


    bool unbalanced = returnBalanced(root);

    if(unbalanced) {
        rebalanceNode(root);
    }
}

/** 
* Algorithm that decides which way to rotate an unbalanced tree.
* Also updates the heights after rebalancing in constant time.
*/
template<typename Key, typename Value>
void AVLTree<Key,Value>::rebalanceNode(AVLNode<Key,Value>* root) {


    int lheight = 0;
    int rheight = 0;
    int rsubHeight  = 0;
    int lsubHeight = 0;

    AVLNode<Key,Value>* parent = root;
    AVLNode<Key,Value>* firstChild;

    bool one = false;

    if(root->getRight()) {
        rheight = root->getRight()->getHeight();
    }
    if(root->getLeft()) {
        lheight = root->getLeft()->getHeight();
    }

    if(rheight > lheight) 
    {
        firstChild = root->getRight();

        if(firstChild->getRight()) 
        {
            rsubHeight = firstChild->getRight()->getHeight();

        } 

        if(firstChild->getLeft()) 
        {
            lsubHeight = firstChild->getLeft()->getHeight();
        }

        if(rsubHeight >= lsubHeight) {

            this->leftRotate(parent);
            one = true;

        } else {

            this->rightRotate(firstChild);
            this->leftRotate(parent);

        }

    } else if(lheight > rheight) {

        firstChild = root->getLeft();

        if(firstChild->getRight()) 
        {
            rsubHeight = firstChild->getRight()->getHeight();
        } 

        if(firstChild->getLeft()) 
        {
            lsubHeight = firstChild->getLeft()->getHeight();
        }

        if(lsubHeight >= rsubHeight) 
        {
            this->rightRotate(parent);
            one = true;

        } else {

            this->leftRotate(firstChild);
            this->rightRotate(parent);
        }
    }

    if(one) 
    {
        parent->setHeight(parent->getHeight()-2);

    } else {

        parent->setHeight(parent->getHeight()-2);
        parent->getParent()->setHeight(parent->getParent()->getHeight()+1);
        firstChild->setHeight(firstChild->getHeight()-1);
    }
}

/**
* Function that recursively updates the heights at a given node.
*/
template<typename Key, typename Value>
void AVLTree<Key,Value>::updateHeight(AVLNode<Key,Value>* root) {
        
    AVLNode<Key,Value>* lchild = root->getLeft();
    AVLNode<Key,Value>* rchild = root->getRight();

    int rightHeight = 0;
    int leftHeight = 0;

    if(lchild) 
    {
        if(!lchild->getLeft() && !rchild->getRight()) {
            lchild->setHeight(1);
        } else {

            if(lchild->getLeft()) {
                leftHeight = lchild->getLeft()->getHeight();
            }
            if(lchild->getRight()) {
                rightHeight = lchild->getRight()->getHeight();
            }
            lchild->setHeight(std::max(rightHeight, leftHeight));
        }
    }

    rightHeight = 0;
    leftHeight = 0;

    if(rchild) 
    {
        if(!rchild->getLeft() && !rchild->getRight()) 
        {
            rchild->setHeight(1);

        } else {

            if(rchild->getLeft()) 
            {
                leftHeight = rchild->getLeft()->getHeight();
            }
            if(rchild->getRight()) 
            {
                rightHeight = rchild->getRight()->getHeight();
            }

            rchild->setHeight(std::max(rightHeight, leftHeight));
        }
    }

    if(lchild && rchild) 
    {
        root->setHeight(std::max(rchild->getHeight(), lchild->getHeight()));

    } else if(lchild) {

        root->setHeight(lchild->getHeight());

    } else if(rchild) {

        root->setHeight(rchild->getHeight());

    } else {

        root->setHeight(1);
    }
    
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   removeHelper(key, dynamic_cast<AVLNode<Key,Value>*>(this->mRoot));
}

/**
* Remove function that is recursievely called until it finds the node to remove.
* Once it removes, it updates the heights at the given node and recursively updates
* the heights going back up constantly checking for any imbalances and whether it
* needs to call rebelance node.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::removeHelper(const Key& key, AVLNode<Key,Value>* root) {
    
    AVLNode<Key,Value>* to_remove = nullptr;
    if(root == nullptr) {
        return;
    } else if(key < root->getKey()) {
        removeHelper(key,root->getLeft());
    } else if(key  > root->getKey()) {
        removeHelper(key,root->getRight());
    } else {
        to_remove = root;
    }

    if(!to_remove) return; 

    AVLNode<Key,Value>* parent = to_remove->getParent();

    if(!to_remove->getRight() && !to_remove->getLeft()) 
    {
        if(this->mRoot == to_remove) 
        {
            this->mRoot = nullptr;

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
        if(parent == nullptr) 
        {
            AVLNode<Key,Value>* child = to_remove->getLeft();
            to_remove->setLeft(nullptr);
            this->mRoot = child;
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
        if(parent == nullptr) 
        {
            AVLNode<Key,Value>* child = to_remove->getRight();
            to_remove->setRight(nullptr);
            this->mRoot = child;
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

        AVLNode<Key,Value>* predecessor = getPredecessor(to_remove);
        swapPred(to_remove, predecessor);
        removeHelper(key, to_remove);
    }

    if(parent) {
        if(parent->getRight() && parent->getLeft()) {
            parent->setHeight((std::max(parent->getRight()->getHeight(), parent->getLeft()->getHeight()))+1);
        } else if(parent->getRight()) {
            parent->setHeight(parent->getRight()->getHeight() + 1);
        } else if(parent->getLeft()) {
            parent->setHeight(parent->getLeft()->getHeight() + 1);
        }

        bool unbalanced = returnBalanced(parent);
        if(unbalanced) {
            rebalanceNode(parent);
        }
    }
}


template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getPredecessor(AVLNode<Key,Value>* root) {
    AVLNode<Key,Value>* temp = root->getLeft();
    if(temp == nullptr) {
        return nullptr;
    }
    while(temp->getRight()) 
    {
        temp = temp->getRight();
    }
    return temp;
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::swapPred(AVLNode<Key,Value>* remove , AVLNode<Key,Value>* pred)
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

    if(remove_right) 
    {
        pred->getParent()->setRight(pred);
    } else if(remove_left) {

        pred->getParent()->setLeft(pred);
    }
    
    if(root) 
    {
        this->mRoot = pred;
    } 
} 

template<typename Key, typename Value>
bool AVLTree<Key, Value>::returnBalanced(AVLNode<Key,Value>* root) const
{
    if(root->getRight() && root->getLeft()) 
    {
        if(abs(root->getRight()->getHeight() - root->getLeft()->getHeight()) > 1)
        {       
            return true;
        }
    } else if(root->getRight()) {
        if(root->getRight()->getHeight() > 1) 
        {
            return true;
        }
    } else if(root->getLeft()) {      
        if(root->getLeft()->getHeight() > 1) 
        {
            return true;
        }
    }

    return false;
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
