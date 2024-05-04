// laba5 , task1 , variant7
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string pib, word;
    vector<string> spellpib;

    // Ccollect data
    cout << "Enter your PIB:" << endl;
    getline(cin, pib);
    pib += ' '; // necessary for spelling

    // Spell pib by spaces & ignore multiple spaces
    char c = pib[0];
    for (size_t i = 1; c != '\0'; c = pib[i], i++) {
        if (c != ' ')
            word += c;
        else if (word != "") {
            spellpib.push_back(word);
            word = "";
        }
    }

    // Find the longest word
    string longest = spellpib[0];
    for (size_t i = 1, maxid = 0; i < spellpib.size(); i++)
    {
        if (spellpib[maxid].size() < spellpib[i].size()) {
            longest = spellpib[i];
            maxid = i;
        }
        else if (spellpib[maxid].size() == spellpib[i].size()) {
            longest = longest + " " + spellpib[i];
        }
    }

    // Output result
    cout << "\n:The longest word:\n" << longest << endl;


    // *** FOR CHEKING ***
    cout << "\n// *** FOR CHEKING ***" << endl;

    cout << "pib contains: ";
    cout << '[' << pib << ']' << endl;
    cout << "vector spellpib size: " << '{' << spellpib.size() << '}' << endl;
    for (size_t i = 0; i < spellpib.size(); i++)
    {
        cout << '[' << spellpib[i] << ']' << endl;
    }

    cout << "// *** *** ******* ***\n" << endl;
    // *** *** ******* ***

    system("PAUSE");
    return 0;
}
