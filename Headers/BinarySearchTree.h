// Brandon Chai, 2014
// Binary Search Tree ADT, used to print sorted list
// Team 1 Project

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

    // removes item with key value
    BinaryNode<KeyType, ItemType>* deleteNode(BinaryNode<KeyType, ItemType>* rootPtr, KeyType key);

    // returns leftmost node in right subtree
    BinaryNode<KeyType, ItemType>* minValueNode(BinaryNode<KeyType, ItemType>* nodePtr);
public:
    // insert a node with item field at the correct location
    bool add(const ItemType& newData);

    // insert a node at with both item and key fields at the correct location
    bool add(const KeyType& key, const ItemType& item);

    // remove an item using key
    bool remove (KeyType key);

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

    BinaryNode<KeyType, ItemType>* pWalk = rootPtr;		//BinaryNode pointer set to the root of the tree

	//Loop to search for the wanted key
    while( pWalk )
    {
        if( key < pWalk->getKey())
            pWalk = pWalk->getLeftChildPtr();
        else
            if( key > pWalk->getKey())
                pWalk = pWalk->getRightChildPtr();
            else
            {
                returnedItem = pWalk->getItem();
                return true;
            }
    }
    return false;
}

// add - insert a node with item field at the correct location
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::add(const ItemType& newData)
{
    BinaryNode<KeyType, ItemType>* newNodePtr = new BinaryNode<KeyType, ItemType>(newData);	//New BinaryNode pointer to store insert data
    rootPtr = insertInorder(rootPtr, newNodePtr);					//Insert into the binary tree
    count++;				//Update counter

    return true;
}

// add - insert a node with both item and key fields at the correct location
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::add(const KeyType& key, const ItemType& item)
{
    BinaryNode<KeyType, ItemType>* newNodePtr = new BinaryNode<KeyType, ItemType>(key, item);	//New BinaryNode pointer to store insert data.
    rootPtr = insertInorder(rootPtr, newNodePtr);			//Insert into binary tree.
    count++;						//Update counter

    return true;
}

// insertInorder - Function inserts the data inorder format
// and returns ptr to a tree with correctly inserted node.
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

// remove - Function calls the deleteNode function which would return the
// new tree with the key deleted.
template<class KeyType, class ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    ItemType foundItem;
    if (getEntry(key, foundItem))
    {
       rootPtr = deleteNode(rootPtr, key);
       return true;
    }

    else
        return false;

}

// minValueNode - Function gets the lowest value node in the tree and returns it.
template<class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::minValueNode(BinaryNode<KeyType, ItemType>* nodePtr)
{
    BinaryNode<KeyType, ItemType>* current = nodePtr;

    /* loop down to find the leftmost leaf */
    while (current->getLeftChildPtr() != NULL)
        current = current->getLeftChildPtr();

    return current;
}

// deleteNode - Function deletes the requested key from the user from the binary tree.
template<class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::deleteNode(BinaryNode<KeyType, ItemType>* rootPtr, KeyType key)
{
    // base case
    if (rootPtr == NULL) return rootPtr;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < rootPtr->getKey())
        rootPtr->setLeftChildPtr(deleteNode(rootPtr->getLeftChildPtr(), key));

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > rootPtr->getKey())
        rootPtr->setRightChildPtr(deleteNode(rootPtr->getRightChildPtr(), key));

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (rootPtr->getLeftChildPtr() == NULL)
        {
            BinaryNode<KeyType, ItemType>* temp = rootPtr->getRightChildPtr();
            delete rootPtr;
            return temp;
        }
        else if (rootPtr->getRightChildPtr() == NULL)
        {
            BinaryNode<KeyType, ItemType>* temp = rootPtr->getLeftChildPtr();
            delete rootPtr;
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        BinaryNode<KeyType, ItemType>* temp = minValueNode(rootPtr->getRightChildPtr());

        // Copy the inorder successor's content to this node
        rootPtr->setKey(temp->getKey());
        rootPtr->setItem(temp->getItem());

        // Delete the inorder successor
        rootPtr->setRightChildPtr(deleteNode(rootPtr->getRightChildPtr(), temp->getKey()));
    }
    return rootPtr;
}
#endif // BINARYSEARCHTREE_H_INCLUDED
