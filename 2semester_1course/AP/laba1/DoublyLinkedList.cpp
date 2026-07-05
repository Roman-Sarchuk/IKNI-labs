#include "DoublyLinkedList.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	length = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

template<typename T>
void DoublyLinkedList<T>::show()
{
	ref current = head;

	cout << "[ ";
	if (current != nullptr)
	{
		while (true)
		{
			cout << current->data;
			if (current->pNext == nullptr)
				break;
			cout << " ";
			current = current->pNext;
		}
	}
	cout << " ]" << endl;
	
}

template<typename T>
void DoublyLinkedList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node(data);
		tail = head;
	}
	else
	{
		tail->pNext = new Node(data, nullptr, tail);
		tail = tail->pNext;
	}

	length++;
}

template<typename T>
void DoublyLinkedList<T>::popFront()
{
	ref temp = head;

	head = head->pNext;

	delete temp;

	length--;
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
	tail = nullptr;

	while (length)
	{
		popFront();
	}
}

template<typename T>
void DoublyLinkedList<T>::reverse()
{
	ref start = head;
	ref end = tail;

	T temp;
	for (size_t i = 0, len = length / 2; i < len; i++)
	{
		temp = start->data;
		start->data = end->data;
		end->data = temp;

		start = start->pNext;
		end = end->pPrev;
	}
}

template<typename T>
T& DoublyLinkedList<T>::operator[](const size_t index)
{
	size_t counter;
	ref current;

	if (index <= length / 2)
	{
		counter = 0;
		current = head;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else
	{
		counter = length - 1;
		current = tail;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pPrev;
			counter--;
		}
	}
}
