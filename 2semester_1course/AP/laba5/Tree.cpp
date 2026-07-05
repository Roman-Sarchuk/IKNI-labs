#include "Tree.h"

void Tree::showAsTree(ref root, int indent)
{
    /*[Recursive function] -> exit if the element pointer is nullptr
        DESCRIPTION:
        Display the AVL tree as a tree structure
    */
    if (root == nullptr)
        return;

    showAsTree(root->right, indent + 4);

    for (int i = 0; i < indent; i++)
        std::cout << " ";

    std::cout << root->key << std::endl;

    showAsTree(root->left, indent + 4);
}

void Tree::showAsList(ref elem)
{
    /*[Recursive function] -> exit if the element pointer is nullptr
        DESCRIPTION:
        Output the keys of tree form the left subtrees to the right ones
        FOR INSTANCE:
        5
        13
        45     (root)
        90
        50
    */
    if (elem == nullptr)
        return;

    // Show a left subtree
    showAsList(elem->left);

    cout << elem->key;
    if (elem == root)
        cout << "\t(root)";
    cout << endl;

    // Show a right subtree
    showAsList(elem->right);
}

void Tree::del(ref& root)
{
    /*[Recursive function] -> exit if the element pointer is nullptr
        DESCRIPTION:
        Delete all elements using DFS
    */
    if (root == nullptr)
        return;

    del(root->left);
    del(root->right);

    delete root;
    root = nullptr;
}

void Tree::showAsList()
{
    /*
        DESCRIPTION:
        Output a tree in the console as list
        EXCEPTION:
        the tree doesn't have the elements => return
    */
    if (root == nullptr)
        return;

    showAsList(root);
}

void Tree::showAsTree()
{
    /*
        DESCRIPTION:
        Output a tree in the console as tree
        EXCEPTION:
        the tree doesn't have the elements => return
    */
    if (root == nullptr)
        return;

    showAsTree(root);
}

void Tree::add(int key)
{
    /*
        DESCRIPTION:
        Add a new node to the tree.
    */
    ref elem = new node(key);

    if (root == nullptr)    // if a tree is void
    {
        root = elem;
        return;
    }

    ref current = root;
    ref parent = nullptr;

    while (current != nullptr)
    {
        parent = current;
        if (key > current->key)
            current = current->right;
        else
            current = current->left;
    }

    if (key < parent->key)
        parent->left = elem;
    else
        parent->right = elem;
}

void Tree::add(const vector<int>& keys)
{
    /*
        DESCRIPTION:
        Add the list of node to the tree
    */

    for (unsigned int i = 0u; i < keys.size(); ++i)
    {
        add(keys[i]);
    }
}

// to call 'del(ref& root)' from outside
void Tree::clear()
{
    /*
        DESCRIPTION:
        Delete all tree elements
    */

    del(root);
}

Tree::~Tree()
{
    clear();
}
