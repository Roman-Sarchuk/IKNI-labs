#include "Queue.cpp"
#include <iostream>
using std::cout;
using std::endl;

class IntQueue : public Queue<int>
{
public:
    bool verifyRange();
    void print();
};


int main()
{
    IntQueue queue1;
    IntQueue queue2;

    // Fill queues
    int start = 3, end = 10;
    for (int i = start; i < end; i++)
    {
        queue1.add(i);
    }
    for (int i = start; i < end; i++)
    {
        queue2.add(rand()% end);
    }

    // Output result
    cout << "Queue #1" << endl;
    queue1.print();
    cout << "Is queue 1 as a range?  ->  " << (queue1.verifyRange() ? "True" : "False") << endl << endl;
    cout << "Queue #2" << endl;
    queue2.print();
    cout << "Is queue 2 as a range?  ->  " << (queue2.verifyRange() ? "True" : "False") << endl << endl;

    system("PAUSE");
    return 0;
}


bool IntQueue::verifyRange()
{
    /* return true if all the elemets in the queue form a range */
    ref current = pFirst;
    while (current && current->pNext)
    {
        if (current->data != current->pNext->data - 1)
        {
            return false;
        }

        current = current->pNext;
    }

    return true;
}

void IntQueue::print()
{
    /* Output the queue in the console */
    cout << "{ ";
    ref current = pFirst;
    while (current != nullptr)
    {
        cout << current->data;
        current = current->pNext;
        if (current != nullptr)
        {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}
