#include "KeyTree.h"

int main()
{
    KeyTree tree;

    tree.add({ 90, 74, 80, 98, 105, 102, 114 }, { "IN", "ON", "NO", "IF", "OF", "EL", "DO" });

    tree.show();

    system("PAUSE");
    return 0;
}
