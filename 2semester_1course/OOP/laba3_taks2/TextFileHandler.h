#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

class FileTextHandler
{
	string text{};
	size_t numOfPairWordLength{};
	pair<vector<char>, vector<size_t>> letter{};

	bool verifNumber(string value);
public:
	FileTextHandler() {}
	FileTextHandler(const char* fileName) { setText(fileName); }
	void setText(string fileName);

	void copyTextToFile(string fileName);
	void calcPairWordLength();
	void calcLetter();
	bool verifyBrackets();
	void delOddNum();

	void saveDataToFile(string fileName);
	void showData();
	inline string getText() { return text; }
	inline size_t getNumOfPairWordLength() { return numOfPairWordLength; }
	inline vector<char> getLetterList() { return letter.first; }
	inline vector<size_t> getCountOfLetetr() { return letter.second; }
};

