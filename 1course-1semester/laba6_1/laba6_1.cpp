// laba6, task1, variant7
#include <iostream>
using namespace std;

char* inputStr();
bool isDoubleLatter(const char* const str);

int main()
{
	char* str;

	cout << ":Enter some string:" << endl;
	str = inputStr();

	cout << "\nChecking if in your string has duble latter..." << endl;
	if (isDoubleLatter(str))
		cout << "it's TRUE... There is duble !" << endl;
	else
		cout << "it's FALSE... There isn't duble !" << endl;

	delete[] str;
	str = nullptr;

	system("PAUSE");
	return 0;
}


void increaseSize(char*& str, size_t* size, const size_t value = 50) {
	/*	Increase number of elements in char array
	str -> pointer to the link of char array
	size -> start size of char array
	value -> number of elements which you need to increase your array*/
	char* newArray = new char[*size + value];

	// Copy elements of str array in newArray
	for (size_t i = 0; i < *size; i++)
	{
		newArray[i] = str[i];
	}

	delete[] str;
	str = newArray;
	*size += value;
}

char* inputStr()
{
	/*	Get chars from consol and input them into char array.
		Increase size of array if char array is small to get all chars
		Stop geting chars from cin if you enter '\n' */
	size_t size = 50, i = 0;
	char* str = new char[size];
	char ch;

	do
	{
		ch = getchar();
		if (i == size)
			increaseSize(str, &size);
		str[i] = ch;
		if (ch == '\n')
			break;
		i++;
	} while (true);

	return str;
}

bool isDoubleLatter(const char* const str)
{
	/*	Check if array has double latters
	str -> chat array pointer*/
	char temp = NULL;
	for (size_t i = 0; str[i] != '\0' && str[i] != '\n'; i++)
	{
		if (temp == str[i])
			return true;
		temp = str[i];
	}
	return false;
}
