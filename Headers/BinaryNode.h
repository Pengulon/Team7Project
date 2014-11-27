// Brandon Chai, 2014
// Node for a binary tree
// Team 1 Project

#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED

template<class KeyType, class ItemType>
class BinaryNode
{
private:
    ItemType item;
    KeyType key;
    BinaryNode<KeyType, ItemType>* leftChildPtr;
    BinaryNode<KeyType, ItemType>* rightChildPtr;
public:
    // constructors
    BinaryNode(const ItemType& anItem) {item = anItem; key = ""; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const KeyType& aKey, const ItemType& anItem) {item = anItem; key = aKey; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const KeyType& aKey, const ItemType& anItem,
               BinaryNode<KeyType, ItemType>* leftPtr,
               BinaryNode<KeyType, ItemType>* rightPtr) {item = anItem; key = aKey; leftChildPtr = leftPtr; rightChildPtr = rightPtr;}
    // mutators
    void setItem(const ItemType& anItem) {item = anItem;}					//Function sets the item
    void setKey(const KeyType& aKey) {key = aKey;}							//Function sets the key
    void setLeftChildPtr(BinaryNode<KeyType, ItemType>* leftPtr) {leftChildPtr = leftPtr;}		//Function sets the leftchild of the tree
    void setRightChildPtr(BinaryNode<KeyType, ItemType>* rightPtr) {rightChildPtr = rightPtr;}		//Function sets the rightchild of the tree
    //accessors
    ItemType getItem() const {return item;}							//Function returns the item
    KeyType getKey() const {return key;}							//Function returns the key
    BinaryNode<KeyType, ItemType>* getLeftChildPtr() const {return leftChildPtr;}			//Function returns the leftchild
    BinaryNode<KeyType, ItemType>* getRightChildPtr() const {return rightChildPtr;}			//Function returns the rightchild

    bool isLeaf() const {return (leftChildPtr == 0 && rightChildPtr == 0);}					//Function checks to see if the node is a leaf.
};


#endif // BINARYNODE_H_INCLUDED
