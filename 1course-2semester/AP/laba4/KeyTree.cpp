#include "KeyTree.h"

// private
void KeyTree::showAsList(ref elem)
{
    /*[Recursive function] -> exit if the element pointer is nullptr
        DESCRIPTION:
        Output the keys and data of tree form the left subtrees to the right ones
        FOR INSTANCE:
        5: cyber 
        13: uber
        45: off     (root)
        90: hello
        50: great
    */
    if (elem == nullptr)
        return;

    // Show a left subtree
    showAsList(elem->left);

    cout << elem->key << ": " << elem->data;
    if (elem == root)
        cout << "\t(root)";
    cout << endl;

    // Show a right subtree
    showAsList(elem->right);
}

void KeyTree::del(ref& root)
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

KeyTree::ref KeyTree::find(int key)
{
    /*
        DESCRIPTION:
        This algorithm uses an iterative approach to find a node 
        with a specified key in a binary tree, traversing the 
        nodes until it finds the key it is looking for or reaches 
        the end of the tree.
    */
    ref current = root;

    while (current)
    {
        if (current->key == key)
            return current;
        else if (current->key < key)
            current = current->left;
        else
            current = current->right;
    }

    return nullptr;
}

// public
void KeyTree::show()
{
    /*
        DESCRIPTION:
        Output a tree in the console
        EXCEPTION: 
        the tree doesn't have the elements => return
    */
    if (root == nullptr)
        return;

    showAsList(root);
}

void KeyTree::add(int key, string value)
{
    /*
        DESCRIPTION:
        Add a new node to the tree.
        EXCEPTION: 
        If the given key already exists => return without insertion
    */
	ref elem = new node(key, value);

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
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else    // if key already exists, return without insertion
        {
            delete elem;
            return;
        }
    }

    if (key < parent->key)
        parent->left = elem;
    else
        parent->right = elem;
}

void KeyTree::add(const vector<int>& keys, const vector<string>& values)
{
    /*
        DESCRIPTION:
        Add the list of node to the tree
        EXCEPTION: 
        if a vector size of keys and values don't math => throw the invalid_argument
    */
    if (keys.size() != values.size())
        throw std::invalid_argument("The number of elements in the vector of keys and values don't match");

    for (unsigned int i = 0u; i < keys.size(); ++i)
    {
        add(keys[i], values[i]);
    }
}

void KeyTree::del(int key)
{
    /*
    DESCRIPTION:
    Find the node of the binary tree by 
    the given key and delete it.
    */
    ref elem = find(key);
    
    if (elem != nullptr)
    {
        delete elem;
        elem = nullptr;
    }
}

// to call 'del(ref& root)' from outside
void KeyTree::clear()
{
    /*
        DESCRIPTION:
        Delete all tree elements
    */

    del(root);
}

string KeyTree::getData(int key)
{
    /*
        DESCRIPTION:
        Retrieves the data from the node 
        of the binary tree by the given 
        key and returns it.
    */
    ref elem = find(key);

    if (elem != nullptr)
        return elem->data;
    return string();
}

KeyTree::~KeyTree()
{
    clear();
}
