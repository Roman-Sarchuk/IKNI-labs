#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TwoFourTree
{
	struct node;
	typedef node* ref;
	struct node
	{
		vector<int> keys{};
		vector<ref> children{};

		node() {}
		node(int key1) { 
			keys.push_back(key1); 
		}
		node(int key1, int key2) { 
			keys.push_back(key1); keys.push_back(key2); 
		}
		node(int key1, int key2, int key3) { 
			keys.push_back(key1); keys.push_back(key2); keys.push_back(key3);
		}
	};

	ref root{};

	void clear(ref& root);
	void remove(ref& node, int key);
	ref findMinKeyNode(ref node);
	void showAsList(ref root, int level = 0);
	bool isKey(ref node, int key);
	ref findParent(int key);
	void spell(ref node);
public:
	void insert(int key);
	void remove(int key);
	ref search(int key);
	void clear();
	void showAsList();
	TwoFourTree()
	{
		// ***** TESTING *****
		/*root = new node(6);

		ref kid1 = new node(3);
		ref kid2 = new node(8, 12, 40);

		ref kid11 = new node(1);
		ref kid12 = new node(5);

		ref kid21 = new node(7);
		ref kid22 = new node(9, 10);
		ref kid23 = new node(15, 24, 32);
		ref kid24 = new node(74, 89, 140);

		root->children.push_back(kid1);
		root->children.push_back(kid2);

		root->children[0]->children.push_back(kid11);
		root->children[0]->children.push_back(kid12);

		root->children[1]->children.push_back(kid21);
		root->children[1]->children.push_back(kid22);
		root->children[1]->children.push_back(kid23);
		root->children[1]->children.push_back(kid24);*/
		// ***** ******* *****
	}
};

