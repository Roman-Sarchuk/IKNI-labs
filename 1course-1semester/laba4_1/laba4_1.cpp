// laba4 , task1 , variant7
/*	What can you do? [ FOR USERS ]
	- change N (// Array size)
	- change MAXRAND and MINRAND (// Random range)
	- start program
*/
/*	What does program do?
	It create array and fill by rand number.
	Calc count of number in array.
	Output result in console.
*/
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

// Array size
#define N 10
// Random range
const short MAXRAND = 5;
const short MINRAND = 0;

void fillArr(int* arr, const int size, int max, int min);
void showArr(int* arr, const int size);
void calcDubl(int* arr, int* cheklist, const int size);

int main()
{
	// Check the corectness max and min rand number
	if (MAXRAND < MINRAND) {
		cerr << "ERROR: rand number can't be generate.\n\tMAXRAND < MINRAND !" << endl;
		return 1;
	}

	srand(time(NULL));
	const int size = N;
	int arr[size], checklist[size];

	fillArr(arr, size, MAXRAND, MINRAND);
	cout << ":: Our array of numbers ::" << endl;
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]));
	showArr(arr, size);
	cout << "\n:: Count of numbers ::" << endl;
	calcDubl(arr, checklist, size);

	system("PAUSE");
	return 0;
}


void fillArr(int* arr, const int size, int max, int min) {
	/* fill elements of array by rand numbers from max to min */
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (max + 1 - min) + min;
	}
}

void showArr(int* arr, const int size) {
	/* Output array in stream */
	cout << "[ ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
		if (i != size - 1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

bool checkNum(int num, int* cheklist, const int size) {
	/* check if num is in cheklist array */
	for (int i = 0; i < size; i++)
	{
		if (num == cheklist[i])
			return 1;
	}
	return 0;
}

void calcDubl(int* arr, int* cheklist, const int size) {
	/* Output list of number and their count in arr */
	int counter;
	for (int i = 0; i < size; i++)
	{
		if (!checkNum(arr[i], cheklist, size)) {
			cheklist[i] = arr[i];
			counter = 0;
			cout << arr[i] << " -> ";
			// calc dublicate
			for (int j = i; j < size; j++)
			{
				if (arr[i] == arr[j])
					counter++;
			}
			cout << counter << endl;
		}
	}
}