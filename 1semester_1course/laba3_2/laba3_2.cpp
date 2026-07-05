#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

void get_x(double* x);
void get_e(double* e);
double calc_y(double x);
double calc_s(double x, double e);


int main() {
	double x = 0., e;

	// Get data
	cout << ":Enter data:" << endl;
	get_x(&x);
	get_e(&e);
	cout << endl;

	// Show data
	cout << ":You entered:" << endl;
	cout << "x = " << x << endl;
	cout << "e = " << e << endl << endl;

	double y = calc_y(x), s = calc_s(x, e);
	// Output Result
	cout << "|============================|" << endl;
	cout << "| func Y(x)  | " << y << endl;
	cout << "|----------------------------|" << endl;
	cout << "| range S(x) | " << s << endl;
	cout << "|----------------------------|" << endl;
	cout << "| S(x)-Y(x)  | " << fabs(s - y) << endl;
	cout << "|============================|" << endl;

	system("PAUSE");
	return 0;
}


double calc_y(double x) {
	/* Calculation of function:
			  1                      п
	Y(x) = - --- * ln( 1 - 2x * cos(---) + x^2 )
			  2                      3
	*/
	return (-(1. / 2.) * log(1 - 2 * x * cos(M_PI / 3) + pow(x, 2.)));
}

double calc_s(double x, double e) {
	/* Calculation of the approximate value S(x):
			oo  x^k * cos(k*п / 3)
	S(x) = SUM --------------------
		   k=1        k
	*/
	double s = 0., piece = 0.;
	for (int k = 1; piece <= e; k++)
	{
		piece = (pow(x, k) * cos(k * M_PI / 3)) / k;
		s += piece;
	}
	return s;
}

void get_x(double* x) {
	while (true)
	{
		cout << "x: ";
		cin >> *x;
		if (*x < 1 || *x > 0)
			break;
		cout << "x must be > 0 and < 1. Try again!" << endl;
	}
}

void get_e(double* e) {
	do
	{
		cout << "e: ";
		cin >> *e;
		if (*e < 0.0001 || *e > 0)
			break;
		cout << "e must be > 0 and < 0.0001. Try again!" << endl;
	} while (true);
}