#include "sortFunction.h"

// 5
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> left_half(n1);
    vector<int> right_half(n2);

    // Copy data to temporary arrays left_half[] and right_half[]
    for (int i = 0; i < n1; ++i)
        left_half[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        right_half[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            ++i;
        }
        else {
            arr[k] = right_half[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of left_half[], if there are any
    while (i < n1) {
        arr[k] = left_half[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of right_half[], if there are any
    while (j < n2) {
        arr[k] = right_half[j];
        ++j;
        ++k;
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr)
{
    merge_sort(arr, 0, arr.size() - 1);
}

//9
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void gnomeSort(vector<int>& arr) {
    int n = arr.size();
    int index = 0;

    while (index < n) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}

// 13
// Utility function to create a new tree node
TreeNode* newNode(int value) {
    TreeNode* node = new TreeNode();
    node->data = value;
    node->left = node->right = nullptr;
    return node;
}

// Utility function to insert a new node with a given key in BST
TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) return newNode(key);

    if (key <= root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

// Utility function to perform in-order traversal of BST
void inOrder(TreeNode* root, vector<int>& sorted) {
    if (root != nullptr) {
        inOrder(root->left, sorted);
        sorted.push_back(root->data);
        inOrder(root->right, sorted);
    }
}

// Function to perform tree sort
void treeSort(vector<int>& arr) {
    TreeNode* root = nullptr;

    // Construct the BST
    for (int i = 0; i < arr.size(); ++i)
        root = insert(root, arr[i]);

    // Perform in-order traversal to get sorted array
    arr.clear(); // Clearing the original vector
    inOrder(root, arr);
}

// 17 
// To get the Leonardo numbers
int leonardo(int k)
{
    if (k < 2) {
        return 1;
    }
    return leonardo(k - 1) + leonardo(k - 2) + 1;
}

// Build the Leonardo heap by merging
// pairs of adjacent trees
void heapify(vector<int>& arr, int start, int end)
{
    int i = start;
    int j = 0;
    int k = 0;

    while (k < end - start + 1) {
        if (k & 0xAAAAAAAA) {
            j = j + i;
            i = i >> 1;
        }
        else {
            i = i + j;
            j = j >> 1;
        }

        k = k + 1;
    }

    while (i > 0) {
        j = j >> 1;
        k = i + j;
        while (k < end) {
            if (arr[k] > arr[k - i]) {
                break;
            }
            swap(arr[k], arr[k - i]);
            k = k + i;
        }

        i = j;
    }
}

// Smooth Sort function
void smoothSort(vector<int>& arr)
{
    int n = arr.size();

    int p = n - 1;
    int q = p;
    int r = 0;

    // Build the Leonardo heap by merging
    // pairs of adjacent trees
    while (p > 0) {
        if ((r & 0x03) == 0) {
            heapify(arr, r, q);
        }

        if (leonardo(r) == p) {
            r = r + 1;
        }
        else {
            r = r - 1;
            q = q - leonardo(r);
            heapify(arr, r, q);
            q = r - 1;
            r = r + 1;
        }

        swap(arr[0], arr[p]);
        p = p - 1;
    }

    // Convert the Leonardo heap
    // back into an array
    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j = j - 1;
        }
    }
}
