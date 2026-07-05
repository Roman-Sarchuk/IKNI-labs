#pragma once
#include <vector>
using std::vector;

// 5
void merge(vector<int>& arr, int left, int mid, int right);
void merge_sort(vector<int>& arr, int left, int right);
void mergeSort(vector<int>& arr);

// 9
void swap(int& a, int& b);
void gnomeSort(vector<int>& arr);

// 13
// Structure for a tree node
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};
TreeNode* newNode(int value);
TreeNode* insert(TreeNode* root, int key);
void inOrder(TreeNode* root, vector<int>& sorted);
void treeSort(vector<int>& arr);

// 17
int leonardo(int k);
void heapify(vector<int>& arr, int start, int end);
void smoothSort(vector<int>& arr);
