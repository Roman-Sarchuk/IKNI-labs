#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

string getPath();
size_t calcNumOfSymbl(string filename, char symbl);
void outputRes(string filename, size_t rownum, size_t prgnum);

int main()
{
	// Add Ukrain language
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	size_t rownum, prgnum;
	string filename = getPath();	// more -> BLUE-BEARD.txt | less -> computers.txt
	rownum = calcNumOfSymbl(filename, '\n');
	prgnum = calcNumOfSymbl(filename, '\t');

	outputRes(filename, rownum, prgnum);

	system("PAUSE");
	return 0;
}

string getPath()
{
	/* Inputting the path to the file and checking that the path is correct */
	string path;
	do
	{
		cout << "Enter path of file> ";
		cin >> path;
		fstream file(path);
		if (file) {
			cout << "! File is fined !\n" << endl;
			file.close();
			break;
		}
		cerr << "ERROR: file '" << path << "' wasn't opened !\n\tCheck it and try again.\n" << endl;
	} while (true);
	return path;
}

size_t calcNumOfSymbl(string filename, char symbl)
{
	/* Calc number of symbol in txt file */
	ifstream file(filename);
	size_t counter = 0;
	char ch;

	while (file)
	{
		ch = file.get();
		if (ch == symbl)
			counter++;
	}

	// if last char is not '\n' add 1 to counter
	// else program not calc one more row
	if (symbl == '\n' && ch != '\n')
		counter++;

	return counter;
}

void outputRes(string filename, size_t rownum, size_t prgnum)
{
	/* Output tabel of results */
	cout << "::::::::::::RESULT::::::::::::" << endl;
	cout << "file name\t" << filename << endl;
	cout << "num of row\t" << rownum << endl;
	cout << "num of prg\t" << prgnum << endl;
	cout << "::::::::::::::::::::::::::::::" << endl;
}
