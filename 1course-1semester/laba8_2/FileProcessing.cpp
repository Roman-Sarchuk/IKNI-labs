#include "laba8_2.h"
using namespace std;


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

void updateFile(vector<Order> database, string filename)
{
	/* Clear the file and input the data from 'database' */
	ofstream file(filename);

	for (size_t i = 0, s = database.size(); i < s; i++)
	{
		file << '\n';
		file << fieldName[0] << ":" << database[i].customer << "\n";
		file << fieldName[1] << ":" << database[i].language << "\n";
		file << fieldName[2] << ":" << database[i].pages << "\n";
		file << fieldName[3] << ":" << database[i].transleter << "\n";
		file << fieldName[4] << ":" << database[i].date << "\n";
		file << fieldName[5] << ":" << database[i].price << "\n";
	}

	file.close();
}

void appandRtoF(Order record, string filename)
{
	/* Append the data of 'record' into the end of the file */
	ofstream file(filename, ios::app);

	file << "\n";
	file << fieldName[0] << ":" << record.customer << "\n";
	file << fieldName[1] << ":" << record.language << "\n";
	file << fieldName[2] << ":" << record.pages << "\n";
	file << fieldName[3] << ":" << record.transleter << "\n";
	file << fieldName[4] << ":" << record.date << "\n";
	file << fieldName[5] << ":" << record.price << "\n";

	file.close();
}

void getData(vector<Order>& database, string filename)
{
	/* Read the file and add a record to the vector 'database' */
	ifstream file(filename);
	string field;
	Order record;

	bool isGathering = true;
	while (file)
	{
		getline(file, field);
		if (field == "" && isGathering)
			continue;
		if (field == "") {
			database.push_back(record);
			isGathering = true;
			continue;
		}

		record.customer = getFieldvalue(field);
		getline(file, field);
		record.language = getFieldvalue(field);
		getline(file, field);
		record.pages = stoi(getFieldvalue(field));
		getline(file, field);
		record.transleter = getFieldvalue(field);
		getline(file, field);
		record.date = getFieldvalue(field);
		getline(file, field);
		record.price = stof(getFieldvalue(field));
		isGathering = false;
	}

	file.close();
}