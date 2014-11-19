// Brandon Chai, 2014
// Node for a binary tree

#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED

template<class KeyType, class ItemType>
class BinaryNode
{
private:
    ItemType item;
    KeyType uniqueKey;
    BinaryNode<KeyType, ItemType>* leftChildPtr;
    BinaryNode<KeyType, ItemType>* rightChildPtr;
public:
    // constructors
    BinaryNode(const ItemType& anItem) {item = anItem; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const ItemType& anItem, const ItemType& key) {item = anItem; uniqueKey = key; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const ItemType& anItem,
               BinaryNode<KeyType, ItemType>* leftPtr,
               BinaryNode<KeyType, ItemType>* rightPtr) {item = anItem; leftChildPtr = leftPtr; rightChildPtr = rightPtr;}
    // mutators
    void setItem(const ItemType& anItem) {item = anItem;}
    void setUniqueKey(const ItemType& key) {uniqueKey = key;}
    void setLeftChildPtr(BinaryNode<KeyType, ItemType>* leftPtr) {leftChildPtr = leftPtr;}
    void setRightChildPtr(BinaryNode<KeyType, ItemType>* rightPtr) {rightChildPtr = rightPtr;}
    //accessors
    ItemType getItem() const {return item;}
    KeyType getUniqueKey() const {return uniqueKey;}
    BinaryNode<KeyType, ItemType>* getLeftChildPtr() const {return leftChildPtr;}
    BinaryNode<KeyType, ItemType>* getRightChildPtr() const {return rightChildPtr;}

    bool isLeaf() const {return (leftChildPtr == 0 && rightChildPtr == 0);}
};


#endif // BINARYNODE_H_INCLUDED
