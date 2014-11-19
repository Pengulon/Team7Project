// Brandon Chai, 2014
// Node for a binary tree

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
    void setItem(const ItemType& anItem) {item = anItem;}
    void setKey(const KeyType& aKey) {key = aKey;}
    void setLeftChildPtr(BinaryNode<KeyType, ItemType>* leftPtr) {leftChildPtr = leftPtr;}
    void setRightChildPtr(BinaryNode<KeyType, ItemType>* rightPtr) {rightChildPtr = rightPtr;}
    //accessors
    ItemType getItem() const {return item;}
    KeyType getKey() const {return key;}
    BinaryNode<KeyType, ItemType>* getLeftChildPtr() const {return leftChildPtr;}
    BinaryNode<KeyType, ItemType>* getRightChildPtr() const {return rightChildPtr;}

    bool isLeaf() const {return (leftChildPtr == 0 && rightChildPtr == 0);}
};


#endif // BINARYNODE_H_INCLUDED
