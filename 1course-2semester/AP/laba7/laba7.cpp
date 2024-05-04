#include "BTree.h"

int main()
{
    vector<int> inValues = { 20,34,29,100, 4, 6,13,19,130,8,15 };
    vector<int> outValues = { 8, 130, 13, 34 };
    BTree tree(5);

    for (int value : inValues)
    {
        cout << "----------------------------- in(" << value << ")" << endl;
        tree.insert(value);
        tree.show();
    }
    cout << "-----------------------------" << endl;

    cout << "\n+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+\n" << endl;
    for (int value : outValues)
    {
        cout << "----------------------------- out(" << value << ")" << endl;
        tree.remove(value);
        tree.show();
    }
    cout << "-----------------------------" << endl;

    system("PAUSE");
    return 0;
}
