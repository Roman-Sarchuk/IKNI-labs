#include "AVLTree.h"

unsigned char AVLTree::height(node* p)
{
    /*
        DESCRIPTION:
        Calculate the height of a node
        Returns the height of the node if it exists, otherwise 0
    */
    return p ? p->height : 0;
}

int AVLTree::bfactor(node* p)
{
    /*
        DESCRIPTION:
        Calculate the balance factor of a node
        (R - L)
    */
    return height(p->right) - height(p->left);
}

void AVLTree::fixheight(node* p)
{
    /*
        DESCRIPTION:
        Update the height of a node based on its children's heights
    */
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

AVLTree::node* AVLTree::rotateright(node* p)
{
    /*
        DESCRIPTION:
        Perform a right rotation at a given node
    */
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

AVLTree::node* AVLTree::rotateleft(node* q)
{
    /*
        DESCRIPTION:
        Perform a left rotation at a given node
    */
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

AVLTree::node* AVLTree::balance(node* p)
{
    /*
        DESCRIPTION:
        balance a node in the AVL tree
    */
    fixheight(p);
    if (bfactor(p) == 2)    // If the balance factor is 2 (right-heavy)
    {
        if (bfactor(p->right) < 0)  // If the right child is left-heavy
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)    // If the balance factor is -2 (left-heavy)
    {
        if (bfactor(p->left) > 0)   // If the left child is right-heavy
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

AVLTree::node* AVLTree::insert(node* p, int k)
{
    /*[Recursive function] -> return node if the p pointer is nullptr
        DESCRIPTION:
        Insert a new node into the tree
    */
    if (p == nullptr) return new node(k);
    if (k > p->key)
        p->right = insert(p->right, k);
    else
        p->left = insert(p->left, k);
    return balance(p);
}

AVLTree::node* AVLTree::remove(node* p, int k)
{
    /*[Recursive function] -> return nullptr if the element pointer is nullptr
        DESCRIPTION:
        Remove a node from the tree
    */
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
}

void AVLTree::showAsTree(node* root, int indent)
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

void AVLTree::showAsList(node* elem)
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

void AVLTree::del(node*& root)
{
    /*[Recursive function] -> exit if the element pointer is nullptr
        DESCRIPTION:
        Delete all nodes in the AVL tree
    */
    if (root == nullptr)
        return;

    del(root->left);
    del(root->right);

    delete root;
    root = nullptr;
}

void AVLTree::insert(int data)
{
    /*[public interface]
        DESCRIPTION:
        to call 'insert(node* p, int k)'
    */
    root = insert(root, data);
}

void AVLTree::remove(int value)
{
    /*[public interface]
        DESCRIPTION:
        to call 'del(node*& root)'
    */
    root = remove(root, value);
}

int AVLTree::getMax()
{
    /*
        DESCRIPTION:
        Get the maximum key in the AVL tree
    */
    if (root == nullptr)
        return 0;

    node* current = root;
    while (current->right)
        current = current->right;
    return current->key;

}

void AVLTree::showAsList()
{
    /*[public interface]
        DESCRIPTION:
        to call 'showAsList(node* root)'
    */
    showAsList(root);
}

void AVLTree::showAsTree()
{
    /*[public interface]
        DESCRIPTION:
        to call 'showAsTree(node* root, int indent)'
    */
    showAsTree(root);
}

void AVLTree::clear()
{
    /*[public interface]
        DESCRIPTION:
        to call 'del(node*& root)'
    */
    if (root == nullptr)
        return;

    del(root);
}

AVLTree::~AVLTree()
{
    clear();
}
