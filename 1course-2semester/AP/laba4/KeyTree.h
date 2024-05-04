#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class KeyTree
{
	/*
		This class as a dictionary has the keys and the corresponding values
		FOR EXAMPLE: {key: 12, data: "IDK"}, {key: 75, data: "ASAP"}, ...
	*/
	struct node;
	typedef node* ref;
	struct node
	{
		int key{};
		string data{};
		ref left = nullptr, right = nullptr;
		node(int key, string data) : key(key), data(data) {}
	};

	ref root = nullptr;

	void showAsList(ref elem);
	void del(ref& root);
	ref find(int key);
public:
	void show();
	void add(int key, string value);
	void add(const vector<int>& keys, const vector<string>& values);
	void del(int key);
	void clear();
	string getData(int key);
	~KeyTree();
};

