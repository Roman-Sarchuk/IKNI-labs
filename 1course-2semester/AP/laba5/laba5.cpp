#include "AVLTree.h"
#include "Tree.h"

int main()
{
    int number[] = { 20, 15, 5, 8, 6, 45 };

    // BS tree
    Tree simpleTree;

    for (size_t i = 0, length = sizeof(number) / sizeof(number[0]); i < length; i++)
    {
        simpleTree.add(number[i]);
    }

    simpleTree.showAsTree();
    cout << "-------------------" << endl;

    // AVL tree
    AVLTree tree;

    for (size_t i = 0, length = sizeof(number)/sizeof(number[0]); i < length; i++)
    {
        tree.insert(number[i]);
    }

    tree.showAsTree();
    cout << "Max: " << tree.getMax();

    system("PAUSE");
    return 0;
}