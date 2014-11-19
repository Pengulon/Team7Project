#ifndef BINARY_TREE
#define BINARY_TREE

#include <string>

using namespace std;

struct Data
{
	string title;
	int year;
	string genre;
	double rating;
}

class BinaryTree
{
	struct BinaryNode
	{
		Data data;
		BinaryNode* left;
		BinaryNode* right;
		string[] hashArray;
	};
	
private:
	BinaryNode *root;
	int count;

public:
	BinaryTree();
	~BinaryTree();
	hashFunction(string key, int size);
	addNode(string key, string subKey);
	removeNode(string key, string subKey);
	searchNode(string key);
	searchNode(string key, string subKey);
	printTree();
	listHash();
	listKey();
	displayStatistics();

};
#endif