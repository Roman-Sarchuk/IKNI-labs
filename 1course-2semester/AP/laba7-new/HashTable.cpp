#include "HashTable.h"

unsigned long AnagramCounter::getHash(string key)
{
	unsigned long hash = 5381;

	for (char c : key) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

void AnagramCounter::add(string value)
{
	// Extend table (optional)
	if (elem_count == size)
	{
		unsigned int temp_elem_count = elem_count, temp_size = size;
		clear();
		// init the extended table
		size = temp_size * 2;
		table = new Elem*[size];
		for (size_t i = 0; i < size; i++)
			table[i] = nullptr;

		// copy elems
		for (size_t i = 0; i < temp_elem_count; i++)
			add(words[i]);
	}

	// Add elem || increase the counter (if already exist one)
	size_t hashID = getHash(value) % size;
	Elem* bucket = table[hashID];	// [getHash(value) % size] -> hashID
	// add a new elem
	if (bucket == nullptr)
	{
		Elem*& elem = table[hashID];
		elem = new Elem(value);
		elem_count++;
		return;
	}
	while (true)
	{
		if (bucket->value == value)	// increase the counter if the value is an anagram
		{
			bucket->count++;
			return;
		}
		else if (bucket->next == nullptr)
		{
			Elem*& elem = bucket;
			elem->next = new Elem(value);
			elem_count++;
			return;
		}
		bucket = bucket->next;
	}
}

void AnagramCounter::add(vector<string> valueList)
{
	for (string value : valueList)
		add(value);
}

void AnagramCounter::counting()
{
	count = 0;

	for (size_t i = 0; i < size; i++)
	{
		for (Elem* bucket = table[i]; bucket != nullptr; bucket = bucket->next)
		{
			count += bucket->count;
		}
	}
}

AnagramCounter::AnagramCounter(string text)
{
	setText(text);
}

void AnagramCounter::setText(string text)
{
	clear();

	initTable();

	words = splitText(text);

	for (auto it = words.begin(); it != words.end(); it++)
		sort((*it).begin(), (*it).end());

	add(words);
	
	counting();
}

void AnagramCounter::outputTable()
{
	for (size_t i = 0; i < size; i++)
	{
		if (table[i] == nullptr)
		{
			cout << "| \t" << "(..., ...)" << " \t|\n";
			continue;
		}
		for (Elem* bucket = table[i]; bucket != nullptr; bucket = bucket->next)
		{
			cout << "| \t(" << bucket->value << ", " << bucket->count << ") \t|";
		}
		cout << "\n";
	}
	cout << "\n\n";
}

void AnagramCounter::initTable()
{
	// init the hash table on STANDART_TABLE_SIZE buckets
	size = STANDART_TABLE_SIZE;
	elem_count = 0;
	table = new Elem*[size];
	for (size_t i = 0; i < size; i++)
		table[i] = nullptr;
}

void AnagramCounter::clear()
{
	// if table isn't initialized
	if (size == 0)
        return;

	// Delete buckets
	Elem *elem, *temp;
	for (size_t i = 0; i < size; i++)
	{
		elem = table[i];
		if (elem == nullptr)
			continue;

		while (true)
		{
			if (elem->next == nullptr)
			{
				delete elem;
				break;
			}
			else
			{
				temp = elem->next;
				delete elem;
				elem = nullptr;
				elem = temp;
			}
		}
	}

	// Delete table;
    size = 0;
	elem_count = 0;
    delete[] table;
    table = nullptr;
}

void AnagramCounter::toLowercase(string& word)
{
	for (char& letter : word)
	{
		if (letter >= 'À' && letter <= 'ß')
			letter -= 'ß' - 'ÿ';
		else if (letter >= 'A' && letter <= 'Z')
			letter -= 'Z' - 'z';
	}
}

vector<string> AnagramCounter::splitText(string text)
{
	vector<char> symbols = { '!', '"','#','$', '%', '&', ':','(',')', '*', '+', 
							 ',', '-', '\\', '/', '\'',';', '<', '=', '>', '?', '»',
							 '@', '[','.',']', '^', '_','`','{', '|', '}','~', '«'};

	vector<string> words; 
	string word;
	stringstream ss(text);

	int i;
	while (ss >> word)
	{
		// Remove characters from the string based on the symbols vector
		word.erase(std::remove_if(word.begin(), word.end(), [&symbols](char ch) {
			return std::find(symbols.begin(), symbols.end(), ch) != symbols.end();
			}), word.end());

		// add word
		if (word.size() > 1)
		{
			toLowercase(word);
			words.push_back(word);
		}
	}
	
	return words;
}

AnagramCounter::~AnagramCounter()
{
	clear();
}
