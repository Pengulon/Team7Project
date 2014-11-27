// Brandon Chai, 2014
// Hash Map ADT
// Team 1 Project

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
    HashMap();				//Constructor
    ~HashMap();				//Destructor

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
	//Initialize all the elements in the hashtable
    for (int i = 0; i < TABLE_SIZE; i++)
        htable[i] = new HashEntry<KeyType, ItemType>();	
}


// Destructor
template <class KeyType, class ItemType>
HashMap<KeyType, ItemType>::~HashMap()
{
	//Deletes all the elements in the hashtable with addition to the
	//linked lists that handled collisions.
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
        sum = sum + int(key[k]);			//Gets the sum of the ASCII value of the whole string.
    return sum % TABLE_SIZE;				//Return the index on where to store the string data
}

// insert - inserts item into the hash based on the key value
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::insert(KeyType key, ItemType item)
{
    int index = hashFunc(key);					//Get the index on where to insert

	//If the index contains nothing, insert it as the first item.
	//Otherwise, insert it as a linkedlist to that index.
    if (htable[index]->getKey() == "")
    {
        htable[index]->setKey(key);					//Set the key in the index
        htable[index]->setItem(item);				//Set the item in the index
    }
    else
    {
        HashEntry<KeyType, ItemType>* curr = htable[index];						//HashEntry ptr to the first item in the index of the hashtable
        HashEntry<KeyType, ItemType>* newEntry = new HashEntry<KeyType, ItemType>(item, key, 0);		//New HashEntry ptr to be inserted
        //Find the element stored in the linkedlist
		while (curr->getNext() != NULL)
            curr = curr->getNext();					
        curr->setNext(newEntry);					//Set the new HashEntry to the end of the linkedlist 
    }
}

//printTable - prints the hash table with indexes and indents to
//             indicate a linked list
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::printTable()
{
    cout << "\nPrinting hash table:\n";
    HashEntry<KeyType, ItemType>* curr;				//HashEntry pointer
    
	//This loop displays each value in the hashtable and prints empty if nothing is contained.
	//It also prints the linkedlist of the index with an indented space.
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
    HashEntry<KeyType, ItemType>* curr;			//HashEntry pointer 
	
	//Loop to display each value in the hashtable including linkedlists with no indents.
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
    int index = hashFunc(key);				//Get the index of the key
    bool found = false;

    HashEntry<KeyType, ItemType>* curr = htable[index];			//Set the HashEntry pointer to the index of the hashtable
    
	//Loop to see if the key is in the hashtable and the linkedlist at the index if any.
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
    HashEntry<KeyType, ItemType>* curr;					//HashEntry pointer
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        curr = htable[i];							
		//Loop to check if there is a linkedlist at the index and if there is, increment
		//count for every item in the linkedlist.
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
    HashEntry<KeyType, ItemType>* curr;					//HashEntry pointer
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
    int empty = getNumEmpty();					//Get the number of empty spaces in the hashtable.
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
    HashEntry<KeyType, ItemType>* curr;				//HashEntry pointer
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int length = 0;
        curr = htable[i];
        curr = curr->getNext();
		
		//Increments the int length for every node in the linkedlist at the index.
        while(curr != NULL)
        {
            length++;
            curr = curr->getNext();
        }
		
		//Sets longest to the longest linked list in the hashtable.
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
        HashEntry<KeyType, ItemType>* curr;			//HashEntry pointer
        
		//This loop adds up all the nodes in the linked list for each index.
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

// remove - This function removes the wanted key from the hashtable.
template <class KeyType, class ItemType>
void HashMap<KeyType, ItemType>::remove(KeyType key, ItemType &deletedItem)
{
    int index = hashFunc(key);		//Get the index on where the key is stored

    HashEntry<KeyType, ItemType>* ptrToDelete;				//HashEntry pointer
    HashEntry<KeyType, ItemType>* p1;						//HashEntry pointer
    HashEntry<KeyType, ItemType>* p2;						//HashEntry pointer 

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
// writeToFile - Writes the data in the hashtable into the file according to their position
// in the hashtable.
template <class KeyType, class ItemType>
bool HashMap<KeyType, ItemType>::writeToFile()
{
   	ofstream outFile("output.txt");				//Open the file
    int i = 0;
    HashEntry<KeyType, ItemType>* curr;			//HashEntry pointer

    while (i < TABLE_SIZE)
    {
		//Write the first item in the index of the hashtable to the file if not empty.
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

		//Write the linkedlist nodes at the index of the hashtable into the file according to order of the list.
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
    outFile.close();				//Close the file.

    cout << "Save successful\n";
    return true;
}

#endif // HASHMAP_H_INCLUDED
