#include "laba8_2.h"
using namespace std;

string enterString(size_t marginl, string inputtext)
{
	cout << left;
	string value;
	while (true)
	{
		cout << setw(marginl) << inputtext;
		getline(cin, value);
		if (value != "") {
			break;
		}

		cerr << "ERROR: Incorect input, try again !\n\tYou have to enter something\n" << endl;
	}
	return value;
}

size_t enterPages(size_t marginl)
{
	int pages;
	bool iscorrectinput;

	while (true)
	{
		cout << setw(marginl) << "Num of pages:";
		cin >> pages;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n\tNum of pages must be entered as a number\n" << endl;
		else if (pages <= 0)
			cerr << "ERROR: Incorect input, try again !\n\tNumber must be > 0\n" << endl;
		else
			break;
	}
	return (size_t)pages;
}

float enterPrice(size_t marginl)
{
	float price;
	bool iscorrectinput;

	while (true)
	{
		cout << setw(marginl) << "Price:";
		cin >> price;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (!iscorrectinput && price > 0.0f) {
			break;
		}

		cerr << "ERROR: Incorect input, try again !\n\tPrice must be > 0.0\n" << endl;
	}
	return price;
}

string enterDate(size_t marginl)
{
	int day, month, year;
	string date = "";
	bool iscorrectinput;

	while (true)
	{
		cout << setw(marginl) << "year:";
		cin >> year;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput) 
			cerr << "ERROR: Incorect input, try again !\n\tYear must be entered as a number\n" << endl;
		else if (year <= 0) 
			cerr << "ERROR: Year must be > 0\n" << endl;
		else
			break;
	}
	while (true)
	{
		cout << setw(marginl) << "month:";
		cin >> month;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n\tMonth must be entered as a number\n" << endl;
		else if (month <= 0 || month > 12)
			cerr << "ERROR: Month must be > 0 and <= 12\n" << endl;
		else
			break;
	}
	while (true)
	{
		cout << setw(marginl) << "day:";
		cin >> day;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n\tDay must be entered as a number\n" << endl;
		else if (day <= 0)
			cerr << "ERROR: Day must be > 0\n" << endl;
		else if (isin(month, { 1,3,5,7,8,10,12 }) && day > 31)	// 31
			cerr << "ERROR: Day must be <= 31\n" << endl;
		else if (isin(month, { 4,6,9,11 }) && day > 30) 
			cerr << "ERROR: Day must be <= 30\n" << endl;
		else if (month == 2 && year % 4 == 0 && day > 29) 
			cerr << "ERROR: Day must be <= 29\n" << endl;
		else if (month == 2 && year % 4 != 0 && day > 28) 
			cerr << "ERROR: Day must be <= 28\n" << endl;
		else
			break;
	}
	
	if (day < 10)
		date += '0';
	date += to_string(day) + '.';
	if (month < 10)
		date += '0';
	date += to_string(month) + '.';
	date += to_string(year);
	return date;
}

vector<size_t> spellDate(string date)
{
	vector<size_t> spldate{};
	string value{};

	for (size_t i = 0, s = date.size(); i < s; i++)
	{
		if (date[i] == '.') {
			spldate.push_back(stoi(value));
			value = "";
		}
		else {
			value += date[i];
		}
	}
	spldate.push_back(stoi(value));

	return spldate;
}

bool compareDate(Order lor, Order ror)
{
	vector<size_t> spldatel = spellDate(lor.date);
	vector<size_t> spldater = spellDate(ror.date);
	if (spldatel[2] != spldater[2])
		return spldatel[2] < spldater[2];
	else if (spldatel[1] != spldater[1])
		return spldatel[1] < spldater[1];
	else
		return spldatel[0] < spldater[0];
}