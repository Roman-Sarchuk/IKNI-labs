#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Tree
{
	struct node;
	typedef node* ref;
	struct node
	{
		int key{};
		ref left = nullptr, right = nullptr;
		node(int key) : key(key) {}
	};

	ref root = nullptr;

	void showAsTree(ref elem, int indent = 0);
	void showAsList(ref elem);
	void del(ref& root);
public:
	void showAsTree();
	void showAsList();
	void add(int key);
	void add(const vector<int>& keys);
	void clear();
	~Tree();
};

