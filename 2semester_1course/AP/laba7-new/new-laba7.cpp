#include <iostream>
#include <Windows.h>
#include "HashTable.h"


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    string text = "Літо, тіло, от, то; Колічка де гроші а? Коля шо за спави... Оліт";
    AnagramCounter counter(text);

    cout << "Текст:\n" << text << endl << endl;
    cout << "Хеш-Таблиця:\n";
    counter.outputTable();
    cout << "\n  Anagrama:\t} " << counter.getCount() << " {\n\n";

    system("PAUSE");
    return 0;
}