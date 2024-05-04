#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


short int getStep();
double integral(short int range[2], short int step);
void outputRes(short int range[2], short int step, double integ);


int main()
{
    short int step;
    short int range[2]{ 2,3 };

    step = getStep();
    outputRes(range, step, integral(range, step));

    system("PAUSE");
    return 0;
}


short int getStep()
{
    /* Return gotten int value that is > 0 */
    short int value;
    bool iscorrectinput;

    do
    {
        cout << "Enter step (int value): ";
        cin >> value;
        iscorrectinput = cin.fail();
        cin.clear();
        cin.ignore(100, '\n');

        if (iscorrectinput)
            cerr << "ERROR: Incorect input, try again !\n\tStep must be entered as a number\n" << endl;
        else if (value <= 0)
            cerr << "ERROR: step must be > 0\n" << endl;
        else
            break;
    } while (true);

    return value;
}

inline double function(double x)
{
    /* Return f(x) = 7x^3 - x^2 + 3x + 2 */
    return 7 * pow(x, 3) - pow(x, 2) + 3 * x + 2;
}

double integral(short int range[2], short int step)
{
    /* Calc integral of f(x) = 7x^3 - x^2 + 3x + 2 by the method of rectangles */
    double h = (double)(range[1] - range[0]) / (double)step;
    double sum = (function(range[0]) + function(range[1])) / 2;

    for (size_t i = 1; i <= step - 1; i++)
    {
        sum += function(range[0] + i * h);
    }

    return h * sum;
}

void outputTableLine(size_t dashnum) {
    /*  Output table row as |----|
        dashnum - number of dashes */
    cout << '|';
    for (size_t i = 0; i < dashnum; i++)
    {
        cout << '-';
    }
    cout << '|' << endl;
}
void outputTableValue(vector<string> value, size_t maxl) {
    /*  Output field of table row as | value   |
        value -> list of values that fieldes of table row contain
        maxl -> fielde size */
    cout << "| ";
    for (size_t i = 0; i < value.size(); i++)
    {
        cout << setw(maxl) << left << value[i] << " | ";
    }
    cout << endl;
}

void outputRes(short int range[2], short int step, double integ)
{
    /* Output tabel of result (2x3) */
    string srange = to_string(range[0]) + " to " + to_string(range[1]);
    string sstep = to_string(step);
    string sinteg = to_string(integ);
    size_t maxl = max({ srange.length(),sstep.length(),sinteg.length() });
    vector<string> topic = { "range","step","integral" };

    outputTableLine(maxl * 3 + 8);
    outputTableValue(topic, maxl);
    outputTableLine(maxl * 3 + 8);
    outputTableValue({ srange,sstep,sinteg }, maxl);
    outputTableLine(maxl * 3 + 8);
}
