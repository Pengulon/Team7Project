// Brandon Chai, 2014
// Hash Map ADT

#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
#include "HashEntry.h"
#include <iostream>
#include <fstream>
using namespace std;

template<class KeyType, class ItemType>
class HashMap
{
private:
    static const int TABLE_SIZE = 53;
    HashEntry<KeyType, ItemType>* htable [TABLE_SIZE];

    // internal functions
    int hashFunc(KeyType key);
    int getNumCollisions();
    int getNumEmpty();
    int getLoadFactor();
    int getLongestList();
    double getAverageListSize();
public:
    // Admin functions
    HashMap();
    ~HashMap();

    // Public user functions
    void insert(KeyType key, ItemType item);
    void printTable();
    void displayList();
    bool search(KeyType key, ItemType &foundItem);
    void stats();
    void remove(KeyType key, ItemType &deletedItem);
    bool writeToFile();
};

// Default constructor
template <class KeyType, class ItemType>
HashMap<KeyType, ItemType>::HashMap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        htable[i] = new HashEntry<KeyType, ItemType>();
}


// Destructor
template <class KeyType, class ItemType>
HashMap<KeyType, ItemType>::~HashMap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashEntry<KeyType, ItemType>* entry = htable[i];
        while (entry != NULL)
        {
            HashEntry<KeyType, ItemType>* prev = entry;
            entry = entry->getNext();
            delete prev;
        }
    }
}

//hashFunc - takes the key, sums the ascii value of each character
//           in the key and returns the total mod table size as index
template <class KeyType, class ItemType>
int HashMap<KeyType, ItemType>::hashFunc(KeyType key)
{
    int sum = 0;
    for (int k = 0; k < key.length(); k++)
        sum = sum + int(key[k]);
    return sum % TABLE_SIZE;
}

// insert - inserts item into the hash based on the key value
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::insert(KeyType key, ItemType item)
{
    int index = hashFunc(key);

    if (htable[index]->getKey() == "")
    {
        htable[index]->setKey(key);
        htable[index]->setItem(item);
    }
    else
    {
        HashEntry<KeyType, ItemType>* curr = htable[index];
        HashEntry<KeyType, ItemType>* newEntry = new HashEntry<KeyType, ItemType>(item, key, 0);
        while (curr->getNext() != NULL)
            curr = curr->getNext();
        curr->setNext(newEntry);
    }
}

//printTable - prints the hash table with indexes and indents to
//             indicate a linked list
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::printTable()
{
    cout << "\nPrinting hash table:\n";
    HashEntry<KeyType, ItemType>* curr;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        curr = htable[i];
        cout << "Index " << i << ":";
        if (curr->getItem() == NULL)
            cout << "//empty\n";
        else
            cout << (curr->getItem())->getTitle() << endl;
        curr = curr->getNext();
        while(curr!= NULL)
        {
            cout << "\t\t\t\t" << (curr->getItem())->getTitle() << endl;
            curr = curr->getNext();
        }
    }
}

// displayList - displays the each item starting from the beginning
//               of the list. //empty is displayed is no item is present
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::displayList()
{
    cout << "\nDisplaying List:\n";
    HashEntry<KeyType, ItemType>* curr;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        curr = htable[i];
        if (curr->getItem() == NULL)
            cout << "//empty\n";
        //if ((curr->getItem())->getTitle() == "")
        //    cout << "//empty\n";
        else
            cout << (curr->getItem())->getTitle() << endl;
        curr = curr->getNext();

        while(curr!= NULL)
        {
            if (curr->getItem() == NULL)
                cout << "//empty\n";
            //if ((curr->getItem())->getTitle() == "")
            //    cout << "//empty\n";
            else
                cout << (curr->getItem())->getTitle() << endl;
            curr = curr->getNext();
        }
    }
}

// search - searches for an item by its key value, return item if found
template <class KeyType, class ItemType>
bool HashMap<KeyType, ItemType>::search(KeyType key, ItemType &foundItem)
{
    int index = hashFunc(key);
    bool found = false;

    HashEntry<KeyType, ItemType>* curr = htable[index];
    while(curr != NULL)
    {
        if (curr->getKey() == key)
        {
            found = true;
            foundItem = curr->getItem();
        }
        curr = curr->getNext();
    }

    return found;
}

// getNumCollisions - returns number of collisions in hash table
template <class KeyType, class ItemType>
int HashMap<KeyType, ItemType>::getNumCollisions()
{
    int count = 0;
    HashEntry<KeyType, ItemType>* curr;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        curr = htable[i];

        while (curr->getNext())
        {
            curr = curr->getNext();
            count++;
        }
    }
    return count;
}

// getNumEmpty - returns number of empty slots in hash table
template <class KeyType, class ItemType>
int HashMap<KeyType, ItemType>::getNumEmpty()
{
    int count = 0;
    HashEntry<KeyType, ItemType>* curr;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        curr = htable[i];
        if (curr->getItem() == NULL)
            count++;
    }
    return count;
}

// getLoadFactor - returns load factor of hash table
template <class KeyType, class ItemType>
int HashMap<KeyType, ItemType>::getLoadFactor()
{
    int empty = getNumEmpty();
    int load = (TABLE_SIZE - empty)*100 / TABLE_SIZE;
    return load;
}

// stats - displays statistics for hash table
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::stats()
{
    cout << "\nStatistics:\n";
    cout << "Num of collisions  : " << getNumCollisions() << "\n";
    cout << "Load factor        : " << getLoadFactor() << "%\n";
    cout << "Longest list       : " << getLongestList() << "\n";
    cout << "Average list size  : " << getAverageListSize() << "\n";
}

//getLongestList - returns the length of the longest
//                 linked list in the hash table
template <class KeyType, class ItemType>
int HashMap<KeyType, ItemType>::getLongestList()
{
    int longest = 0;
    HashEntry<KeyType, ItemType>* curr;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int length = 0;
        curr = htable[i];
        curr = curr->getNext();
        while(curr != NULL)
        {
            length++;
            curr = curr->getNext();
        }
        if (length > longest)
            longest = length;
    }
    return longest;
}
// getAverageListSize - returns the average length of
//                      the linked lists in the hash table
template <class KeyType, class ItemType>
double HashMap<KeyType, ItemType>::getAverageListSize()
{
    if (getNumCollisions()== 0)
        return 0;
    else
    {
        int sum = 0;
        HashEntry<KeyType, ItemType>* curr;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            curr = htable[i];
            curr = curr->getNext();
            while(curr != NULL)
            {
                sum++;
                curr = curr->getNext();
            }
        }
        return (double)sum/getNumCollisions();
    }
}

// remove -
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::remove(KeyType key, ItemType &deletedItem)
{
    int index = hashFunc(key);

    HashEntry<KeyType, ItemType>* ptrToDelete;
    HashEntry<KeyType, ItemType>* p1;
    HashEntry<KeyType, ItemType>* p2;

    // case 0 - bucket is empty
    if (htable[index]->getItem() == NULL && htable[index]->getKey() == "")
        cout << "\"" << key << "\" was not found in the Hash Table\n";

    // case 1 - only 1 item in bucket, which is key
    else if (htable[index]->getKey() == key && htable[index]->getNext() == NULL)
    {
        deletedItem = htable[index]->getItem();
        htable[index]->setItem(NULL);
        htable[index]->setKey("");
        //cout << "\"" << key << "\" was removed from the Hash Table\n";
    }

    // case 2 - match in 1st bucket item, but more bucket items exist
    else if (htable[index]->getKey() == key)
    {
        deletedItem = htable[index]->getItem();
        ptrToDelete = htable[index];
        htable[index] = htable[index]->getNext();
        delete ptrToDelete;
        //cout << "\"" << key << "\" was removed from the Hash Table\n";
    }
    // case 3 - bucket contains items but first item is not match
    else
    {
        p1 = htable[index]->getNext();
        p2 = htable[index];

        while(p1 != NULL && p1->getKey() != key)
        {
            p2 = p1;
            p1 = p1->getNext();
        }
        // case 3.1 - no match found
        if (p1 == NULL)
            cout << "\"" << key << "\" was not found in the Hash Table\n";
        // case 3.2 - match found
        else
        {
            deletedItem = p1->getItem();
            ptrToDelete = p1;
            p1 = p1->getNext();
            p2->setNext(p1);
            delete ptrToDelete;
            //cout << "\"" << key << "\" was removed from the Hash Table\n";
        }
    }
}
// writeToFile -
template <class KeyType, class ItemType>
bool HashMap<KeyType, ItemType>::writeToFile()
{
   	ofstream outFile("output.txt");
    int i = 0;
    HashEntry<KeyType, ItemType>* curr;

    while (i < TABLE_SIZE)
    {
        if (htable[i]->getItem())
        {
            outFile << (htable[i]->getItem())->getYear();
            outFile << " ";
            outFile << (htable[i]->getItem())->getGenre();
            outFile << " ";
            outFile << (htable[i]->getItem())->getRating();
            outFile << " ";
            outFile << (htable[i]->getItem())->getTitle();
            outFile << endl;
        }

        if (htable[i]->getNext())
        {
            curr = htable[i]->getNext();
            while (curr)
            {
                outFile << (curr->getItem())->getYear();
                outFile << " ";
                outFile << (curr->getItem())->getGenre();
                outFile << " ";
                outFile << (curr->getItem())->getRating();
                outFile << " ";
                outFile << (curr->getItem())->getTitle();
                outFile << endl;
                curr = curr->getNext();
            }
        }
        i++;
    }
    outFile.close();

    cout << "Save successful\n";
    return true;
}

#endif // HASHMAP_H_INCLUDED
