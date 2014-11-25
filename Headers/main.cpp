// Brandon Chai, 2014
// main test driver for movie database program

#include "FileIO.h"
#include "BinarySearchTree.h"
#include "HashMap.h"
#include "Movie.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <algorithm>
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
    cout << "\nMenu" << endl;
    cout << "I - Insert item\n";
    cout << "R - Remove item\n";
    cout << "U - Undo remove item\n";
    cout << "S - Search by a unique key (movie title)\n";
    cout << "D - Display hash list\n";
    cout << "P - Print the hashed table(indented)\n";
    cout << "N - Print sorted list(inorder bst traverse)\n";
    cout << "T - Show hash statistics\n";
    cout << "M - Show Menu\n";
    cout << "O - Write data to file\n";
    cout << "Q - Quit\n\n";
}

// searchKey - menu option to search by unique key
void searchKey(HashMap<string, Movie*>* h)
{
    Movie* foundItem;
    string key;
    cout << "\nEnter key\n";
    getline(cin, key);
    cout << "\nSearching for \"" << key << "\" " << endl;

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

// insertItem -
void insertItem(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst)
{
    Movie* foundItem;
    string title;
    string genre;
    int year;
    double rating;

    cout << "Enter movie title:\n";
    getline(cin, title);

    if (h->search(title, foundItem))
    {
        cout << "\"" << title << "\" already exists\n";
        return;
    }

    cout << "Enter movie year:\n";
    while (1)
    {
        if (cin >> year)
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
        if (cin >> rating)
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

    Movie* newItem = new Movie(title, year, genre, rating);
    h->insert(title, newItem);
    bst->add(title, newItem);

    cout << "\nSuccessfully inserted new item\n";
}

// removeItem -
void removeItem(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s)
{
    Movie* foundItem;
    Movie* deletedItem;
    string key;

    cout << "Enter key of item to be deleted:\n";
    cin.ignore();
    getline(cin, key);

    if (!h->search(key, foundItem))
    {
        cout << "\"" << key << "\" does not exist\n";
        return;
    }

    h->remove(key, deletedItem);
    bst->remove(key);
    s->push(deletedItem);
}

// runDatabase - displays menu options for Movie Database application
void runDatabase(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s, FileIO* f)
{
    cout << "Movie Database Program\n";
    cout << "--------------------------";
    showMenu();

    bool isvalid = false;
	string input;

	while(isvalid == false)
	{
	    cout << endl;
		getline(cin,input);

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
			Movie* deletedItem;

            s->pop(deletedItem);
            h->insert(deletedItem->getTitle(), deletedItem);
            bst->add(deletedItem->getTitle(), deletedItem);
            cout << "Undo remove successful\n";
		}
		else if(input == "S")
			searchKey(h);
		else if(input == "D")
            h->displayList();
		else if(input == "P")
            h->printTable();
		else if(input == "N")
			bst->recursiveInorderTraverse(display);
		else if(input == "T")
            h->stats();
		else if(input == "M")
			showMenu();
        else if(input == "O")
			h->writeToFile();
		else
			cout << "Invalid Entry." << endl;
	}
	cout << "\nQuitting...\n";
}

int main()
{
   Stack<Movie*>* s = new Stack<Movie*>();
   BinarySearchTree<string, Movie*>* bst = new BinarySearchTree<string, Movie*>();
   HashMap<string, Movie*>* h = new HashMap<string, Movie*>();
   FileIO* f = new FileIO();

   f->readInData(h, bst);
   runDatabase(h, bst, s, f);

   delete s;
   delete bst;
   delete h;
   delete f;

   return 0;
}
