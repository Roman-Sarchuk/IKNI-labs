#include "BankAccount.h"

BankAccount::BankAccount(string name, size_t day, size_t month, size_t year)
{
	setName(name);
	setDate(day, month, year);
}

void BankAccount::setDate(size_t day, size_t month, size_t year)
{
	// max -> 31.12.9999 , min -> 01.01.01
	if (year <= 0)
		cerr << "ERROR: Year must be > 0\n\n";
	else if (year > 9999)
		cerr << "ERROR: Year must have 4 numbers\n\n";
	else if (month <= 0 || month > 12)
		cerr << "ERROR: Month must be > 0 and <= 12\n\n";
	else if (day <= 0)
		cerr << "ERROR: Day must be > 0\n\n";
	else if (isin(month, { 1,3,5,7,8,10,12 }) && day > 31)
		cerr << "ERROR: Day must be <= 31\n\n";
	else if (isin(month, { 4,6,9,11 }) && day > 30)
		cerr << "ERROR: Day must be <= 30\n\n";
	else if (month == 2 && year % 4 == 0 && day > 29)
		cerr << "ERROR: Day must be <= 29\n\n";
	else if (month == 2 && year % 4 != 0 && day > 28)
		cerr << "ERROR: Day must be <= 28\n\n";
	else
	{
		date = "";
		if (day < 10)
			date += '0';
		date += to_string(day) + '.';
		if (month < 10)
			date += '0';
		date += to_string(month) + '.';
		date += to_string(year);
		addRecToHistory("Set 'date' to '" + date + "'");
	}
}

void BankAccount::setName(string name)
{
	if (name.length() == 0)
	{
		cerr << "ERROR: You can't set void name\n\n";
	}
	else
	{
		this->name = name;
		addRecToHistory("Set 'name' to '" + name + "'");
	}
}

void BankAccount::topUp(float amount)
{
	money += amount;
	addRecToHistory("Transfer " + to_string(amount));
}

void BankAccount::withdraw(float amount)
{
	if (amount > money)
		cerr << "ERROR: You don't have enough funds\n\n";
	else
	{
		money -= amount;
		addRecToHistory("Withdraw " + to_string(amount));
	}
}

void BankAccount::addRecToHistory(string text)
{
	history.push(text);
	if (history.size() > 10)
	{
		history.pop();
	}
}

bool BankAccount::isin(size_t value, vector<size_t> list)
{
	for (size_t i = 0, s = list.size(); i < s; i++)
	{
		if (value == list[i])
			return true;
	}
	return false;
}
