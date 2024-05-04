#include "TwoFourTree.h"

void TwoFourTree::clear(ref& root)
{
    if (root == nullptr)
        return;

    // Recursively delete children
    for (ref child : root->children) {
        clear(child);
        delete child;
    }

    // Clear keys vector
    root->keys.clear();
}

void TwoFourTree::remove(ref& node, int key)
{
    // Find the key
    short index = 0;
    while (index < node->keys.size() && key > node->keys[index]) {
        ++index;
    }

    // Key found in this node
    if (index < node->keys.size() && key == node->keys[index]) {
        if (node->children.empty()) {
            // Case 1: Node is a leaf
            node->keys.erase(node->keys.begin() + index);
        }
        else {
            // Case 2: Node is an internal node
            int successorKey = findMinKeyNode(node->children[index + 1])->keys[0];
            remove(node->children[index + 1], successorKey);
            node->keys[index] = successorKey;
        }
    }
    else {
        // Key might be in a child node
        if (node->children.empty()) {
            // Key not found
            return;
        }

        bool keyInLastChild = (index == node->keys.size());
        if (node->children[index]->keys.size() == 1) {
            // Merge child with sibling if it has only one key
            if (index > 0 && node->children[index - 1]->keys.size() > 1) {
                // Merge with left sibling
                ref leftSibling = node->children[index - 1];
                node->children[index]->keys.insert(node->children[index]->keys.begin(),
                    node->keys[index - 1]);
                if (!node->children[index]->children.empty()) {
                    node->children[index]->children.insert(node->children[index]->children.begin(),
                        leftSibling->children.back());
                    leftSibling->children.pop_back();
                }
                node->keys[index - 1] = leftSibling->keys.back();
                leftSibling->keys.pop_back();
            }
            else if (!keyInLastChild &&
                node->children[index + 1]->keys.size() > 1) {
                // Merge with right sibling
                ref rightSibling = node->children[index + 1];
                node->children[index]->keys.push_back(node->keys[index]);
                if (!node->children[index]->children.empty()) {
                    node->children[index]->children.push_back(rightSibling->children.front());
                    rightSibling->children.erase(rightSibling->children.begin());
                }
                node->keys[index] = rightSibling->keys.front();
                rightSibling->keys.erase(rightSibling->keys.begin());
            }
            else {
                // Merge with left sibling if index is the last child
                if (keyInLastChild) {
                    ref leftSibling = node->children[index - 1];
                    leftSibling->keys.push_back(node->keys.back());
                    node->keys.pop_back();
                    if (!leftSibling->children.empty()) {
                        for (ref child : node->children.back()->children) {
                            leftSibling->children.push_back(child);
                        }
                    }
                    node->children.pop_back();
                    remove(leftSibling, key);
                }
                else {
                    // Merge with right sibling
                    ref rightSibling = node->children[index + 1];
                    node->children[index]->keys.push_back(node->keys[index]);
                    node->keys.erase(node->keys.begin() + index);
                    if (!rightSibling->children.empty()) {
                        for (ref child : rightSibling->children) {
                            node->children[index]->children.push_back(child);
                        }
                    }
                    node->children.erase(node->children.begin() + index + 1);
                    remove(node->children[index], key);
                }
            }
        }
        else {
            // Recursively remove key from child node
            remove(node->children[index], key);
        }
    }
}

TwoFourTree::ref TwoFourTree::findMinKeyNode(ref node)
{
    ref current = node;
    while (current->children.size() > 0) {
        current = current->children[0];
    }
    return current;
}


void TwoFourTree::showAsList(ref root, int level)
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

bool TwoFourTree::isKey(ref node, int key)
{
    // if node equal nullptr
    if (node == nullptr)
        return false;

    // if there is a key
    for (short i = 0, length = node->keys.size(); i < length; i++)
    {
        if (key == node->keys[i])
            return true;
    }

    // if there isn't a key
    return false;
}

TwoFourTree::ref TwoFourTree::findParent(int key)
{
    // if the tree is void
    if (root == nullptr)
        return nullptr;
    // if a key is in the root
    if (isKey(root, key))
        return nullptr;

    // find the node
    ref current = root;
    short length;
    while (current != nullptr)
    {
        length = current->keys.size();
        for (short i = 0; i < length; i++)
        {
            // check the left kids (p1, p2, p3) 
            if (key <= current->keys[i])
            {
                if (isKey(current->children[i], key))
                    return current;
                current = current->children[i];
                continue;
            }
        }
        // check the right kid (p4)
        if (isKey(current->children[current->keys.size()], key))
            return current;
        current = current->children[current->keys.size()];
    }
    return nullptr;
}

void TwoFourTree::spell(ref elem)
{
    if (elem->keys.size() < 4)
        return;

    if (elem == root)   // if an elem is the root
    {
        /*                                     _ {k2, ~, ~} _
            {k1, k2, k3, k4}   =>   {k1, ~, ~}                {k3, k4, ~}
        */
        int maxLKey = elem->keys[1];    // key2 (it would be max in left)

        ref left = new node(elem->keys[0]); // left: {key1, ~, ~}
        ref right = new node(elem->keys[2], elem->keys[3]); // right: {key3, key4, ~}
        elem->keys = { maxLKey };

        if (elem->children.size() == 0)
        {
            elem->children.push_back(left);
            elem->children.push_back(right);
        }
        else
        {
            left->children.push_back(elem->children[0]);
            left->children.push_back(elem->children[1]);
            
            right->children.push_back(elem->children[2]);
            right->children.push_back(elem->children[3]);
            right->children.push_back(elem->children[4]);

            elem->children.clear();
            elem->children.push_back(left);
            elem->children.push_back(right);
        }
    }
    else
    {
        int maxLKey = elem->keys[1];    // key2 (it would be max in left)

        ref parent = findParent(maxLKey);   // parent of this elem
        ref right = new node(elem->keys[2], elem->keys[3]); // right: {key3, key4, ~}
        elem->keys.resize(1);   // left: {key1, ~, ~}
        parent->keys.push_back(maxLKey);

        parent->children.push_back(right);
        
        if (parent->keys.size() > 3)
            spell(parent);
    }
}

void TwoFourTree::insert(int key)
{
    // if the tree is void
    if (root == nullptr)
    {
        root = new node(key);
        return;
    }

    ref current = root;
    while (current != nullptr)
    {
        // if the node is a leaf
        if (current->children.size() == 0)
        {
            current->keys.push_back(key);
            sort(current->keys.begin(), current->keys.end());
            // if node is overloaded
            if (current->keys.size() > 3)
                spell(current);
            break;
        }

        // go into a kid
        for (short i = 0, length = current->keys.size(); i < length; i++)
        {
            if (key <= current->keys[i])
            {
                current = current->children[i];
                break;
            }
            else if (i == length - 1)
                current = current->children[current->keys.size()];
        }
    }
}

void TwoFourTree::remove(int key)
{
    if (root == nullptr)
        return;

    remove(root, key);

    // Check if root is empty after removal
    if (root->keys.empty() && root->children.size() == 1) {
        ref tmp = root;
        root = root->children[0];
        delete tmp;
    }
}

TwoFourTree::ref TwoFourTree::search(int key)
{
    // if the tree is void
    if (root == nullptr)
        return nullptr;

    // find the node
    ref current = root;
    while (current != nullptr)
    {
        if (isKey(current, key))
            return current;
        
        // go into a kid
        for (short i = 0, length = current->keys.size(); i < length; i++)
        {
            if (key <= current->keys[i])
            {
                current = current->children[i];
                break;
            }
            else if (i == length - 1)
                current = current->children[current->keys.size()];
        }
    }
    return nullptr;
}

void TwoFourTree::clear()
{
    clear(root);
}

void TwoFourTree::showAsList()
{
	if (root == nullptr)
		return;

	showAsList(root);
}
