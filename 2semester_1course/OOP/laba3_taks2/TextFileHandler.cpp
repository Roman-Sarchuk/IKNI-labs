#include "TextFileHandler.h"

bool FileTextHandler::verifNumber(string value)
{
	char num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (size_t i = 0; i < value.size(); i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (value[i] != num[j])
				return false;
		}
	}
	return true;
}

void FileTextHandler::setText(string fileName)
{
	ifstream file(fileName);

	if (!file.is_open())
		throw invalid_argument("ERROR: file \"" + fileName + "\" can't be opened");

	text = "";

	string str;
	while (!file.eof())
	{
		getline(file, str);
		text.append(str + '\n');
	}

	file.close();
}

void FileTextHandler::copyTextToFile(string fileName)
{
	ofstream file(fileName);

	if (!file.is_open())
		throw invalid_argument("ERROR: file \"" + fileName + "\" can't be opened");

	file << text;

	file.close();
}

void FileTextHandler::calcPairWordLength()
{
	if (text == "")
		throw invalid_argument("ERROR: hangler don't have text to process");

	stringstream ss(text);

	numOfPairWordLength = 0;
	string word;
	while (ss >> word)
	{
		if (word.size() % 2 == 0)
			numOfPairWordLength++;
	}
}

void FileTextHandler::calcLetter()
{
	if (text == "")
		throw invalid_argument("ERROR: hangler don't have text to process");

	letter.first.clear();
	letter.second.clear();

	for (char ch : text)
	{
		if (isalpha(ch))
		{
			ch = (char)tolower(ch);
			if (find(letter.first.begin(), letter.first.end(), ch) == letter.first.end())
			{
				letter.first.push_back(ch);
				letter.second.push_back(count(text.begin(), text.end(), ch));
			}
		}
	}
}

bool FileTextHandler::verifyBrackets()
{
	if (text == "")
		throw invalid_argument("ERROR: hangler don't have text to process");

	stringstream ss(text);
	
	bool isBracket = false;
	char ch;
	while (ss >> ch)
	{
		if (isBracket)
		{
			if (ch == ')')
				return true;
			if (ch == '(' || ch == '.')
				return false;
		}
		else if (ch == '(')
			isBracket = true;
		else if (ch == ')')
			return false;
	}
	if (!isBracket)
		return true;
	return false;
}

void FileTextHandler::delOddNum()
{
	if (text == "")
		throw invalid_argument("ERROR: hangler don't have text to process");

	stringstream ss(text);
	string word;
	int num;
	size_t n;
	while (ss >> word)
	{
		if (verifNumber(word))
		{
			num = stoi(word);
			if (num % 2 != 0)
			{
				n = text.find(word);
				text.erase(n, word.length());
			}
		}
	}
}

void FileTextHandler::saveDataToFile(string fileName)
{
	ofstream file(fileName, ios::app);

	if (!file.is_open())
		throw invalid_argument("ERROR: file \"" + fileName + "\" can't be opened");

	file.clear();
	
	file << text << '\n';
	file << "=== INFO ====\n";
	file << "Number of pair word lenghts: " << numOfPairWordLength << '\n';
	file << "Brackets is corrected: " << (verifyBrackets() ? "true" : "false") << '\n';
	calcLetter();
	file << "~ Letter ~\n";
	for (size_t i = 0, length = letter.first.size(); i < length; i++)
	{
		file << letter.first[i] << ": " << letter.second[i] << '\n';
	}
	cout << '\n';
}

void FileTextHandler::showData()
{
	cout << text << endl << endl;
	cout << "=== INFO ===\n";
	cout << "Number of pair word lenghts: " << numOfPairWordLength << '\n';
	cout << "Bracket is coorected: " << (verifyBrackets() ? "true" : "false") << '\n';
	calcLetter();
	cout << "~ Letter ~\n";
	for (size_t i = 0, length = letter.first.size(); i < length; i++)
	{
		cout << letter.first[i] << ": " << letter.second[i] << '\n';
	}
	cout << '\n';
}
