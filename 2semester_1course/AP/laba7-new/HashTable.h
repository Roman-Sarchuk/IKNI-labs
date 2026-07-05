#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>		// TEST
#include <cctype>
#include <locale>
#include <codecvt>
#include <sstream>
using namespace std;
#define STANDART_TABLE_SIZE 5

class AnagramCounter
{
	// Init a  structure of hash element
	struct Elem
	{
		string value{};
		unsigned int count = 0;
		Elem* next = nullptr;

		Elem(string value) : value(value) {}
		Elem() {}
	};

	// Init table (When constructor is run, it perform in the setText() func)
	unsigned int size, elem_count;
	Elem** table;

	unsigned int count{};
	vector<string> words{};

	// Init private function
	unsigned long getHash(string key);
	void add(string value);
	void add(vector<string> valueList);
	void toLowercase(string& word);
	vector<string> splitText(string text);
	void counting();
	void initTable();
	void clear();
public:
	// Init public function
	AnagramCounter(string text);
	~AnagramCounter();
	void setText(string text);
	inline unsigned int getCount() { return count; }
	void outputTable();
};

