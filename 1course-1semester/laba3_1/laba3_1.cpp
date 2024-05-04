#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

#define N 15
double segment[2] = { 0.0, M_PI };

double function(double x);
double integral(double* seg);

int main() {
	cout << "|----------------------------------|" << endl;
	cout << "| number | value of x | function y |" << endl;
	cout << "|----------------------------------|" << endl;
	unsigned int counter = 1;
	double step = segment[1] / (N);
	for (float x = segment[0]; counter <= N; x += step, counter++)
		cout << "| " << counter << "\t | " << x << "\t" << function(x) << "\t" << endl;
	cout << "|----------------------------------|" << endl;
	cout << "|integral (0 - pi): " << integral(segment) << "\t\t" << endl;
	cout << "|----------------------------------|\n" << endl;

	system("PAUSE");

	return 0;
}


double function(double x) {
	/* Calculate the function in point x
			1         2x-1
		y = - * atan( ---- + п)
			п           2
	*/
	return (1.0 / M_PI) * atan((2 * x - 1) / 2.0 + M_PI);
}

double antiderivative(double x) {
	/* Calculate the antiderivative of function in point x
					 2x-1              2x-1                 2x-1            5+4x^2-4x
			2x*atan( ---- + п) - atan( ---- + п) + 2п*atan( ---- + п) - ln( --------- + 2пx - п + п^2 )
					   2                 2                    2                 4
		Y = -------------------------------------------------------------------------------------------
												 2п
	*/
	double part1, part2;
	part1 = atan((2 * x - 1) / 2.0 + M_PI);
	part2 = log((5 + 4 * pow(x, 2) - 4 * x) / 4.0 + 2 * M_PI * x - M_PI + pow(M_PI, 2));
	return (2 * x * part1 - part1 + 2 * M_PI * part1 - part2) / 2 * M_PI;
}

double integral(double* seg) {
	// Calculation of the definite integral
	return antiderivative(seg[1]) - antiderivative(seg[0]);
}