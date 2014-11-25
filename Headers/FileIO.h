#ifndef FILE_IO
#define FILE_IO
#include <fstream>
#include <string>
#include "Movie.h"
#include "BinarySearchTree.h"
#include "HashMap.h"
#define ARRAY_SIZE 128
using namespace std;

const string fileName = "MovieSourceFile.txt";

class FileIO
{
private:
    Movie* moviePtrArray[ARRAY_SIZE];
	fstream File;
	bool available;
	int count;
	bool readInArray(Movie* (&moviePtrArray) [ARRAY_SIZE]);

public:
	FileIO();
	~FileIO();
	void readInData(HashMap<string, Movie*>*& h, BinarySearchTree<string, Movie*>*& bst);

	int getCount() {return count;}
	bool isAvailable() {return available;}
};

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

FileIO::~FileIO()
{
    for (int i = 0; i < count; i++)
        delete moviePtrArray[i];
	if(File.is_open())
		File.close();
}

void FileIO::readInData(HashMap<string, Movie*>*& h, BinarySearchTree<string, Movie*>*& bst)
{
	readInArray(moviePtrArray);
	for(int i = 0; i < count; i++)
	{
		h->insert(moviePtrArray[i]->getTitle(), moviePtrArray[i]);
		bst->add(moviePtrArray[i]->getTitle(), moviePtrArray[i]);
	}
}

bool FileIO::readInArray(Movie* (&moviePtrArray) [ARRAY_SIZE])
{
    if(available)
	{
		int index = 0;
		File.open(fileName.c_str());
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
			moviePtrArray[index] = new Movie(title, year, genre, rating);
			index++;
		}

		//for(int x = 0; x < index; x++)
		//	cout << moviePtrArray[x]->getTitle() << endl;

		count = index;
		File.close();

		return true;
	}
	return false;
}

#endif
