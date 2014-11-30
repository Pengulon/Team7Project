// Ethan Wong, 2014
// Team 1 Project
// Handles File I/O, dynamically allocates array of Movie ptr objects from data in input file

#ifndef FILE_IO
#define FILE_IO
#include <fstream>
#include <string>
#include "Movie.h"
#include "BinarySearchTree.h"
#include "HashMap.h"
#define ARRAY_SIZE 128
using namespace std;

const string fileName = "MovieSourceFile.txt";				//Text file name

class FileIO
{
private:
    Movie* moviePtrArray[ARRAY_SIZE];
	fstream File;
	bool available;
	int count;

	// private functions
	bool readInArray(Movie* (&moviePtrArray) [ARRAY_SIZE]);

public:
	// Constructor
	FileIO();

	// Destructor
	~FileIO();

    // public functions
	void readInData(HashMap<string, Movie*>*& h, BinarySearchTree<string, Movie*>*& bst);
	int getCount() {return count;}
	bool isAvailable() {return available;}
};
//Constructor
FileIO::FileIO()
{
	File.open("MovieSourceFile.txt");
	count = 0;
	if(!File)
	{
		available = false;
		cout << "File Not Found.\n";
	}
	else
	{
		available = true;
		File.close();
	}
}

//Destructor
FileIO::~FileIO()
{
    for (int i = 0; i < count; i++)
        delete moviePtrArray[i];
	if(File.is_open())
		File.close();
}

//readInData - Read in the data and insert the data into the hashtable and binary tree.
void FileIO::readInData(HashMap<string, Movie*>*& h, BinarySearchTree<string, Movie*>*& bst)
{
	readInArray(moviePtrArray);
	for(int i = 0; i < count; i++)
	{
		h->insert(moviePtrArray[i]->getTitle(), moviePtrArray[i]);
		bst->add(moviePtrArray[i]->getTitle(), moviePtrArray[i]);
	}
}

//readInArray - Reads in the data from the file and stores it into a pointer of arrays.
bool FileIO::readInArray(Movie* (&moviePtrArray) [ARRAY_SIZE])
{
    if(available)
	{
		int index = 0;
		File.open(fileName.c_str());
		while(!File.eof())
		{
			Movie* temp = new Movie();			//Movie object
			int year;
			string genre;
			double rating;
			string title;

			File >> year >> genre >> rating;		//Get the year,genre, and rating from the file
			File.ignore(128, ' ');
			getline(File, title);					//Get the title from the file
			moviePtrArray[index] = new Movie(title, year, genre, rating);		//Set the data into the index of the pointer of arrays
			index++;
		}

		//for(int x = 0; x < index; x++)
		//	cout << moviePtrArray[x]->getTitle() << endl;

		count = index;		//Set count equal to the number of lines in the file
		File.close();		//Close the file

		return true;
	}
	return false;
}

#endif
