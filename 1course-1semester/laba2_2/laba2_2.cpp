#include <iostream>
#include <cmath>
using namespace std;

inline double function(double x);

int main() {
	double z, x;

	// get data
	cout << "Please, enter number.\n";
	cout << "z: ";
	cin >> z;

	// show got data
	cout << "\nI got such number:\n";
	cout << "z = " << z << "\n\n";

	// calc x
	if (z < 0) {
		x = pow(z, 2.) - z;
	}
	else {
		x = pow(z, 3.);
	}

	// output result
	cout << "x = " << x << endl;
	cout << "Y = " << function(x) << endl;

	system("PAUSE");
	return 0;
}


inline double function(double x) {
	/* Calc this funcion and return its result:
	y = sin^3(x + x^2 + x^3)
	*/
	return pow(sin(x + pow(x, 2.) + pow(x, 3.)), 3.);
}