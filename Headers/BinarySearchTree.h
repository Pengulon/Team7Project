// Brandon Chai, 2014
// Binary Search Tree ADT

#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include <iostream>
using namespace std;

template<class KeyType, class ItemType>
class BinarySearchTree : public BinaryNodeTree<KeyType, ItemType>
{
private:
    using BinaryNodeTree<KeyType, ItemType>::rootPtr; //declaration of base class field
    using BinaryNodeTree<KeyType, ItemType>::count; //declaration of base class field
protected:
    // returns ptr to a tree with correctly inserted node
    BinaryNode<KeyType, ItemType>* insertInorder(BinaryNode<KeyType, ItemType>* subTreePtr,
                                        BinaryNode<KeyType, ItemType>* newNode);
    // prints the item in each node greater than key
    void _printItemsGreater(BinaryNode<KeyType, ItemType>* subTreePtr, KeyType& key);
public:
    // insert a node with item field at the correct location
    bool add(const ItemType& newData);

    // insert a node at with both item and key fields at the correct location
    bool add(const KeyType& key, const ItemType& item);

	// find a key node
	bool getEntry(const KeyType& key, ItemType& returnedItem) const;

	// calls internal function '_printItemsGreater'
	void printItemsGreater(ItemType key);

	// searches for key and displays success of the search
    void search(const KeyType& key);
};

// search - searches for key and displays item if found
template<class KeyType, class ItemType>
void BinarySearchTree<KeyType, ItemType>::search(const KeyType& key)
{
    ItemType returnedItem;

    cout << "\nSearching for \" " << key << " \" " << endl;
    if (getEntry(key, returnedItem))
    {
        cout << "Found: " << returnedItem->getTitle() << endl;
        cout << "Year: " << returnedItem->getYear() << endl;
        cout << "Genre: " << returnedItem->getGenre() << endl;
        cout << "Rating: " << returnedItem->getRating() << endl;
    }
    else
        cout << " \" " << key << " \" was not found\n";
}

// getEntry - returns true if key is found in the tree, false otherwise
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::getEntry(const KeyType& key, ItemType& returnedItem) const
{
    if (rootPtr == 0)
        return false;

    BinaryNode<KeyType, ItemType>* pWalk = rootPtr;

    while( pWalk )
    {
        if( key < pWalk->getUniqueKey())
            pWalk = pWalk->getLeftChildPtr();
        else
            if( key > pWalk->getUniqueKey())
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
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::add(const ItemType& newData)
{
    BinaryNode<KeyType, ItemType>* newNodePtr = new BinaryNode<KeyType, ItemType>(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    count++;

    return true;
}

// add - insert a node at with both item and key fields at the correct location
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::add(const KeyType& key, const ItemType& item)
{
    BinaryNode<KeyType, ItemType>* newNodePtr = new BinaryNode<KeyType, ItemType>(key, item);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    count++;

    return true;
}

// insertInorder - returns ptr to a tree with correctly inserted node
template<class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::insertInorder(BinaryNode<KeyType, ItemType>* subTreePtr,
                                        BinaryNode<KeyType, ItemType>* newNode)
{
    if (subTreePtr == 0)
        return newNode;
    else if (subTreePtr->getKey() > newNode->getKey())
    {
        BinaryNode<KeyType, ItemType>* tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<KeyType, ItemType>* tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

// printItemsGreater - calls internal function '_printItemsGreater'
template<class KeyType, class ItemType>
void BinarySearchTree<KeyType, ItemType>::printItemsGreater(ItemType key)
{
    cout << "\nPrinting items greater than " << key << "\n";
    _printItemsGreater(rootPtr, key);
}

// _printItemsGreater - prints the item in each node greater than key
template<class KeyType, class ItemType>
void BinarySearchTree<KeyType, ItemType>::_printItemsGreater(BinaryNode<KeyType, ItemType>* subTreePtr, KeyType& key)
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
