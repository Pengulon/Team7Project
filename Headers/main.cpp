// Brandon Chai, 2014
// main test driver for movie database program

#include "BinarySearchTree.h"
#include "HashMap.h"
#include "Movie.h"
#include "Stack.h"
#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <stdlib.h>
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
    //cout << "O - Write data to file\n";
    cout << "Q - Quit\n\n";
}

// searchKey - menu option to search by unique key
void searchKey(HashMap<string, Movie*>* h)
{
    Movie* foundItem;
    string key;
    cout << "\nEnter key\n";
    cin.ignore();
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
    cin.ignore();
    getline(cin, title);

    if (h->search(title, foundItem))
    {
        cout << "\"" << title << "\" already exists\n";
        return;
    }

    cout << "Enter movie year:\n";
    cin.ignore();
    cin >> year;

    cout << "Enter movie rating:\n";
    cin.ignore();
    cin >> rating;

    cout << "Enter movie genre:\n";
    cin.ignore();
    getline(cin, genre);
    //cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    Movie* newItem = new Movie(title, year, genre, rating);
    h->insert(title, newItem);
    bst->add(title, newItem);

    cout << "\nSuccessfully inserted new item\n";
}

// removeItem -
void removeItem(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s)
{
    Movie* foundItem;
    string key;
    cout << "Enter key of item to be deleted:\n";
    cin.ignore();
    getline(cin, key);

    if (!h->search(key, foundItem))
    {
        cout << "\"" << key << "\" does not exist\n";
        return;
    }

    Movie* deletedItem;
    h->remove(key, deletedItem);
    bst->remove(key);
    s->push(deletedItem);
}

// runDatabase - displays menu options for Movie Database application
void runDatabase(HashMap<string, Movie*>* h, BinarySearchTree<string, Movie*>* bst, Stack<Movie*>* s)
{
    cout << "Movie Database Program\n";
    cout << "--------------------------";
    showMenu();

    char input;
    cin >> input;

    while (input != 'Q' && input != 'q')
    {
        switch(input)
        {
        case 'I':
        case 'i':
            {
                insertItem(h, bst);
                break;
            }
        case 'R':
        case 'r':
            {
                removeItem(h, bst, s);
                break;
            }
        case 'U':
        case 'u':
            {
                Movie* deletedItem;
                s->pop(deletedItem);
                h->insert(deletedItem->getTitle(), deletedItem);
                bst->add(deletedItem->getTitle(), deletedItem);
                cout << "Undo remove successful\n";
                break;
            }
        case 'S':
        case 's':
            {
                searchKey(h);
                break;
            }
        case 'D':
        case 'd':
            h->displayList();
            break;
        case 'P':
        case 'p':
            h->printTable();
            break;
        case 'N':
        case 'n':
            bst->iterativeInorderTraverse(display);
            break;
        case 'T':
        case 't':
            h->stats();
            break;
        case 'M':
        case 'm':
            showMenu();
            break;
        case 'Q':
        case 'q':
            break;
        }

        cout << endl;
        cin >> input;
    }
}

int main()
{
   Stack<Movie*>* s = new Stack<Movie*>();
   BinarySearchTree<string, Movie*>* bst = new BinarySearchTree<string, Movie*>();
   HashMap<string, Movie*>* h = new HashMap<string, Movie*>();

   runDatabase(h, bst, s);

   delete s;
   delete bst;
   delete h;

   return 0;
}