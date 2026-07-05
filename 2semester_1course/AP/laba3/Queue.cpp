#include "Queue.h"

template<typename T>
void Queue<T>::add(T value)
{
	/* add a new element to end of queue */
	ref elem = new Elem;
	elem->data = value;

	if (pFirst == nullptr)
	{
		pFirst = elem;
		pLast = elem;
	}
	else
	{
		pLast->pNext = elem;
		pLast = elem;
	}
}

template<typename T>
T Queue<T>::pop()
{
	/* delete a firt elemet of the queue
		+ save a value of the deleted element
		+ return the seved value	*/
	if (pFirst == nullptr)
	{
		return T();
	}
	else
	{
		ref temp = pFirst;

		// transfer point
		value = pFirst->data;
		pFirst = pFirst->pNext;
		
		// deleting
		if (!pFirst)
		{
			pLast = nullptr;
		}
		delete temp;
		temp = nullptr;
	}

	return value;
}