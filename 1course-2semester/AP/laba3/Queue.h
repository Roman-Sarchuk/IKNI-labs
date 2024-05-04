#pragma once

template <typename T>
class Queue
{
	/* A simple queue that works according to the FIFO */
protected:
	struct Elem;
	typedef Elem* ref;
	struct Elem
	{
		T data;
		ref pNext = nullptr;
	};

	ref pFirst = nullptr;
	ref pLast = nullptr;
	T value = T();
	size_t length = 0;

public:
	void add(T value);
	T pop();
	inline T getPopValue() { return value; }
	inline size_t getLength() { return length; }
};
