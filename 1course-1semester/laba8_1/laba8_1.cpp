#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student
{
	string fname;
	float gpa = 0.0;
};
string getPath();
void getData(vector<Student>& database, string filename);
float calcGroupGPA(vector<Student> database);
void outputAll(vector<Student> database);
void outputStronger(vector<Student> database, float groupGPA);


int main()
{
	vector<Student> database;

	getData(database, getPath());

	outputAll(database);
	outputStronger(database, calcGroupGPA(database));

	system("PAUSE");
	return;
}


string getPath()
{
	/* Inputting the path to the file and checking that the path is correct */
	string path;
	do
	{
		cout << "Enter path of file> ";
		cin >> path;
		ifstream file(path);
		if (file) {
			cout << "! File is fined !\n" << endl;
			file.close();
			break;
		}
		cerr << "ERROR: file '" << path << "' wasn't opened !\n\tCheck it and try again.\n" << endl;
	} while (true);
	return path;
}

string getValue(string field)
{
	string value = "";

	bool startRead = false;
	char ch;
	for (size_t i = 0; i < field.size(); i++)
	{
		ch = field[i];
		if (startRead && field[i] != ' ')
			value += field[i];
		else if (field[i] == ':')
			startRead = true;
	}
	return value;
}

void getData(vector<Student>& database, string filename)
{
	ifstream file(filename);
	string field;
	Student record;

	bool newRecord = true;
	float sum = 0.0f, sumnum = 0.0f;
	while (file)
	{
		getline(file, field);
		if (field == "") {
			newRecord = true;
			record.gpa = sum / sumnum;
			sum = 0;
			sumnum = 0;
			database.push_back(record);
			continue;
		}

		if (!newRecord) {
			sum += stof(getValue(field));
			sumnum++;
		}
		else {
			record.fname = getValue(field);
			newRecord = false;
		}
	}

	file.close();
}

float calcGroupGPA(vector<Student> database)
{
	float sum = 0.0f;
	size_t i = 0;
	do
	{
		sum += database[i].gpa;
		i++;
	} while (i < database.size());
	return sum / (float)i;
}

void outputAll(vector<Student> database)
{
	size_t fsize[2]{ 13,15 }, counter = 1;
	cout << right << setfill('-') << fixed;

	cout << "/-" << setw(fsize[0] + 3) << "---" << setw(fsize[1] + 2) << "-\\" << endl;
	cout << "|-" << setw(fsize[0] + 3) << "-|-" << setw(fsize[1] + 2) << "-|" << endl;

	cout << left << setfill(' ');
	cout << "| " << setw(fsize[0]) << "First Name" << " | " << setw(fsize[1]) << "GPA" << " |" << endl;
	cout << right << setfill('-');
	cout << "|-" << setw(fsize[0] + 3) << "-|-" << setw(fsize[1] + 2) << "-|" << endl;

	for (size_t i = 0; i < database.size(); i++)
	{
		cout << left << setfill(' ');
		cout << "| " << setw(fsize[0]) << database[i].fname << " | " << setw(fsize[1]) << database[i].gpa << " |" << endl;
		cout << right << setfill('-');
		cout << "|-" << setw(fsize[0] + 3) << "-|-" << setw(fsize[1] + 2) << "-|" << endl;
	}

	cout << "\\-" << setw(fsize[0] + 3) << "---" << setw(fsize[1] + 2) << "-/" << endl << endl;
	cout << setfill(' ');
}

void outputStronger(vector<Student> database, float groupGPA)
{
	vector<Student> stronger;

	for (size_t i = 0; i < database.size(); i++)
	{
		if (database[i].gpa > groupGPA)
			stronger.push_back(database[i]);
	}

	cout << "***** Stronger *****" << endl;
	cout << " groupGPA :: " << groupGPA << endl;
	outputAll(stronger);
}
