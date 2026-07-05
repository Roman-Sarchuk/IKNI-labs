// laba4 , task2 , variant7
/*	What can you do? [ FOR USERS ]
    - change N (// Array size)
    - change MAXRAND and MINRAND (// Random range)
    - start program
*/
/*  What does program do?
    It create square matrix and fill by rand number.
    Calc sum of matrix elements above main diagonal.
    Input Matrix in file 1 and sum in file 2.
    Output data from that files in console.
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;

// Matrix size
#define N 3
// Random range
int MAXRAND = 50;
int MINRAND = -20;

void fillMrx(int mrx[N][N], int max, int min);
bool inputMrx(int mrx[N][N], const char* filename);
bool outputTxtFile(const char* filename);
int calcSum(int mrx[N][N], const char* filename);


int main()
{
    srand(time(NULL));
    int mrx[N][N], sum = 0;

    fillMrx(mrx, MAXRAND, MINRAND);
    inputMrx(mrx, "F1.txt");

    cout << ":: Our squar matrix ::" << endl;
    outputTxtFile("F1.txt");
    cout << endl;

    calcSum(mrx, "F2.txt");

    outputTxtFile("F2.txt");
    cout << endl << endl;

    system("PAUSE");
    return 0;
}


void fillMrx(int mrx[N][N], int max, int min) {
    /* fill elements of square matrix by rand numbers from max to min */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mrx[i][j] = rand() % (max + 1 - min) + min;
        }
    }
}

bool inputMrx(int mrx[N][N], const char* filename) {
    /* Input matrix in text file by a bitwise left shift operator (<<) */
    ofstream file(filename);

    // Checking if file was opened
    if (!file) {
        cerr << "ERROR: file '" << filename << "' wasn't opened !\n" << endl;
        return false;
    }

    // Input data in file
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << setw(5) << mrx[i][j] << "\t";
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool outputTxtFile(const char* filename) {
    /* Output matrix from text file by character-by-character reading */
    ifstream file(filename);

    // Checking if file was opened
    if (!file) {
        cerr << "ERROR: file '" << filename << "' wasn't opened !\n" << endl;
        return false;
    }

    // Output data from file
    char sym;
    while (file)
    {
        file.get(sym);
        if (file)
            cout << sym;
    }

    file.close();
    return true;
}

int calcSum(int mrx[N][N], const char* filename) {
    /* Calculate sum of matrix elements above main diagonals
        and input it in tex file*/
    ofstream file(filename);

    // Checking if file was opened
    if (!file) {
        cerr << "ERROR: file '" << filename << "' wasn't opened !\n" << endl;
        return false;
    }

    // Calc sum
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            sum += mrx[i][j];
        }
    }

    // Input data
    file << "sum of elements above main diagonal :: " << sum;

    return sum;
}
