#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;


class VerifNSdata
{
    pair<size_t, size_t> range{ 2, 16 };

public:
    bool isin(char value, string list) {
        for (size_t i = 0, s = list.size(); i < s; i++)
        {
            if (value == list[i])
                return true;
        }
        return false;
    }

    bool isin(string valueList, string verfList) {
        for (size_t i = 0, s = valueList.size(); i < s; i++)
        {
            if (!isin(valueList[i], verfList))
                return false;
        }
        return true;
    }

    void setRange(pair<size_t, size_t> range) {
        if (range.first < 2) {
            invalid_argument err("ERROR: (VerifNSdata::setRange) size_t start must be > 1\n\tand not" + to_string(range.first) + "\n");
            cerr << err.what() << endl;
            throw err;
        }
        if (range.first > range.second) {
            invalid_argument err("ERROR: (VerifNSdata::setRange) size_t start must be < than size_t end\n\tand not" + to_string(range.first) + " > " + to_string(range.second) + "\n");
            cerr << err.what() << endl;
            throw err;
        }
        this->range = range;
    }

    size_t inputBase(string inputText) {
        size_t value;

        while (true)
        {
            cout << inputText;
            cin >> value;
            for (size_t i = range.first; i <= range.second; i++)
            {
                if (value == i)
                    return value;
            }
            cin.clear();
            cin.ignore(100, '\n');
            cerr << "ERROR: Incorect input. Try again !\n\t";
            cerr << "base must be from " << range.first << " to " << range.second << endl << endl;
        }
        return size_t();
    }

    string inputNumber(string inputText, size_t base) {
        string value{};
        string verfList{};

        for (int i = 0; i < base; i++)
        {
            if (i > 9)
                verfList.push_back('A' + i - 10);
            else
                verfList.append(to_string(i));
        }
        verfList.push_back('.');

        while (true)
        {
            cout << inputText;
            cin >> value;
            if (isin(value, verfList))
                return value;
            cerr << "ERROR: Incorect input. Try again !\n\t";
            cerr << "your number must consist of " << verfList << endl << endl;
        }
        return string();
    }
};


class NumSysCnvrt : private VerifNSdata
{
    bool showInfo;
    size_t froms = 0, tos = 0, floatAccuracy = 50;
    string number{}, result{}, info{};

    long long powll(long long x, int exp) {
        long long res = 1;

        if (exp == 0) return 1;
        else for (size_t i = 1, end = abs(exp); i <= end; i++)  res *= x;

        if (exp < 0) res = 1 / res;
        return res;
    }

    string toDecimal(string num, size_t base) {
        /*  INFO
        num[base] = digit * base^dr + .. = product + .. = res[10]
                    \^     piece1    ^/   \^  piece2 ^/
        */
        // init value
        bool isFloat = false;
        if (isin('.', num))
            isFloat = true;

        string wholePart = num, fractionalPart = num;
        long long wholeRes = 0;
        double fractionalRes = 0.0;

        string res{}, piece1{}, piece2{};   // info

        if (isFloat) {
            wholePart.erase(wholePart.find('.'));                   // (cut) '.' to end
            fractionalPart.erase(0, fractionalPart.find('.') + 1);  // (cut) begin to '.'
        }

        // calc whole res
        long long digit, wproduct;
        for (int i = 0, dr = (int)wholePart.size() - 1; dr >= 0; i++, dr--)
        {
            if (wholePart[i] >= 'A')
                digit = (long long)(wholePart[i] - 'A' + 10);
            else
                digit = (long long)(wholePart[i] - '0');
            wproduct = digit * powll(base, dr);
            wholeRes += wproduct;
            piece1.append(to_string(digit) + "*" + to_string(base) + "^" + to_string(dr));
            piece2.append(to_string(wproduct));
            piece1.append(" + ");
            piece2.append(" + ");
        }

        // calc fractional res
        if (isFloat) {
            double fproduct;
            for (int i = 0, dr = -1, end = -((int)fractionalPart.size()); dr >= end; i++, dr--)
            {
                if (fractionalPart[i] >= 'A')
                    digit = (long long)(fractionalPart[i] - 'A' + 10);
                else
                    digit = (long long)(fractionalPart[i] - '0');
                fproduct = (double)digit * pow(base, dr);
                fractionalRes += fproduct;
                piece1.append(to_string(digit) + "*" + to_string(base) + "^" + to_string(dr));
                piece2.append(to_string(fproduct));
                if (dr != end) {
                    piece1.append(" + ");
                    piece2.append(" + ");
                }
            }
        }

        // form the result
        res = to_string(wholeRes);
        if (isFloat) {
            string sfr = to_string(fractionalRes);
            sfr.erase(0, sfr.find('.'));
            res.append(sfr);
        }

        // form the info
        info.append(num + "[" + to_string(base) + "] = ");
        info.append(piece1 + " = " + piece2);
        info.append(" = " + res + "[10]\n");

        return res;
    }

    char getCharNum(int digit) {
        if (digit < 10)
            return '0' + digit;
        return 'A' + digit - 10;
    }

    string fromDecimal(string num, size_t base, size_t accuracy) {
        /*  INFO
        num / base = piece (remainder_1)
        piece / base = .. (remainder_2)
        . . . = .. (remainder_n)
        res = {'remainder_n' .. 'remainder_1'}
        num[10] = res[base]
        */
        // init values
        bool isFloat = false;
        if (isin('.', num))
            isFloat = true;

        long long wholePart = 0, fractionalPart = 0;
        string wholeRes, fractionalRes{};
        stack<char> remainder;  // use to whole calc
        queue<char> whole;      // use to fraction calc

        string wholeAct{}, fractionalAct{};   // info
        pair<string, string> partRes{};
        bool isInfinite = false;

        if (isFloat) {
            string part = num;
            part.erase(part.find('.'));
            wholePart = stoll(part);            // (value) begine to '.'
            part = num;
            part.erase(0, part.find('.') + 1);
            fractionalPart = stoll(part);       // (value) '.' to end
        }
        else {
            wholePart = stoll(num);
        }

        // calc whole res
        partRes.first.append(to_string(wholePart) + "[10] = ");
        int rem;
        while (wholePart != 0)
        {
            rem = wholePart % base;
            remainder.push(getCharNum(rem));

            wholeAct.append(to_string(wholePart) + " / " + to_string(base) + " = ");
            wholePart /= base;
            wholeAct.append(to_string(wholePart) + " (" + to_string(rem) + ")\n");
        }

        // calc fractional res
        if (isFloat) {
            partRes.second.append("0." + to_string(fractionalPart) + "[10] = ");
            string part{};
            char digit;
            double fractional = stod("0." + to_string(fractionalPart));
            for (size_t i = accuracy; fractionalPart != 0 && accuracy > 0; accuracy--)
            {
                fractionalAct.append(to_string(fractional) + " * " + to_string(base) + " = ");
                fractional *= base;
                fractionalAct.append(to_string(fractional));

                part = to_string(fractional);   // get whole digit form fraction
                part.erase(part.find('.'));
                digit = getCharNum(stoi(part));
                whole.push(digit);
                fractionalAct.append(" (");
                fractionalAct.push_back(digit);
                fractionalAct.append(")\n");

                part = to_string(fractional);   // get fraction without whole digit
                part.erase(0, part.find('.') + 1);
                fractional = stod("0." + part);

                fractionalPart = stoll(part);   // set new fractional part without whole digit & witout 0.
            }
            if (accuracy <= 0)
                isInfinite = true;
        }

        // form the res
        if (remainder.empty())
            wholeRes = "0";
        else {
            while (!remainder.empty())
            {
                wholeRes += remainder.top();
                remainder.pop();
            }
        }
        partRes.first.append(wholeRes + "[" + to_string(base) + "]");
        if (isFloat) {
            while (!whole.empty())
            {
                fractionalRes += whole.front();
                whole.pop();
            }
            partRes.second.append("0." + fractionalRes + (isInfinite ? "..." : "") + "[" + to_string(base) + "]");
        }

        info.append(wholeAct + partRes.first + "\n\n");
        if (isFloat)
            info.append(fractionalAct + partRes.second + "\n\n");
        string res = isFloat ? wholeRes + "." + fractionalRes : wholeRes;
        info.append(num + "[10] = " + res + (isInfinite ? "..." : "") + "[" + to_string(base) + "]\n");
        return res;
    }

public:
    NumSysCnvrt(bool showInfo = false, pair<size_t, size_t> range = { 2, 16 }) {
        this->showInfo = showInfo;
        setRange(range);
    }

    void setAccuracy(size_t accuracy) {
        if (accuracy <= 0) {
            invalid_argument err("ERROR: (NumSysCnvrt::setAccuracy) size_t accuracy must be > 0\n");
            cerr << err.what() << endl;
            throw err;
        }
        this->floatAccuracy = accuracy;
    }

    void enterData() {
        cout << ":: Number System conversions ::" << endl;
        froms = inputBase("FROM:\t");
        cout << endl;
        tos = inputBase("TO:\t");
        cout << endl;
        number = inputNumber("NUMBER:\t", froms);
    }

    void calcRes() {
        info.clear();
        if (tos == 10)
        {
            result = toDecimal(number, froms);
        }
        else if (froms == 10) {
            result = fromDecimal(number, tos, floatAccuracy);
        }
        else
        {
            result = toDecimal(number, froms);
            info.push_back('\n');
            result = fromDecimal(result, tos, floatAccuracy);
        }
    }

    void outputRes() {
        cout << "RESULT: " << result << endl;
        if (showInfo) {
            cout << ": INFO :" << endl;
            cout << info << endl;
        }
    }
};


int main() {
    NumSysCnvrt nsc(true);

    while (true)
    {
        nsc.enterData();
        cout << endl;

        nsc.calcRes();

        nsc.outputRes();
    }

    system("PAUSE");
    return 0;
}
