// Brandon Chai, 2014
// HashEntry for a Hash Map
// Team 1 Project

#ifndef HASHENTRY_H_INCLUDED
#define HASHENTRY_H_INCLUDED
#include <iostream>

template<class KeyType, class ItemType>
class HashEntry
{
private:
    ItemType item;
    KeyType key;
    HashEntry<KeyType, ItemType>* nextPtr;
public:
    // Constructors
    HashEntry() {item = NULL; key = ""; nextPtr = NULL;}
    HashEntry(ItemType newEntry, KeyType newKey,
              HashEntry<KeyType, ItemType>* nextEntryPtr) {item = newEntry; key = newKey; nextPtr = nextEntryPtr;}

    // Accessors
    ItemType getItem() const {return item;}							//Function to return the item
    KeyType getKey() const {return key;}							//Function to return the key
    HashEntry<KeyType, ItemType>* getNext() const {return nextPtr;}		//Function to get the next node

    // Mutators
    void setItem(const ItemType& newEntry) {item = newEntry;}		//Function to set the item
    void setKey(const KeyType& newKey) {key = newKey;}				//Function to set the key
    void setNext(HashEntry<KeyType, ItemType>* nextEntryPtr) {nextPtr = nextEntryPtr;}		//Function to set the next node in 
																							//linked list of the index in the hashtable.
		
    // Overloaded operators
    bool operator==(const HashEntry<KeyType, ItemType>& rightHandItem) const;
    bool operator>(const HashEntry<KeyType, ItemType>& rightHandItem) const;
};

// == - Checks to see if value is same key
template <class KeyType, class ItemType>
bool HashEntry<KeyType, ItemType>::operator==
                    (const HashEntry<KeyType, ItemType>& rightHandItem) const
{
    return (key == rightHandItem.getKey());
}

// == - Checks to see if value is greater than key
template <class KeyType, class ItemType>
bool HashEntry<KeyType, ItemType>::operator>
                    (const HashEntry<KeyType, ItemType>& rightHandItem) const
{
    return (key > rightHandItem.getKey());
}
#endif // HASHENTRY_H_INCLUDED
