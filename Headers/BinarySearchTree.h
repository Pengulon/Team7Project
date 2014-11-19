// Brandon Chai, 2014
// Binary Search Tree ADT

#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include <iostream>
using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
    using BinaryNodeTree<ItemType>::rootPtr; //declaration of base class field
    using BinaryNodeTree<ItemType>::count; //declaration of base class field
protected:
    // returns ptr to a tree with correctly inserted node
    BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
                                        BinaryNode<ItemType>* newNode);
    // prints the item in each node greater than key
    void _printItemsGreater(BinaryNode<ItemType>* subTreePtr, ItemType& key);
public:
    // insert a node with item field at the correct location
    bool add(const ItemType& newData);

    // insert a node at with both item and key fields at the correct location
    bool add(const ItemType& item, const ItemType& key);

	// find a target node
	bool getEntry(const ItemType& target, ItemType& returnedItem) const;

	// calls internal function '_printItemsGreater'
	void printItemsGreater(ItemType key);

	// searches for target and displays success of the search
    void search(const ItemType& target);
};

// search - searches for target and displays item if found
template<class ItemType>
void BinarySearchTree<ItemType>::search(const ItemType& target)
{
    ItemType returnedItem;

    cout << "\nSearching for " << target << endl;
    if (getEntry(target, returnedItem))
        cout << "Found: " << returnedItem << endl;
    else
        cout << target << " not found\n";
}

// getEntry - returns true if target is found in the tree, false otherwise
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& target, ItemType& returnedItem) const
{
    if (rootPtr == 0)
        return false;

    BinaryNode<ItemType>* pWalk = rootPtr;

    while( pWalk )
    {
        if( target < pWalk->getUniqueKey())
            pWalk = pWalk->getLeftChildPtr();
        else
            if( target > pWalk->getUniqueKey())
                pWalk = pWalk->getRightChildPtr();
            else
            {
                returnedItem = pWalk->getItem();
                return true;
            }
    }
    return false;
}

// add - insert a node at with item field at the correct location
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    count++;

    return true;
}

// add - insert a node at with both item and key fields at the correct location
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& item, const ItemType& key)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(item, key);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    count++;

    return true;
}

// insertInorder - returns ptr to a tree with correctly inserted node
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
                                        BinaryNode<ItemType>* newNode)
{
    if (subTreePtr == 0)
        return newNode;
    else if (subTreePtr->getItem() > newNode->getItem())
    {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

// printItemsGreater - calls internal function '_printItemsGreater'
template<class ItemType>
void BinarySearchTree<ItemType>::printItemsGreater(ItemType key)
{
    cout << "\nPrinting items greater than " << key << "\n";
    _printItemsGreater(rootPtr, key);
}

// _printItemsGreater - prints the item in each node greater than key
template<class ItemType>
void BinarySearchTree<ItemType>::_printItemsGreater(BinaryNode<ItemType>* subTreePtr, ItemType& key)
{
    if (subTreePtr == 0)
        return;
    else if (subTreePtr->getUniqueKey() > key)
    {
        _printItemsGreater(subTreePtr->getLeftChildPtr(), key);
        cout << subTreePtr->getItem() << endl;
        _printItemsGreater(subTreePtr->getRightChildPtr(), key);
    }
    else
        _printItemsGreater(subTreePtr->getRightChildPtr(), key);
}

#endif // BINARYSEARCHTREE_H_INCLUDED
