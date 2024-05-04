#include "BankAccount.h"

void BankAccount::setDate(string date)
{
	unsigned short day, month, year;
	stringstream ss(date);
	char delimiter;
	ss >> day >> delimiter >> month >> delimiter >> year;

	if (year <= 0)
		cerr << "ERROR: Year must be > 0\n\n";
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
		this->date = "";
		if (day < 10)
			this->date += '0';
		this->date += to_string(day) + '.';
		if (month < 10)
			this->date += '0';
		this->date += to_string(month) + '.';
		this->date += to_string(year);
		addRecToHistory("Set 'date' to '" + this->date + "'");
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

void BankAccount::setCardNumber(string cardNumber)
{
	if (cardNumber.size() < 15 || cardNumber.size() > 16)
	{
		cerr << "ERROR: Card number must have 16 or 15 digits\n\n";
		return;
	}
	for (size_t i = 0, len = cardNumber.length(); i < len; i++)
	{
		if (!isin(cardNumber[i], { '0','1','2','3','4','5','6','7','8','9' }))
		{
			cerr << "ERROR: Check the card digits\n\n";
			return;
		}
	}
	this->cardNumber = cardNumber;
	addRecToHistory("Set 'card number' to " + cardNumber);
}

void BankAccount::transferMoney(float amount)
{
	if (amount < 0)	// withdraw
	{
		if (money > -amount)
		{
			money += amount;
			addRecToHistory("Withdraw (-) " + to_string(-amount));
		}
		else
		{
			cerr << "ERROR: There are insufficient funds in the account\n\n";
		}
	}
	else			// top up
	{
		money += amount;
		addRecToHistory("Top up by (+) " + to_string(amount));
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

template <typename T>
bool BankAccount::isin(T value, vector<T> list)
{
	for (size_t i = 0, s = list.size(); i < s; i++)
	{
		if (value == list[i])
			return true;
	}
	return false;
}
