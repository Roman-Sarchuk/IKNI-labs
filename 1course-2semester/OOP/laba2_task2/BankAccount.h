#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
using namespace std;


class BankAccount
{
private:
	string date;
	float money = 0.f;
	string name;
	queue<string> history;
	string cardNumber;

public:
	void setDate(string date);
	void setName(string name);
	void setCardNumber(string cardNumber);
	void transferMoney(float amount);

	inline string getDate() { return date; }
	inline float getMoney() { return money; }
	inline string getName() { return name; }
	inline string getCardNumber() { return cardNumber; };
	inline queue<string> getHistory() { return history; }

private:
	void addRecToHistory(string text);
	template <typename T>
	bool isin(T value, vector<T> list);
};

