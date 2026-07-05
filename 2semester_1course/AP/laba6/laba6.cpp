#include "TwoFourTree.h"


int main()
{
    int value[] = { 9,3,6,1,5,7,8,40,12,24,89,74,32,10,15,140 };
    TwoFourTree tree;

    for (size_t i = 0, length = sizeof(value)/sizeof(value[0]); i < length; i++)
    {
        tree.insert(value[i]);
    }

    tree.showAsList();
    cout << "\n------------------------ Delete(6)\n\n";

    tree.remove(6);

    tree.showAsList();
    cout << "\n------------------------ Delete(9)\n\n";

    tree.remove(9);

    tree.showAsList();

    system("PAUSE");
    return 0;
}
