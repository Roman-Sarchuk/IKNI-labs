// laba5 , task1 , variant7
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#define N 100
const string symbolslist = "`~!?@#№$%^&*()[]{}'\"_+-=\\/|*,.;:";
void inputArr(char s[N]);
void outputArr(char s[N]);
void getSymbol(char s[N], char symbarr[N]);
void insertSymbol(char s[N], char symbarr[N]);


int main()
{
    char s1[N], s2[N], symbarr[N];

    inputArr(s1);
    cout << endl;
    inputArr(s2);

    cout << "\n\n:Your char arrays:" << endl;
    outputArr(s1);
    outputArr(s2);

    cout << "\nInserting symbols in first array..." << endl;
    getSymbol(s2, symbarr);
    outputArr(symbarr);
    insertSymbol(s1, symbarr);

    cout << "\n:Your char arrays:" << endl;
    outputArr(s1);
    outputArr(s2);
    cout << endl;

    system("PAUSE");
    return 0;
}


void inputArr(char s[N])
{
    /* input from stream in array until '\n' char or until i != N
    s -> array in which you need to enter data*/
    cout << ":Enter some characters:" << endl;
    char ch = ' ';

    size_t i = 0;
    while (ch != '\n' && i < N)
    {
        ch = getchar();
        s[i] = ch;
        i++;
    }

    if (ch != '\n')
        cin.ignore(32000, '\n');
    s[i - 1] = '\0';
}


void outputArr(char s[N])
{
    /* Output chars of array until '\0' char
    s -> array which you need to output*/
    cout << "{ ";
    size_t i = 0;
    while (s[i] != '\0')
    {
        cout << '\'' << s[i] << "' ";
        i++;
    }
    cout << "}" << endl;
}


bool checkingChar(char ch)
{
    /* Check if char ch is symbol that contains in list
    if ch is symbol return true else if it is letter or number return 0
    ch -> char which you need to check */
    for (size_t i = 0; symbolslist[i] != '\0'; i++)
    {
        if (ch == symbolslist[i])
            return true;
    }
    return false;
}

void getSymbol(char s[N], char symbarr[N])
{
    /* Find symbols in first array and input them in second
    s -> array from which you need to get synbols
    synbarr -> array in which you need to save got symbols*/
    size_t j = 0;
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (checkingChar(s[i]))
        {
            symbarr[j] = s[i];
            j++;
        }
    }
    symbarr[j] = '\0';
}


int charCounter(char s[N])
{
    /* Calc amount of elements in array and return it as int value
    s -> array in which you need to calc amount of elements*/
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

void insertSymbol(char s[N], char symbarr[N])
{
    /* Insert symbols in center of array
    s -> array in which you need to insert symbols
    symbarr -> array which contain inserting symbols*/
    char temp[N];
    copy(s, s + N, temp);

    size_t start = charCounter(s) / 2, symbcount = charCounter(symbarr);
    for (size_t i = start, j = 0, k = start; i < N; i++)
    {
        if (j < symbcount) {
            s[i] = ' ';
            i++;
            if (i >= N)
                break;
            s[i] = symbarr[j];
            j++;
            if (j == symbcount) {
                i++;
                if (i >= N)
                    break;
                s[i] = ' ';
            }
        }
        else {
            s[i] = temp[k];
            k++;
        }
    }
    s[N - 1] = '\0';
}
