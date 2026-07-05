#include "laba8_2.h"
using namespace std;


bool isin(size_t value, vector<size_t> list)
{
	for (size_t i = 0, s = list.size(); i < s; i++)
	{
		if (value == list[i])
			return true;
	}
	return false;
}

vector<size_t> getRange(size_t end)
{
	vector<size_t> range;
	for (size_t i = 0; i < end; i++)
	{
		range.push_back(i);
	}
	return range;
}

size_t getActionNum(size_t range)
{
	short int action;
	while (true)
	{
		cout << "Select a number> ";
		cin >> action;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "ERROR: Incorect number of action. Try again !\n\t";
			cerr << "numbe must be from 1" << " to " << range << endl << endl;
			continue;
		}
		for (size_t i = 1; i < range + 1; i++)
		{
			if (action == i)
				return action;
		}
		cerr << "ERROR: Incorect number of action. Try again !\n\t";
		cerr << "numbe must be from 1" << " to " << range << endl << endl;
	}
}

size_t getFieldId(bool showAll) 
{
	size_t i = 0, action = 0;

	for (size_t s = fieldName.size(); i < s; i++)
	{
		cout << i + 1 << ") " << fieldName[i] << endl;
	}

	if (showAll) {
		cout << ++i << ") all records\n" << endl;
		action = getActionNum(fieldName.size() + 1);
		if (action == i)
			return -1;
	}

	if (action == 0) {
		cout << endl;
		action = getActionNum(fieldName.size());
	}

	return action - 1;
}

string getFieldname(string field)
{
	string value = "";

	char ch;
	for (size_t i = 0, s = field.size(); i < s; i++)
	{
		ch = field[i];
		if (field[i] == ':')
			return value;
		value += field[i];
	}
}

string getFieldvalue(string field)
{
	string value = "";

	bool startRead = false;
	char ch;
	for (size_t i = 0; i < field.size(); i++)
	{
		ch = field[i];
		if (startRead)
			value += field[i];
		else if (field[i] == ':')
			startRead = true;
	}
	return value;
}