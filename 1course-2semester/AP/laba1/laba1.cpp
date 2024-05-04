#include <iostream>
#include "DoublyLinkedList.h"
#include "DoublyLinkedList.cpp"
using std::cin;

int main()
{
    DoublyLinkedList<char> list;

    cout << "Enter some text:" << endl;

	char ch;
	while (true)
	{
		ch = getchar();
		if (ch == '\n')
			break;
		list.push_back(ch);
	}

	cout << "\nYou enter:" << endl;
	list.show();
	cout << "Reverse:" << endl;
	list.reverse();
	list.show();

	system("PAUSE");
	return 0;
}
