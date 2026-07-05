#pragma once
#include <iomanip>
#include "BankAccount.h"
#define MAX_CUSTOMERS 10

class BankAccounts
{
private:
	enum PaymentSystem
	{
		VISA,
		MASTERCARD,
		DISCOVER,
		AMERICAN_EXPRESS
	};
	string cardNumList[MAX_CUSTOMERS];
	size_t maxCustomers = MAX_CUSTOMERS;
	size_t currentCustomers = 0;
	BankAccount customersList[MAX_CUSTOMERS];

public:
	BankAccounts();
	void show();
	void info(size_t id);
	void add();
	void edit(size_t id);
	void del(size_t id);
	void enterAmount(bool isTopUp);
	void sort();
	void accounts(string name);

private:
	string enterString(const char* text);
	string enterDate();
	unsigned short calcCheckDigit(const string& card_number);
	string generateCardNum(PaymentSystem paySys);
	template <typename T>
	bool isin(T value, vector<T> list);
};

