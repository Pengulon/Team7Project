// Brandon Chai, 2014
// Node for a binary tree

#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED

template<class ItemType>
class BinaryNode
{
private:
    ItemType              item;
    ItemType              uniqueKey;
    BinaryNode<ItemType>* leftChildPtr;
    BinaryNode<ItemType>* rightChildPtr;
public:
    // constructors
    BinaryNode(const ItemType& anItem) {item = anItem; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const ItemType& anItem, const ItemType& key) {item = anItem; uniqueKey = key; leftChildPtr = 0; rightChildPtr = 0;}
    BinaryNode(const ItemType& anItem,
               BinaryNode<ItemType>* leftPtr,
               BinaryNode<ItemType>* rightPtr) {item = anItem; leftChildPtr = leftPtr; rightChildPtr = rightPtr;}
    // mutators
    void setItem(const ItemType& anItem) {item = anItem;}
    void setUniqueKey(const ItemType& anItem) {uniqueKey = anItem;}
    void setLeftChildPtr(BinaryNode<ItemType>* leftPtr) {leftChildPtr = leftPtr;}
    void setRightChildPtr(BinaryNode<ItemType>* rightPtr) {rightChildPtr = rightPtr;}
    //accessors
    ItemType getItem() const {return item;}
    ItemType getUniqueKey() const {return uniqueKey;}
    BinaryNode<ItemType>* getLeftChildPtr() const {return leftChildPtr;}
    BinaryNode<ItemType>* getRightChildPtr() const {return rightChildPtr;}

    bool isLeaf() const {return (leftChildPtr == 0 && rightChildPtr == 0);}
};


#endif // BINARYNODE_H_INCLUDED
