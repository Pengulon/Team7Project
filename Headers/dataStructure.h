#ifndef BINARY_TREE
#define BINARY_TREE

#include <string>

using namespace std;

class BinaryTree
{
	struct BinaryNode
	{
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