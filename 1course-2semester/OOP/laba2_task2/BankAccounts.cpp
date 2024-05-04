#include "BankAccounts.h"

BankAccounts::BankAccounts()
{
	// ************ TESTING ************
	BankAccount act1;
	act1.setName("Tom");
	act1.setDate("24.02.2024");
	act1.setCardNumber(generateCardNum(VISA));
	act1.transferMoney(8241.07);
	currentCustomers++;
	BankAccount act2;
	act2.setName("Ruby");
	act2.setDate("15.06.1978");
	act2.setCardNumber(generateCardNum(VISA));
	act2.transferMoney(983491.28);
	currentCustomers++;
	BankAccount act3;
	act3.setName("Tom");
	act3.setDate("07.11.2016");
	act3.setCardNumber(generateCardNum(AMERICAN_EXPRESS));
	act3.transferMoney(1980);
	currentCustomers++;
	customersList[0] = act1;
	customersList[1] = act2;
	customersList[2] = act3;

	BankAccount act4;
	act4.setName("ABC");
	act4.setDate("07.11.2016");
	act4.setCardNumber(generateCardNum(MASTERCARD));
	act4.transferMoney(1980);
	currentCustomers++;
	customersList[3] = act4;
	BankAccount act5;
	act5.setName("ACB");
	act5.setDate("07.11.2016");
	act5.setCardNumber(generateCardNum(MASTERCARD));
	act5.transferMoney(1980);
	currentCustomers++;
	customersList[4] = act5;
	BankAccount act6;
	act6.setName("Ruby");
	act6.setDate("07.11.2016");
	act6.setCardNumber(generateCardNum(DISCOVER));
	act6.transferMoney(1980);
	currentCustomers++;
	customersList[5] = act6;
	/*BankAccount act7;
	act7.setName("London");
	act7.setDate("07.11.2016");
	act7.setCardNumber(generateCardNum(DISCOVER));
	act7.transferMoney(1980);
	currentCustomers++;
	customersList[6] = act7;
	BankAccount act8;
	act8.setName("Lviv");
	act8.setDate("07.11.2016");
	act8.setCardNumber(generateCardNum(AMERICAN_EXPRESS));
	act8.transferMoney(1980);
	currentCustomers++;
	customersList[7] = act8;
	BankAccount act9;
	act9.setName("JKL");
	act9.setDate("07.11.2016");
	act9.setCardNumber(generateCardNum(AMERICAN_EXPRESS));
	act9.transferMoney(1980);
	currentCustomers++;
	customersList[8] = act9;
	BankAccount act0;
	act0.setName("Olia UA");
	act0.setDate("07.11.2016");
	act0.setCardNumber(generateCardNum(DISCOVER));
	act0.transferMoney(1980);
	currentCustomers++;
	customersList[9] = act0;*/
	// ************ ******* ************
}

void BankAccounts::show()
{
	/* Show list of accounts (id, name, cardNum) */
	short margin[3]{ 5,25,17 }, lineSize = margin[0] + margin[1] + margin[2] + 5;
	cout << left;

	// Header
	cout << setfill('-') << fixed;
	cout << "/" << setw(lineSize) << "" << "\\" << endl;
	cout << setfill(' ') << fixed;
	cout << "| " << setw(margin[0]) << "ID" << "| " << setw(margin[1]) << "NAME" << "| " << setw(margin[2]) << "CARD NUMBER" << "|\n";

	// Data 
	for (short i = 0; i < currentCustomers; i++)
	{
		cout << setfill('-') << fixed;
		cout << "|-" << setw(margin[0]) << "" << "|-" << setw(margin[1]) << "" << "|-" << setw(margin[2]) << "" << "|\n";
		cout << setfill(' ') << fixed;
		cout << "| " << setw(margin[0]) << i << "| " << setw(margin[1]) << customersList[i].getName() << "| " << setw(margin[2]) << cardNumList[i] << "|\n";
	}
	cout << setfill('-') << fixed;
	cout << "\\" << setw(lineSize) << "" << "/" << endl;
	cout << setfill(' ') << fixed << endl << endl;
}

void BankAccounts::info(size_t id)
{
	/* Show info about the account */

	if (id < 0 || id >= currentCustomers)
	{
		cerr << "ERROR: The account with this id doesn't exist\n\n";
		return;
	}

	unsigned short margine = 14, lineSize = 35;
	queue<string> history = customersList[id].getHistory();
	cout << left;

	cout << setfill('=') << fixed;
	cout << setw(lineSize) << "" << endl;

	cout << setfill(' ') << fixed;
	cout << setw(margine) << "Name" << "|  " << customersList[id].getName() << endl;
	cout << setw(margine) << "Card Number" << "|  " << customersList[id].getCardNumber() << endl;
	cout << setw(margine) << "Money" << "|  " << customersList[id].getMoney() << endl;
	cout << setw(margine) << "Date" << "|  " << customersList[id].getDate() << endl;
	cout << "********** History **********\n";
	while (!history.empty())
	{
		cout << "- " << history.front() << endl;
		history.pop();
	}

	cout << setfill('=') << fixed;
	cout << setw(lineSize) << "" << endl;
	cout << setfill(' ') << fixed << endl << endl;
}

void BankAccounts::add()
{
	/* Create a new accout & add it to the bank list */
	if (currentCustomers < 10)
	{
		BankAccount act;

		cout << endl;
		cin.ignore();
		act.setName(enterString("Enter a name> "));

		cout << "~~~ Date ~~~\n";
		act.setDate(enterDate());

		cout << """~~~ Payment system ~~~\n\
1. Visa\n\
2. Mastercard\n\
3. Discovery\n\
4. American Express\n""";
		unsigned short selectedNum;
		while (true)
		{
			cout << "Enter number> ";
			cin >> selectedNum;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cerr << "ERROR: Incorect number. Try again !\n\t";
				cerr << "number must be from 1" << " to " << 4 << endl << endl;
				continue;
			}
			if (selectedNum > 0 && selectedNum <= 4)
				break;
			cerr << "ERROR: Numbe must be from 1" << " to " << 4 << endl << endl;
		}
		act.setCardNumber(generateCardNum(static_cast<PaymentSystem>(selectedNum - 1)));
		cout << endl << endl;

		customersList[currentCustomers] = act;
		currentCustomers++;
	}
	else
	{
		cerr << "ERROR: You can't add new accout!\n\tThe bank list is full!\n\n";
	}
}

void BankAccounts::edit(size_t id)
{
	if (id < 0 || id >= currentCustomers)
	{
		cerr << "ERROR: The account with this id doesn't exist\n\n";
		return;
	}

	cout << """What field to edit?\n\
1. Name\n\
2. Date\n\
3. Card Number\n""";
	unsigned short selectedNum;
	while (true)
	{
		cout << "Enter number> ";
		cin >> selectedNum;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "ERROR: Incorect number. Try again !\n\t";
			cerr << "number must be from 1" << " to " << 3 << endl << endl;
			continue;
		}
		if (selectedNum > 0 && selectedNum <= 3)
			break;
		cerr << "ERROR: Numbe must be from 1" << " to " << 3 << endl << endl;
	}

	switch (selectedNum)
	{
	case 1:
		cout << endl;
		cin.ignore();
		customersList[id].setName(enterString("Enter a name> "));
		break;
	case 2:
		cout << "~~~ Date ~~~\n";
		customersList[id].setDate(enterDate());
		cout << endl;
		break;
	case 3:
		cout << """~~~ Payment system ~~~\n\
1. Visa\n\
2. Mastercard\n\
3. Discovery\n\
4. American Express\n""";
		unsigned short selectedNum;
		while (true)
		{
			cout << "Enter number> ";
			cin >> selectedNum;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cerr << "ERROR: Incorect number. Try again !\n\t";
				cerr << "number must be from 1" << " to " << 4 << endl << endl;
				continue;
			}
			if (selectedNum > 0 && selectedNum <= 4)
				break;
			cerr << "ERROR: Numbe must be from 1" << " to " << 4 << endl << endl;
		}
		customersList[id].setCardNumber(generateCardNum(static_cast<PaymentSystem>(selectedNum - 1)));
		cardNumList[id] = customersList[id].getCardNumber();
		cout << endl << endl;
		break;
	}
}

void BankAccounts::del(size_t id)
{
	/* Delete an account from the bank list */
	if (id < 0 || id >= currentCustomers)
	{
		cerr << "ERROR: The account with this id doesn't exist\n\n";
		return;
	}

	cout << "Delete " << customersList[id].getName() << "'s account...\n\n";
	for (size_t i = id; i < currentCustomers - 1; i++)
	{
		customersList[i] = customersList[i + 1];
		cardNumList[i] = cardNumList[i + 1];
	}

	currentCustomers--;
}

void BankAccounts::enterAmount(bool isTopUp)
{
	/* Top up an account or withdraw money
		isTopUp == true ? top up : withdraw*/
	while (true)
	{
		// enter a card number
		cin.ignore();
		string card = enterString("Enter your card number\n> ");

		// check if such a number exist
		for (size_t i = 0; i < currentCustomers; i++)
		{
			if (customersList[i].getCardNumber() == card)
			{
				// enter the amount
				float amount;
				bool iscorrectinput;
				while (true)
				{
					cout << "Amount: ";
					cin >> amount;
					iscorrectinput = cin.fail();
					cin.clear();
					cin.ignore(100, '\n');

					if (!iscorrectinput && amount > 0.0f) {
						break;
					}

					cerr << "ERROR: Amount must be > 0.0\n" << endl;
				}

				// set value
				if (isTopUp)	// top up
					customersList[i].transferMoney(amount);
				else			// withdraw
					customersList[i].transferMoney(-amount);
				cout << endl;
				return;
			}
		}
		cerr << "ERROR: There isn't such card number\n\tTry again\n\n";
	}
}

void BankAccounts::sort()
{
	/* Bank list sorting by card numbers */
	cout << "Sorting by card numbers..." << endl;

	BankAccount temp;
	string str;
	for (size_t i = 0; i < currentCustomers - 1; i++)
	{
		for (size_t j = 0; j < currentCustomers - 1 - i; j++)
		{
			if (cardNumList[j] > cardNumList[j + 1])
			{
				temp = customersList[j];
				customersList[j] = customersList[j + 1];
				customersList[j + 1] = temp;

				str = cardNumList[j];
				cardNumList[j] = cardNumList[j + 1];
				cardNumList[j + 1] = str;
			}
		}
	}
	cout << endl;
}

void BankAccounts::accounts(string name)
{
	string cardNumber;
	cout << "============ " << name << " ============\n";

	cout << left;
	for (size_t i = 0; i < currentCustomers; i++)
	{
		if (customersList[i].getName() == name)
		{
			cardNumber = customersList[i].getCardNumber();
			cout << setw(18) << cardNumber << "| ";
			if (cardNumber[0] == '4')
				cout << "Visa";
			else if (cardNumber[0] == '5')
				cout << "Mastercard";
			else if (cardNumber[0] == '6')
				cout << "Discover";
			else if (cardNumber[0] == '3' && cardNumber[1] == '7')
				cout << "American Express";
			cout << endl;
		}
	}

	cout << setfill('=') << fixed;
	cout << "============ " << setw(name.size()) << "" << " ============\n\n\n";
	cout << setfill(' ') << fixed;
}

string BankAccounts::enterString(const char* text)
{
	/* String input verification */
	cout << left;
	string value;
	while (true)
	{
		cout << text;
		getline(cin, value);
		if (value != "") {
			break;
		}

		cerr << "ERROR: You have to enter something\n\n" << endl;
	}
	return value;
}

string BankAccounts::enterDate()
{
	/* Return the date of '02.05.2024' format */
	size_t day, month, year;
	string date = "";
	bool iscorrectinput;

	while (true)
	{
		cout << "year:\t";
		cin >> year;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n" << endl;
		else if (year <= 0)
			cerr << "ERROR: Year must be > 0\n" << endl;
		else
			break;
	}
	while (true)
	{
		cout << "month:\t";
		cin >> month;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n" << endl;
		else if (month <= 0 || month > 12)
			cerr << "ERROR: Month must be > 0 and <= 12\n" << endl;
		else
			break;
	}
	while (true)
	{
		cout << "day:\t";
		cin >> day;
		iscorrectinput = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (iscorrectinput)
			cerr << "ERROR: Incorect input, try again !\n" << endl;
		else if (isin(month, { 1,3,5,7,8,10,12 }) && day > 31)
			cerr << "ERROR: Day must be > 0 and <= 31\n" << endl;
		else if (isin(month, { 4,6,9,11 }) && day > 30)
			cerr << "ERROR: Day must be > 0 and <= 30\n" << endl;
		else if (month == 2 && year % 4 == 0 && day > 29)
			cerr << "ERROR: Day must be > 0 and <= 29\n" << endl;
		else if (month == 2 && year % 4 != 0 && day > 28)
			cerr << "ERROR: Day must be > 0 and <= 28\n" << endl;
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

unsigned short BankAccounts::calcCheckDigit(const string& card_number)
{
	/* Generate a last digit of the card number by the Luhn algorithm */
	short total = 0;
	size_t length = card_number.length();

	for (short i = length - 2; i >= 0; i -= 2) {
		short digit = card_number[i] - '0';
		digit *= 2;
		if (digit > 9) {
			digit -= 9;
		}
		total += digit;
	}

	for (short i = length - 1; i >= 0; i -= 2) {
		total += card_number[i] - '0';
	}

	unsigned short check_digit = (10 - (total % 10)) % 10;
	return check_digit;
}

string BankAccounts::generateCardNum(PaymentSystem paySys)
{
	/* Generate a card number according to the template
	   4/5/6/37 + rand digits(13 or 12) + check digit = 15 or 16 digits */
generateAgain:
	string cardNumber{};
	
	// add the first digits
	switch (paySys)
	{
	case VISA:
		cardNumber += "4";
		break;
	case MASTERCARD:
		cardNumber += "5";
		break;
	case DISCOVER:
		cardNumber += "6";
		break;
	case AMERICAN_EXPRESS:
		cardNumber += "37";
		break;
	default:
		cerr << "ERROR: Incorrect payment system\n\n";
		return string();
	}

	// generate the other digits
	srand(time(NULL));
	for (size_t i = 0, repTimes = paySys == AMERICAN_EXPRESS ? 12 : 14; i < repTimes; i++)
	{
		cardNumber += to_string(rand() % 9);
	}

	// calc the check digit
	cardNumber += to_string(calcCheckDigit(cardNumber));

	// unique card verification
	for (size_t i = 0; i < currentCustomers; i++)
	{
		if (cardNumber == cardNumList[i])
			goto generateAgain;
	}
	cardNumList[currentCustomers] = cardNumber;

	return cardNumber;
}

template <typename T>
bool BankAccounts::isin(T value, vector<T> list)
{
	for (size_t i = 0, s = list.size(); i < s; i++)
	{
		if (value == list[i])
			return true;
	}
	return false;
}