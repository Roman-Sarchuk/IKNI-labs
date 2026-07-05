#pragma once
#include "BankAccounts.h"
#include <iostream>
using std::cout;

class CustomerMenu
{
private:
	BankAccounts bank;
	unsigned short selectedNum;

	void inputNum(const char* text, unsigned short numRange);
	void inputNum(const char* text);
	void printMenu();
	bool invokeAction();

public:
	void start();

};

