#include "sortFunction.h"
#include <iostream>
using std::cout;
using std::endl;

void printArr(const vector<int>& arr);
void printArr(const vector<int>& arr, const char* info);

int main()
{
    // Init the testing arrays
    vector<int> arr1, arr2, arr3, arr4;
    arr1 = { 1, 2, 8, 5, 6, 7, 9 };
    arr2 = { 9, 8, 7, 6, 5, 3, 4 };
    arr3 = { 1, 2, 6, 4, 7, 4, 3 };
    arr4 = { 5, 3, 9, 7, 1, 4, 2 };

    // Show arrays
    cout << "~-~-~ given arrays ~-~-~" << endl;
    printArr(arr1);
    printArr(arr2);
    printArr(arr3);
    printArr(arr4);
    cout << "~-~-~ ~-~-~ ~-~-~- ~-~-~" << endl;

    // Sort arrays
    mergeSort(arr1);    // 5
    gnomeSort(arr2);    // 9
    treeSort(arr3);     // 13
    smoothSort(arr4);   // 17

    // Show sorted arrays
    cout << "~-~-~ sorted arrays ~-~-~" << endl;
    printArr(arr1, "merge sort");
    printArr(arr2, "gnome sort");
    printArr(arr3, "tree sort");
    printArr(arr4, "smooth sort");
    cout << "~-~-~ ~-~-~- ~-~-~- ~-~-~" << endl;

    system("PAUSE");
    return 0;
}


void printArr(const vector<int>& arr)
{
    cout << "{  ";
    for (int elem : arr)
    {
        cout << elem << "  ";
    }
    cout << "}" << endl;
}

void printArr(const vector<int>& arr, const char* info)
{
    cout << "{  ";
    for (int elem : arr)
    {
        cout << elem << "  ";
    }
    cout << "}" << "\t(" << info << ")" << endl;
}