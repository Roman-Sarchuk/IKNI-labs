#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class AVLTree
{
	// Node of the tree
	struct node // структура для подачі вузлів дерева
	{
		int key{};
		unsigned char height = 1;
		node* left = nullptr;
		node* right = nullptr;
		node(int k) { key = k; }
	};

	node* root = nullptr;

	unsigned char height(node* p);
	int bfactor(node* p);
	void fixheight(node* p);

	node* rotateright(node* p);
	node* rotateleft(node* q);
	node* balance(node* p);

	node* insert(node* p, int k);
	node* remove(node* p, int k);
	void showAsTree(node* root, int indent = 0);
	void showAsList(node* elem);
	void del(node*& root);
public:
    void insert(int data);
	void remove(int data);
	int getMax();
	void showAsList();
	void showAsTree();
	void clear();
	~AVLTree();
};
