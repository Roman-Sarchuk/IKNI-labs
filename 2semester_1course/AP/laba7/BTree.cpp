#include "BTree.h"

void BTree::showAsList(ref root, int level)
{
    if (root == nullptr)
        return;

    // Print keys of current node
    for (int i = 0; i < root->keys.size(); ++i)
        cout << root->keys[i] << " ";
    cout << endl;

    // Recursively print children with proper indentation
    for (int i = 0; i < root->children.size(); ++i) {
        cout << string(level + 1, '\t'); // Indentation based on the level
        showAsList(root->children[i], level + 1);
    }
}

void BTree::del(ref node)
{
    // If the node is empty, there's no need to delete its children
    if (node == nullptr)
        return;

    // Recursively delete all children of the current node
    for (auto child : node->children) {
        del(child);
    }

    // Delete the node itself
    delete node;
}

BTree::ref BTree::findParent(ref node)
{
    if (node == root)
        return nullptr;

    ref current = root;
    while (current != nullptr)
    {
        // check if a node is in the children list
        if (find(current->children.begin(), current->children.end(), node) != current->children.end())
            return current;
        // go to a kid
        if (node->keys[0] > current->keys[current->keys.size() - 1])
            current = current->children[current->keys.size()];
        for (unsigned short i = 0, length = current->keys.size(); i < length; i++)
        {
            if (node->keys[0] <= current->keys[i])
            {
                current = current->children[i];
                break;
            }
        }
    }

    return nullptr;
}

void BTree::spell(ref node)
{
    // if the node doesn't need to spell
    if (node->keys.size() < m)
        return;

    // get the values
    vector<int> arr1, arr2;
    int key;
    if (m % 2 == 0) // if 'm' is even
    {
        copy(node->keys.begin(), node->keys.begin() + (m / 2 - 1), back_inserter(arr1));
        key = node->keys[m / 2 - 1];
        copy(node->keys.begin() + m / 2, node->keys.end(), back_inserter(arr1));
    }
    else            // if 'm' is odd
    {
        copy(node->keys.begin(), node->keys.begin() + m % 2, back_inserter(arr1));
        key = node->keys[m % 2];
        copy(node->keys.begin() + (m % 2 + 1), node->keys.end(), back_inserter(arr2));
    }
    ref parent = findParent(node);

    // if the node is a leaf
    if (node->children.empty())
    {
        // if the node doesn't have the parent
        /* this node is a root without children */
        if (parent == nullptr)
        {
            ref left = new Node, right = new Node;
            left->keys = arr1;
            right->keys = arr2;
            node->keys = { key };
            node->children = { left, right };
            return;
        }
        /* 
        separate the right part from a node and set the left keys(arr1) to thus node
        create a right node and set right keys(arr2)
        add the right node to a parent of separated node as second kid
        */
        parent->keys.push_back(key);
        sort(parent->keys.begin(), parent->keys.end());

        node->keys = arr1;
        ref right = new Node;
        right->keys = arr2;
        parent->children.insert(parent->children.begin() + 1, right);

        spell(parent);
    }
    else
    {
        // if the node doesn't have the parent
        /* this node is a root with children */
        if (parent == nullptr)
        {
            root = new Node;
            root->keys.push_back(key);

            node->keys = arr1;
            ref right = new Node;
            right->keys = arr2;
            root->children.push_back(node);
            root->children.push_back(right);

            for (vector<ref>::iterator it = node->children.begin() + m % 2; it != node->children.end(); it++)
            {
                right->children.push_back(*it);
            }
            node->children.resize(m % 2);

            spell(root);
        }
        parent->keys.push_back(key);
        sort(parent->keys.begin(), parent->keys.end());

        node->keys = arr1;
        ref right = new Node;
        right->keys = arr2;
        parent->children.insert(parent->children.begin() + 1, right);

        for (vector<ref>::iterator it = node->children.begin() + m % 2; it != node->children.end(); it++)
        {
            right->children.push_back(*it);
        }
        node->children.resize(m % 2);

        spell(root);
    }
}

int BTree::findKeyIndex(ref node, int key) {
    int index = 0;
    while (index < node->keys.size() && node->keys[index] < key)
        ++index;

    // Ensure that the index is within the bounds of the vector
    if (index >= node->keys.size())
        return node->keys.size() - 1; // If index exceeds the vector size, return the last valid index
    else
        return index;
}

void BTree::removeFromNode(ref node, int index) {
    // Check if the index is valid
    if (index >= 0 && index < node->keys.size()) {
        // Remove the key from the node
        node->keys.erase(node->keys.begin() + index);
    }
    else {
        cout << "Error: Invalid index for key removal." << endl;
    }
}

void BTree::fixAfterDeletion(ref node, ref parent) {
    // Check if the node has a satisfactory number of keys
    if (node->keys.size() >= (m + 1) / 2)
        return; // No further fixing needed

    // If the node is too small, we have additional work
    // Removing the specified key might affect the parent node
    if (parent == nullptr) {
        // If the node is the root of the tree
        if (node->keys.empty()) {
            // If the root is empty but has child nodes, remove it and promote one of its children as the new root
            root = node->children[0];
            delete node;
        }
        return;
    }

    // Otherwise, we look for siblings relative to our node
    int siblingIndex;
    ref leftSibling{}, rightSibling{};

    siblingIndex = findSiblingIndex(parent, node);
    if (siblingIndex != -1) {
        // If there is a neighboring node
        if (siblingIndex > 0)
            leftSibling = parent->children[siblingIndex - 1];
        if (siblingIndex < parent->keys.size())
            rightSibling = parent->children[siblingIndex + 1];

        if (leftSibling != nullptr && leftSibling->keys.size() > (m + 1) / 2) {
            // If the left sibling has sufficient keys
            borrowFromLeft(node, leftSibling, parent, siblingIndex - 1);
        }
        else if (rightSibling != nullptr && rightSibling->keys.size() > (m + 1) / 2) {
            // If the right sibling has sufficient keys
            borrowFromRight(node, rightSibling, parent, siblingIndex);
        }
        else if (leftSibling != nullptr) {
            // Merge with the left sibling if the right one is absent or has few keys
            mergeWithLeft(node, leftSibling, parent, siblingIndex - 1);
        }
        else if (rightSibling != nullptr) {
            // Merge with the right sibling if the left one is absent or has few keys
            mergeWithRight(node, rightSibling, parent, siblingIndex);
        }
    }
    else {
        // If we have no siblings, simplify the task by merging the node with its parent
        mergeWithParent(node, parent);
    }
}

int BTree::findSiblingIndex(ref parent, ref node) {
    // Find the index of the node in the parent node
    for (int i = 0; i < parent->children.size(); ++i) {
        if (parent->children[i] == node)
            return i;
    }
    return -1; // If the node is not a child of the parent
}

void BTree::borrowFromLeft(ref node, ref leftSibling, ref parent, int leftSiblingIndex) {
    // Borrow a key from the left sibling
    node->keys.insert(node->keys.begin(), parent->keys[leftSiblingIndex]);
    parent->keys[leftSiblingIndex] = leftSibling->keys.back();
    leftSibling->keys.pop_back();

    // If children are also present, move the corresponding child node
    if (!leftSibling->children.empty()) {
        node->children.insert(node->children.begin(), leftSibling->children.back());
        leftSibling->children.pop_back();
    }
}

void BTree::borrowFromRight(ref node, ref rightSibling, ref parent, int rightSiblingIndex) {
    // Borrow a key from the right sibling
    node->keys.push_back(parent->keys[rightSiblingIndex]);
    parent->keys[rightSiblingIndex] = rightSibling->keys.front();
    rightSibling->keys.erase(rightSibling->keys.begin());

    // If children are also present, move the corresponding child node
    if (!rightSibling->children.empty()) {
        node->children.push_back(rightSibling->children.front());
        rightSibling->children.erase(rightSibling->children.begin());
    }
}

void BTree::mergeWithLeft(ref node, ref leftSibling, ref parent, int leftSiblingIndex) {
    // Merge the node with the left sibling
    leftSibling->keys.push_back(parent->keys[leftSiblingIndex]);
    leftSibling->keys.insert(leftSibling->keys.end(), node->keys.begin(), node->keys.end());
    leftSibling->children.insert(leftSibling->children.end(), node->children.begin(), node->children.end());

    // Remove the node from the parent node and free memory
    parent->keys.erase(parent->keys.begin() + leftSiblingIndex);
    parent->children.erase(parent->children.begin() + leftSiblingIndex + 1);
    delete node;
}

void BTree::mergeWithRight(ref node, ref rightSibling, ref parent, int rightSiblingIndex) {
    // Merge the node with the right sibling
    node->keys.push_back(parent->keys[rightSiblingIndex]);
    node->keys.insert(node->keys.end(), rightSibling->keys.begin(), rightSibling->keys.end());
    node->children.insert(node->children.end(), rightSibling->children.begin(), rightSibling->children.end());

    // Remove the right sibling from the parent node and free memory
    parent->keys.erase(parent->keys.begin() + rightSiblingIndex);
    parent->children.erase(parent->children.begin() + rightSiblingIndex + 1);
    delete rightSibling;
}

void BTree::mergeWithParent(ref node, ref parent) {
    // Merge the node with the parent
    int parentIndex = 0;
    while (parentIndex < parent->children.size() && parent->children[parentIndex] != node)
        ++parentIndex;

    // Check if we can find the child node in the parent node
    if (parentIndex == parent->children.size()) {
        cout << "Error: Node not found in the parent node." << endl;
        return;
    }

    // Merge the node with the parent
    if (parentIndex > 0) {
        mergeWithLeft(node, parent->children[parentIndex - 1], parent, parentIndex - 1);
    }
    else {
        mergeWithRight(node, parent->children[parentIndex + 1], parent, parentIndex);
    }
}


BTree::BTree(unsigned short m)
{
	if (m > 2)
		this->m = m;
	else
		throw exception("ERROR: 'm' must be greater than 2");
}



void BTree::insert(int key)
{
    // if the tree is void
    if (root == nullptr)
    {
        root = new Node;
        root->keys.push_back(key);
        return;
    }

    ref current = root;

    // find a leaf
    if (!current->children.empty())
    {
        while (!current->children.empty())
        {
            // go to a kid
            if (key > current->keys[current->keys.size() - 1])
                current = current->children[current->keys.size()];
            for (unsigned short i = 0, length = current->keys.size(); i < length; i++)
            {
                if (key <= current->keys[i])
                {
                    current = current->children[i];
                    break;
                }
            }
        }
    }
    
    current->keys.push_back(key);
    sort(current->keys.begin(), current->keys.end());
    spell(current);
}

void BTree::remove(int key) {
    // Start with finding the element to be removed
    // We may also keep track of the parent node for further use
    ref parent = nullptr;
    ref current = root;
    int index = -1; // Index of the key we intend to remove

    while (current != nullptr) {
        // Find the appropriate index of the key in the current node
        index = findKeyIndex(current, key);

        if (index != -1 && current->keys[index] == key)
            break; // Key found for removal
        else {
            // Move to the next node to continue the search
            parent = current;
            if (index == -1 || index == current->keys.size() || key < current->keys[index])
                current = current->children[index];
            else
                current = current->children[index + 1];
        }
    }

    if (current == nullptr) {
        cout << "Key " << key << " not found for removal." << endl;
        return;
    }

    // Call the function to actually remove the key
    removeFromNode(current, index);

    // Check if the node remains valid after removal
    fixAfterDeletion(current, parent);
}

void BTree::clear()
{
    // Call a recursive helper function clearHelper with the root node
    del(root);
    // After deleting all nodes, set the root of the tree to nullptr
    root = nullptr;
}

void BTree::show()
{
	showAsList(root, 0);
}
