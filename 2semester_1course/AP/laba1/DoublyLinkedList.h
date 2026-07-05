#pragma once

template <typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();

	void show();
	void push_back(T data);
	void popFront();
	void clear();
	void reverse();

	inline size_t getLength() { return length; }

	T& operator[](const size_t index);

private:
	struct Node;
	typedef Node* ref;

	struct Node
	{
		ref pNext;
		ref pPrev;
		T data;

		Node(T data = T(), ref pNext = nullptr, ref pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};

	ref head;
	ref tail;
	size_t length;
};
