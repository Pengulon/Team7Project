// Brandon Chai, 2014
// Main test driver for movie database program
// Team 1 Project

#include "FileIO.h"
#include "BinarySearchTree.h"
#include "HashMap.h"
#include "Movie.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cctype>
using namespace std;

// display - display function to pass to BST traverse functions
void display(Movie* &movie)
{
   cout << movie->getTitle() << endl;
}

// showMenu - displays menu for Database program
void showMenu()
{
    cout << "\nMenu\n";
    cout << "I - Insert item\n";
    cout << "R - Remove item\n";
    cout << "U - Undo remove item\n";
    cout << "S - Search by a unique key (movie title)\n";
    cout << "H - Display hash list\n";
    cout << "N - Print the hashed table(indented)\n";
    cout << "P - Print sorted list\n";
    cout << "B - Print indented tree\n";
    cout << "T - Show hash statistics\n";
    cout << "M - Show Menu\n";
    cout << "O - Save data to file\n";
    cout << "Q - Quit\n\n";
}

// searchKey - menu option to search by unique key
void searchKey(HashMap<string, Movie*>* h)
{
    Movie* foundItem;				//Movie ptr for the wanted item
    string key;
    cout << "\nEnter key\n";
    getline(cin, key);
    cout << "\nSearching for \"" << key << "\" " << endl;

	//Print key if found, if not print not found.
    if (h->search(key, foundItem))
    {
        cout << "Found\n";
        cout << "Title: " << foundItem->getTitle() << endl;
        cout << "Year: " << foundItem->getYear() << endl;
        cout << "Genre: " << foundItem->getGenre() << endl;
        cout << "Rating: " << foundItem->getRating() << endl;
    }
    else
        cout << "\"" << key << "\" was not found\n";
}

// insertItem - This function inserts the wanted key into the hash table
// binary tree.
void insertItem(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst)
{
    Movie* foundItem;			//Movie ptr to see if entry already exists
    string title;
    string genre;
    int year;
    double rating;

    cout << "Enter movie title:\n";
    getline(cin, title);

	//To see if the entry is already in the table & binary tree.
    if (h->search(title, foundItem))
    {
        cout << "\"" << title << "\" already exists\n";
        return;
    }

    cout << "Enter movie year:\n";
    while (1)
    {
		//Check to see if the input value is an int.
        cin >> year;
		if(year > 0)
			break;
        else
        {
            cout << "Invalid input. Please enter a integer value.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }

    cout << "Enter movie rating:\n";
    while (1)
    {
		//Check to see if the user input is a double
        cin >> rating;
		if(rating > 0 && rating < 10)
            break;
        else
        {
            cout << "Invalid input. Please enter a numerical value.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }

    cout << "Enter movie genre:\n";
    cin.ignore();
    getline(cin, genre);

    Movie* newItem = new Movie(title, year, genre, rating);				//Create a new node and store what the user wants to insert
    h->insert(title, newItem);								//Insert into Hashtable
    bst->add(title, newItem);								//Insert into binary tree

    cout << "\nSuccessfully inserted new item\n";
}

// removeItem - Function removes the item received by the user from the hashtable and binary
// tree.
void removeItem(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s)
{
    Movie* foundItem;		//Movie ptr to see if the wanted item is in the hashtable
    Movie* deletedItem;		//Movie ptr to delete the item
    string key;

    cout << "Enter key of item to be deleted:\n";
    getline(cin, key);

	//When the wanted item is not found.
    if (!h->search(key, foundItem))
    {
        cout << "\"" << key << "\" does not exist\n";
        return;
    }

    else
    {
        h->remove(key, deletedItem);					//Removes the user input key from the hash table
        bst->remove(key);								//Removes the user input key from the binary tree
        s->push(deletedItem);							//Push the user input key into a stack to store for undo.
        cout << "\nSuccessfully removed " << "\"" << key << "\"\n";
    }
}

// runDatabase - displays menu options for Movie Database application
void runDatabase(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s, FileIO* f)
{
    cout << "Movie Database Program\n";
    cout << "--------------------------";
    showMenu();								//Display the menu options

    bool isvalid = false;
	string input;

	//Gets an input from the user and tests to see 
	//if there is a valid option, and if not keep looping 
	//until quit or a valid option is picked.
	while(isvalid == false)
	{
	    cout << "Please enter you choice." << endl;
		getline(cin,input);

		//Loop to set every letter to an uppercase
		for(int x = 0; x<input.length();x++)
			input[x] = toupper(input[x]);

		if(input == "Q")
        {
            h->writeToFile();
            isvalid = true;
		}
		else if(input == "I")
			insertItem(h, bst);
		else if(input == "R")
			removeItem(h, bst, s);
		else if(input == "U")
		{
			Movie* deletedItem;						//Movie ptr to the deleteditem

			//Undos the delete requested by the user; if nothing to delete,
			//then print nothing to undo.
            if (s->pop(deletedItem))
            {
                h->insert(deletedItem->getTitle(), deletedItem);				//Adds the item back to the hashtable
                bst->add(deletedItem->getTitle(), deletedItem);					//Adds the item back to the binary tree
                cout << "Undo remove successful\n";
            }
            else
                cout << "Nothing to undo\n";
		}
		else if(input == "S")
			searchKey(h);
		else if(input == "H")
            h->displayList();
		else if(input == "N")
            h->printTable();
		else if(input == "P")
            bst->recursiveInorderTraverse(display);
        else if(input == "B")
            bst->printIndented();
		else if(input == "T")
            h->stats();
		else if(input == "M")
			showMenu();
        else if(input == "O")
        {
            Movie* deletedItem;
            h->writeToFile();
			while(s->pop(deletedItem))
                s->pop(deletedItem);
        }
		else
			cout << "Invalid Entry." << endl;
	}
	cout << "\nQuitting...\n";
}

int main()
{
   Stack<Movie*>* s = new Stack<Movie*>();							//Stack object
   BinarySearchTree<string, Movie*>* bst = new BinarySearchTree<string, Movie*>();				//Binart tree object
   HashMap<string, Movie*>* h = new HashMap<string, Movie*>();								//Hashtable object
   FileIO* f = new FileIO();										//File in and out object
		
   f->readInData(h, bst);										//Function to read in the data from file
   runDatabase(h, bst, s, f);									//Run the menu options

   delete s;				//Delete the stack object
   delete bst;				//Delete the binary tree object
   delete h;				//Delete the hashtable object
   delete f;				//Delete the file in and out object

   system("pause");
   return 0;
}
