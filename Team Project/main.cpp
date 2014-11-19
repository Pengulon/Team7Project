#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "dataStructure.h"

//Function Prototypes
void insertToTree(BinaryTree);
void addData(BinaryTree);
void deleteData(BinaryTree);
void displayOne(BinaryTree);
void listHashdata(BinaryTree);
void listSortedKeys(BinaryTree);
void printIndentedTree(BinaryTree);
void writeToFile(BinaryTree);
void collisions(BinaryTree);

int main ()
{
	BinaryTree tree;
	int key = 0;
	bool isValid = false;
	insertToTree(tree);
	while(isValid == false)
	{
		cout << "Please enter your choice." << endl;
		cin >> key;
		cin.ignore();
		switch(key)
		{
			case '1':
			{
				addData(tree);
				break;
			}
			case '2': 
			{
				deleteData(tree);
				break;
			}
			case '3': 
			{
				displayOne(tree);
				break;
			}
			case '4': 
			{
				listHashdata(tree);
				break;
			}
			case '5': 
			{
				listSortedKeys(tree);
				break;
			}
			case '6': 
			{
				printIndentedTree(tree);
				break;
			}
			case '7': 
			{
				writeToFile(tree);
				break;
			}
			case '8': 
			{
				collisions(tree);
				break;
			}
			case '9': 
			{
				isValid = true;
				break;
			}
			default:
			{
				cout << "Invalid entry. Please try again." << endl;
			}
		}
	}
}
void insertToTree(BinaryTree tree)
{
	string buffer;
	ifstream inFile;
	inFile.open("MovieSourceFile.txt");
	//Add more here
	while(getline(inFile, buffer))
	{
		cout << buffer << endl;
	}
}