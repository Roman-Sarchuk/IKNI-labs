#include "BookStack.h"

BookStack::~BookStack()
{
	clear();
}

void BookStack::show()
{
	if (top == nullptr)			// if steck is void
	{
		cout << "None" << endl;
		return;
	}

	cout << "--- Book Stack ---" << endl;
	ref current = top;
	while (true)
	{
		cout << "NAME  : " << current->name << endl;
		cout << "VALUE : " << current->value << endl;
		current = current->pNext;
		if (!current)
			break;
		cout << endl;

	}
	cout << "--- ---- ----- ---" << endl;
}

void BookStack::add(string name, float value)
{

	if (top == nullptr)		// if steck is void
	{
		top = new Book(name, value);
	}
	else					// if steck has some element
	{
		ref temp = new Book(name, value);
		temp->pNext = top;
		top = temp;
	}

	length++;
}

pair<string, float> BookStack::pop()
{
	if (top == nullptr)		// if steck is void
	{
		return pair<string, float>();
	}

	name = top->name;
	value = top->value;

	deleteElem();

	return pair<string, float>(name, value);
}

void BookStack::clear()
{
	if (top == nullptr)			// if steck is void
	{
		return;
	}

	while (length)
	{
		deleteElem();
	}
}

float BookStack::calcAverageValue()
{
	float average = 0.f;

	ref current = top;
	while (current)
	{
		average += current->value;
		current = current->pNext;
	}

	return average / length;
}

void BookStack::deleteElem()
{
	ref temp = top;
	top = temp->pNext;
	delete temp;
	temp = nullptr;

	length--;
}
