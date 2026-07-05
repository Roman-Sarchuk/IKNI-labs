// laba6, task2, variant7
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void inputWords(vector<string>& wordlist);
void outputWords(vector<string> wordlist);
void sortWords(vector<string>& wordlist);


int main()
{
    vector<string> wordlist;

    cout << "Enter string to sorting:" << endl;
    inputWords(wordlist);
    cout << "\nFine! Sorting...\n" << endl;

    cout << ":BEFORE:" << endl;
    outputWords(wordlist);
    cout << ":AFTER:" << endl;
    sortWords(wordlist);
    outputWords(wordlist);

    system("PAUSE");
    return 0;
}


void inputWords(vector<string>& wordlist)
{
    /*  Get chars of string from console.
        Split string by space and add this words in vector. */
    string str;
    size_t i = 0;
    char ch;

    do
    {
        ch = getchar();
        if (ch == ' ') {
            wordlist.push_back(str);
            str = "";
            i++;
        }
        else if (ch == '\n') {
            wordlist.push_back(str);
            i++;
            break;
        }
        else
            str += ch;
    } while (true);
}

void outputWords(vector<string> wordlist)
{
    /* Output words from vector in square brackets */
    for (size_t i = 0; i < wordlist.size(); i++)
    {
        cout << '[' << wordlist[i] << ']';
    }
    cout << endl;
}

void sortWords(vector<string>& wordlist)
{
    /*  Sort words in vector by length.
        From less to more */
        // there is lambda expressions
    sort(wordlist.begin(), wordlist.end(), [](const string lhs, const string rhs)->bool {return lhs.length() < rhs.length(); });
}
