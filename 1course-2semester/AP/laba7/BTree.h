#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

class BTree
{
	struct Node;
	typedef Node* ref;
	struct Node
	{
		vector<int> keys{};
		vector<ref> children{};
	};

	ref root;
	unsigned short m;

	void showAsList(ref, int);
	void del(ref);
	// for inserting
	ref findParent(ref);
	void spell(ref);
	// for removing
	int findKeyIndex(ref, int);
	void removeFromNode(ref, int);
	void fixAfterDeletion(ref, ref);
	int findSiblingIndex(ref, ref);
	void borrowFromLeft(ref, ref, ref, int);
	void borrowFromRight(ref, ref, ref, int);
	void mergeWithLeft(ref, ref, ref, int);
	void mergeWithRight(ref, ref, ref, int);
	void mergeWithParent(ref, ref);
public:
	BTree(unsigned short m);

	void insert(int);
	void remove(int);
	void clear();
	void show();
};

