#pragma once
#include <string>
#include <utility>
#include <iostream>
using std::string;
using std::pair;
using std::cout;
using std::endl;


class BookStack
{
private:
	struct Book;
	typedef Book* ref;
	struct Book {
		string name;
		float value;
		ref pNext;

		Book(string name = string(), float value = float(), ref pNext = nullptr) {
			this->name = name;
			this->value = value;
			this->pNext = pNext;
		}
	};

	size_t length = 0;

	ref top = nullptr;
	string name = string();
	float value = float();

public:
	~BookStack();

	void show();
	void add(string name, float value);
	pair<string, float> pop();
	void clear();

	float calcAverageValue();

private:
	void deleteElem();
};

