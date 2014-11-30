// Brandon Chai, 2014
// Binary node tree abstract base class
// Team 1 Project

#ifndef BINARYNODETREE_H_INCLUDED
#define BINARYNODETREE_H_INCLUDED

#include "BinaryNode.h"
#include "Stack.h"
#include <algorithm>
#include <iostream>
using namespace std;

template<class KeyType, class ItemType>
class BinaryNodeTree
{
protected:
    BinaryNode<KeyType, ItemType>* rootPtr; // ptr to root node
    int count; // number of nodes in tree

    // returns height of subTreePtr
    int getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const;

    // deletes all nodes from the tree
    void destroyTree(BinaryNode<KeyType, ItemType>* subTreePtr);

    // returns a ptr to a copy of the tree rooted at subTreePtr
    BinaryNode<KeyType, ItemType>* copyTree(const BinaryNode<KeyType, ItemType>* treePtr) const;

    // internal traverse
    void preorder(void visit(ItemType&),
                 BinaryNode<KeyType, ItemType>* treePtr) const;
    void inorder(void visit(ItemType&),
                 BinaryNode<KeyType, ItemType>* treePtr) const;
    void postorder(void visit(ItemType&),
                   BinaryNode<KeyType, ItemType>* treePtr) const;
public:
    //constructors
    BinaryNodeTree();
    BinaryNodeTree(const ItemType& rootItem);
    BinaryNodeTree(const ItemType& rootItem,
                   const BinaryNodeTree<KeyType, ItemType>* leftTreePtr,
                   const BinaryNodeTree<KeyType, ItemType>* rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<KeyType, ItemType>& tree);

    //destructor
    virtual ~BinaryNodeTree() {clear();}

    //accessors
    int getHeight() const {return getHeightHelper(rootPtr);}
    int getCount() const {return count;}
    ItemType getRootData() const {return rootPtr->getItem();}

    //mutator
    void setRootData(const ItemType& data) {rootPtr->setItem(data);}

    // abstract functions to be implemented by derived class
    /*
	virtual bool add(const ItemType & newData) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    virtual void printItemsGreater(ItemType key) = 0;
    virtual void search(const ItemType& target) = 0;*/

    // common functions for all binary trees
    void clear() {destroyTree(rootPtr); count = 0;}				//Function to delete the nodes in the tree
    bool isEmpty() const {return count == 0;}					//Function to see if tree is empty

    void recursivePreorderTraverse(void visit(ItemType&)) const;
    void recursiveInorderTraverse(void visit(ItemType&)) const;
    void recursivePostorderTraverse(void visit(ItemType&)) const;

    void iterativePreorderTraverse(void visit(ItemType&));
    void iterativeInorderTraverse(void visit(ItemType&));
    void iterativePostorderTraverse(void visit(ItemType&));

    void printIndented();
    void printTreeLevelRec(BinaryNode<KeyType, ItemType>* node, int desired);
    void tab(int i);
};

// Default constructor
template<class KeyType, class ItemType>
BinaryNodeTree<KeyType, ItemType>::BinaryNodeTree()
{
    rootPtr = 0;
    count = 0;
}

// Constructor with item provided
template<class KeyType, class ItemType>
BinaryNodeTree<KeyType, ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
    rootPtr = new BinaryNodeTree<KeyType, ItemType>(rootItem, 0, 0);
    count = 1;
}

// Constructor with item and left and right children provided
template<class KeyType, class ItemType>
BinaryNodeTree<KeyType, ItemType>::BinaryNodeTree(const ItemType& rootItem,
                          const BinaryNodeTree<KeyType, ItemType>* leftTreePtr,
                          const BinaryNodeTree<KeyType, ItemType>* rightTreePtr)
{
    rootPtr = new BinaryNodeTree<KeyType, ItemType>(rootItem,
                                           copyTree(leftTreePtr->rootPtr),
                                           copyTree(rightTreePtr->rootPtr));
    count = 1 + leftTreePtr->getCount() + rightTreePtr()->getCount();
}

// Copy constructor
template<class KeyType, class ItemType>
BinaryNodeTree<KeyType, ItemType>::
                        BinaryNodeTree(const BinaryNodeTree<KeyType, ItemType>& treePtr)
{
    rootPtr = copyTree(treePtr.rootPtr);
    count = treePtr->getCount();
}

// destroyTree - deletes all nodes from subTreePtr
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     destroyTree(BinaryNode<KeyType, ItemType>* subTreePtr)
{
    if (subTreePtr != 0)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

// copyTree - returns a ptr to a copy of the tree
template<class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinaryNodeTree<KeyType, ItemType>::
                          copyTree(const BinaryNode<KeyType, ItemType>* treePtr) const
{
    BinaryNodeTree<KeyType, ItemType>* newTreePtr = 0;			//New BinaryNodeTree pointer set equal to null.
    if (treePtr != 0)
    {
        newTreePtr = new BinaryNode<KeyType, ItemType>(treePtr->getItem(),			//Allocate a new node.
                                              0, 0);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getleftChildPtr()));			//Set the left child
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));		//Set the right child
    }
    return newTreePtr;
}

// getHeightHelper - returns the height of a tree
template<class KeyType, class ItemType>
int BinaryNodeTree<KeyType, ItemType>::
    getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const
{
    if (subTreePtr == 0)
        return 0;
    else
        return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()),
                       getHeightHelper(subTreePtr->getRightChildPtr()));
}

// recursivePreorderTraverse - calls internal preorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     recursivePreorderTraverse(void visit(ItemType&)) const
{
    if (rootPtr == 0)
        cout << "\nThe tree is empty\n";
    else
    {
        cout << "\nPrinting preorder(recursively):"<< endl;
        preorder(visit, rootPtr);
    }
}

// recursiveInorderTraverse - calls internal inorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     recursiveInorderTraverse(void visit(ItemType&)) const
{
    if (rootPtr == 0)
        cout << "\nThe tree is empty\n";
    else
    {
        //cout << "\nPrinting inorder(recursively):"<< endl;
        inorder(visit, rootPtr);
    }
}

// recursivePostorderTraverse - calls internal postorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     recursivePostorderTraverse(void visit(ItemType&)) const
{
    if (rootPtr == 0)
        cout << "\nThe tree is empty\n";
    else
    {
        cout << "\nPrinting postorder(recursively):"<< endl;
        postorder(visit, rootPtr);
    }
}

// recursivePreorderTraverse - prints the item at each node through recursive preorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     preorder(void visit(ItemType&), BinaryNode<KeyType, ItemType>* treePtr) const
{
    if (treePtr != 0)
    {
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

// recursiveInorderTraverse - prints the item at each node through recursive inorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     inorder(void visit(ItemType&), BinaryNode<KeyType, ItemType>* treePtr) const
{
    if (treePtr != 0)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

// recursivePostorderTraverse - prints the item at each node through recursive postorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::
     postorder(void visit(ItemType&), BinaryNode<KeyType, ItemType>* treePtr) const
{
    if (treePtr != 0)
    {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}

// iterativePreorderTraverse - prints the item at each node through iterative preorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::iterativePreorderTraverse(void visit(ItemType&))
{
    if (rootPtr == 0)
    {
        cout << "\nTree is empty\n";
        return;
    }

    cout << "\nPrinting preorder(iteratively): \n";

    Stack<BinaryNode<KeyType, ItemType>* >* s = new Stack<BinaryNode<KeyType, ItemType>* >();		//New stack object
    BinaryNode<KeyType, ItemType>* node;								//BinaryNode pointer
    s->push(rootPtr);													//Push the root to the stack

	//Loop to print the nodes of the tree in iterative preorder.
    while(s->getCount() > 0)
    {
        s->pop(node);
        ItemType theItem = node->getItem();
        visit(theItem);
        if (node->getRightChildPtr())
            s->push(node->getRightChildPtr());
        if (node->getLeftChildPtr())
            s->push(node->getLeftChildPtr());
    }
}

// iterativeInorderTraverse - prints the item at each node through iterative inorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::iterativeInorderTraverse(void visit(ItemType&))
{
    if (rootPtr == 0)
    {
        cout << "\nTree is empty\n";
        return;
    }

    cout << "\nPrinting inorder(iteratively): \n";

    Stack<BinaryNode<KeyType, ItemType>* >* s = new Stack<BinaryNode<KeyType, ItemType>* >();		//Stack Object
    BinaryNode<KeyType, ItemType>* node = rootPtr;									//BinaryNode pointer set equal to the rootPtr

	//Loop to print the nodes in the tree iteratively inorder.
    while(s->getCount() > 0 || node != 0)
    {
        if (node != 0)
        {
            s->push(node);
            node = node->getLeftChildPtr();
        }

        else
        {
            s->pop(node);
            ItemType theItem = node->getItem();
            visit(theItem);
            node = node->getRightChildPtr();
        }
    }
}

// iterativePostorderTraverse - prints the item at each node through iterative postorder traversal
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::iterativePostorderTraverse(void visit(ItemType&))
{
    if (rootPtr == 0)
    {
        cout << "\nTree is empty\n";
        return;
    }

    cout << "\nPrinting postorder(iteratively): \n";

    Stack<BinaryNode<KeyType, ItemType>* >* s = new Stack<BinaryNode<KeyType, ItemType>* >();			//Stack object
    s->push(rootPtr);											//Push the root to the stack

    BinaryNode<KeyType, ItemType>* popVal;						//BinaryNode pointer to point to popped value
    BinaryNode<KeyType, ItemType>* temp;						//Temporary BinaryNode pointer
    BinaryNode<KeyType, ItemType>* prev = 0;					//BinaryNode pointer to point to previous node
    ItemType theItem;

	//Loop to display the nodes in the tree iteratively postorder.
    while(s->getCount() > 0)
    {
        temp = s->getTop();						//Set temp equal to the top of the stack

        if(prev == 0 || prev->getLeftChildPtr() == temp || prev->getRightChildPtr() == temp)
        {
            if (temp->getLeftChildPtr())
                s->push(temp->getLeftChildPtr());
            else if (temp->getRightChildPtr())
                s->push(temp->getRightChildPtr());
            else
            {
                theItem = temp->getItem();
                visit(theItem);
                s->pop(popVal);
            }
        }
        if (temp->getLeftChildPtr() == prev)
        {
            if (temp->getRightChildPtr())
                s->push(temp->getRightChildPtr());
            else
            {
                theItem = temp->getItem();
                visit(theItem);
                s->pop(popVal);
            }
        }
        if (temp->getRightChildPtr() == prev)
        {
            theItem = temp->getItem();
            visit(theItem);
            s->pop(popVal);
        }
        prev = temp;
    }
}

// printIndented - calls internal function 'printTreeLevelRec' to print an indented list
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::printIndented()
{
    if (rootPtr == 0)
        return;

    cout << "\nPrinting indented list\n";
    printTreeLevelRec(rootPtr, 1);
}

// printTreeLevelRec - recursive call to print an indented list of the items at each node with its corresponding level
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::printTreeLevelRec(BinaryNode<KeyType, ItemType>* node, int desired)
{
    if(node == 0)
        return;
    tab(desired-1);
    cout << desired << ".  " << (node->getItem())->getTitle() << "\n";
    printTreeLevelRec(node->getRightChildPtr(), desired+1);
    printTreeLevelRec(node->getLeftChildPtr(), desired+1);
}

//tab - displays tab
template<class KeyType, class ItemType>
void BinaryNodeTree<KeyType, ItemType>::tab(int i)
{
    while(i>0)
    {
        cout << "    ";
        i--;
    }
}

#endif // BINARYNODETREE_H_INCLUDED








