#ifndef FILE_IO
#define FILE_IO

#include <fstream>
#include <string>
#include "Movie.h"
#include "BinarySearchTree.h"
#include "HashMap.h"

using namespace std;

const string fileName = "..\MovieSourceFile.txt";

class FileIO
{
private:
	fstream File;
	bool available;
	int count;
	bool readInArray(Movie* movie[]);

public:
	FileIO();
	~FileIO();
	bool readInData(BinarySearchTree<string,HashMap<string,Movie*>> bst);
	bool writeOutData(BinarySearchTree<string,HashMap<string,Movie*>> bst);

	int getCount() {return count;}
	bool isAvailable() {return available;}
};

FileIO::FileIO()
{
	File.open(fileName);
	count = 0;
	if(File.is_open())
	{
		available = true;
		File.close();
	}
	else
	{
		available = false;
		cout << "File Not Found.\n";
	}
}

FileIO::~FileIO()
{
	if(File.is_open())
		File.close();
}

bool FileIO::readInData(BinarySearchTree<string,HashMap<string,Movie*>> bst)
{
	Movie* movie[128];
	readInArray(movie);
	for(int i = 0; i < count; i++)
	{
		HashMap<string,Movie*> hMap;
		if(bst.getEntry(movie[i]->getGenre(), hMap))
			hMap.insert(movie[i]->getTitle(),movie[i]);
	}
}

bool FileIO::writeOutData(BinarySearchTree<string,HashMap<string,Movie*>> bst)
{
	Movie* movie[128];
	int num;
	// while loop to get all entries in the tree into
	// movie array and to get # of entries
	if(available)
	{
		File.open(fileName);
		for(int i = 0; i < num; i++)
		{
			File << movie[i]->getYear()
				<< movie[i]->getGenre()
				<< movie[i]->getRating()
				<< movie[i]->getTitle()
				<< "\n";
		}
		File.close();
	}		
}

bool FileIO::readInArray(Movie* movie[])
{
	if(available)
	{
		int index = 0;
		Movie* movie[128];
		File.open(fileName);
		while(!File.eof())
		{
			Movie* temp = new Movie();
			int year;
			string genre;
			double rating;
			string title;

			File >> year >> genre >> rating;
			File.ignore(128, ' ');
			getline(File, title);

			temp->setYear(year);
			temp->setGenre(genre);
			temp->setRating(rating);
			temp->setTitle(title);
			movie[index] = temp;
			index++;
		}
		count += index + 1;
		File.close();
		return true;
	}
	return false;
}

#endif