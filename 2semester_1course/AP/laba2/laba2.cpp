#include "BookStack.h"
//#include "BookStack.cpp"


int main()
{
    pair<string, float> book;
    BookStack bookStack;

    bookStack.add("The Hunger Games", 563);
    bookStack.add("Harry Potter", 684);
    bookStack.add("The Book Thief", 365);

    cout << "Hello! I have this books. They're awesome:" << endl;
    bookStack.show();
    cout << "By the way, Their average value is " << bookStack.calcAverageValue() << endl;

    cout << "\nI would like to give my new book\n";
    book = bookStack.pop();
    cout << "\"" << book.first << "\"";
    cout << " for you! ;)" << endl;
    cout << "If anything, it cost " << book.second << "! Remember this..." << endl;

    cout << "\nSo I will keep the other old books to myself." << endl;
    bookStack.show();

    system("PAUSE");
    return 0;
}
