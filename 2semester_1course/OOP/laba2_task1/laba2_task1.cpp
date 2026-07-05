#include "BankAccount.h"

void showInfo(BankAccount act);


int main()
{
    BankAccount act1("Kevin Mitnick", 1, 10, 1963);
    BankAccount act2("Poor Stud", 22, 2, 2024);
    BankAccount act3("Goat Rosa", 21, 8, 2020);

    act1.topUp(1000000.f);
    act2.topUp(2000.f);

    showInfo(act1);
    showInfo(act2);
    showInfo(act3);

    system("PAUSE");
    return 0;
}


void showInfo(BankAccount act)
{
    queue<string> history = act.getHistory();

    cout << "--- ---- ----- ----- ---- ---" << endl;
    cout << "Name:\t" << act.getName() << endl;

    cout << "Date:\t" << act.getDate() << endl;

    cout << "Money:\t" << act.getMoney() << endl;

    cout << "History:\n";
    for (size_t i = 0; !history.empty(); i++)
    {
        cout << i + 1 << ". " << history.front() << endl;
        history.pop();
    }
    cout << "--- ---- ----- ----- ---- ---\n" << endl;
}
