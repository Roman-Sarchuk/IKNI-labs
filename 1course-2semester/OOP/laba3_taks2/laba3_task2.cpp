#include "TextFileHandler.h"

int main()
{
    FileTextHandler handler;
    try
    {
        handler.setText("computers.txt");

        cout << "+:+:+:+:+:+ Origin Text +:+:+:+:+:+" << endl;
        cout << handler.getText();

        cout << "\n-------------------\n";
        cout << "Text processing...\n";
        cout << "-------------------\n" << endl;
        handler.saveDataToFile("result.txt");

        cout << "+:+:+:+:+:+ Processed Text +:+:+:+:+:+" << endl;
        cout << handler.getText() << endl;
        cout << "=== INFO ===\n";
        handler.calcPairWordLength();
        cout << "Number of pair word lenghts: " << handler.getNumOfPairWordLength() << '\n';
        cout << "Bracket is coorected: " << (handler.verifyBrackets() ? "true" : "false") << '\n';
        handler.calcLetter();
        cout << "~ Letter ~\n";
        vector<char> letter = handler.getLetterList();
        vector<size_t> count = handler.getCountOfLetetr();
        for (size_t i = 0, length = letter.size(); i < length; i++)
        {
            cout << letter[i] << ": " << count[i] << '\n';
        }
        cout << '\n';
    }
    catch (invalid_argument& exp)
    {
        cerr << exp.what() << endl;
    }

    system("PAUSE");
    return 0;
}
