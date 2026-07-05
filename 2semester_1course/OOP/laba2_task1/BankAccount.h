#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
using namespace std;


class BankAccount
{
private:
	string date;
	float money = 0.f;
	string name;
	queue<string> history;

public:
	BankAccount(string name = "None", size_t day = 1, size_t month = 1, size_t year = 1);

	void setDate(size_t day, size_t month, size_t year);
	void setName(string name);
	void topUp(float amount);
	void withdraw(float amount);

	inline string getDate() { return date; }
	inline float getMoney() { return money; }
	inline string getName() { return name; }
	inline queue<string> getHistory() { return history; }

private:
	void addRecToHistory(string text);
	bool isin(size_t value, vector<size_t> list);
};

