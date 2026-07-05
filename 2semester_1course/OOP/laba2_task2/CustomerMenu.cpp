#include "CustomerMenu.h"

void CustomerMenu::inputNum(const char* text, unsigned short numRange)
{
	while (true)
	{
		cout << text;
		cin >> selectedNum;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "ERROR: Incorect number. Try again !\n\t";
			cerr << "number must be from 1" << " to " << numRange << endl << endl;
			continue;
		}
		if (selectedNum > 0 && selectedNum <= numRange)
			break;
		cerr << "ERROR: Numbe must be from 1" << " to " << numRange << endl << endl;
	}
}

void CustomerMenu::inputNum(const char* text)
{
	while (true)
	{
		cout << text;
		cin >> selectedNum;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "ERROR: Incorect number. Try again !\n\n";
			continue;
		}
		break;
	}
}

void CustomerMenu::printMenu()
{
	cout << """::=::=::=::=::=::=::=::=::=::\n\
What to do?\n\
1) show all accounts;\n\
2) info about an account;\n\
3) add a new account;\n\
4) edit an account;\n\
5) delete an account;\n\
6) top up an account\n\
7) withdraw the money\n\
8) sort the accounts list;\n\
9) show all owner accounts;\n\
10) exit the program.\n""";
	cout << "::=::=::=::=::=::=::=::=::=::\n" << endl;
}

bool CustomerMenu::invokeAction()
{
	string name;
	switch (selectedNum)
	{
	case 1:
		bank.show();
		break;
	case 2:
		inputNum("Enter the account ID> ");
		bank.info(selectedNum);
		break;
	case 3:
		bank.add();
		break;
	case 4:
		inputNum("Enter the account ID> ");
		bank.edit(selectedNum);
		break;
	case 5:
		inputNum("Enter the account ID> ");
		bank.del(selectedNum);
		break;
	case 6:
		bank.enterAmount(true);
		break;
	case 7:
		bank.enterAmount(false);
		break;
	case 8:
		bank.sort();
		break;
	case 9:
		while (true)
		{
			cout << "Enter owner's name> ";
			cin.ignore();
			getline(cin, name);
			if (name != "") {
				break;
			}
			cerr << "ERROR: You have to enter something\n" << endl;
		}
		bank.accounts(name);
		break;
	case 10:
		return false;
	}
	return true;
}

void CustomerMenu::start()
{
	do
	{
		printMenu();
		inputNum("Select a number> ", 10);
	} while (invokeAction());
}
