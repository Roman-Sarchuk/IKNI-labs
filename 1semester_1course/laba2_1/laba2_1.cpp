#include <iostream>
#include <cmath>
using namespace std;


double function(double x, double y, double z);


int main() {
	double x, y, z; // x = 0.1722, y = 6.33, z = 0.000325

	// get data
	cout << "Please, enter several numbers.\n";
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "z: ";
	cin >> z;

	// show got data
	cout << "\nOK, I got such numbers:\n";
	cout << "x = " << x << "\ny = " << y << "\nz = " << z << "\n\n";

	// verify data
	if (fabs(x) > 1) {
		cout << "ERROR: |x| must be <= 1\n";
		cout << "\tPlease, correct your number!\n";
		return 1;
	}
	else if (fabs(x - y) * z + pow(x, 2.) == 0) {
		cout << "ERROR: |x-y|z+x^2 can't be zero\n";
		cout << "\tPlease, correct your numbers!\n";
		return 1;
	}

	// output result
	cout << "RES = " << function(x, y, z) << endl;

	system("PAUSE");

	return 0;
}


double function(double x, double y, double z) {
	/* Calc this funcion and return its result:
						1                x+3|x-y|+x^2
	f = 5 * arctg(x) - --- * arccos(x) * ------------
						4                 |x-y|z+x^2
	*/
	double part1, part2, part3, part4;

	part1 = 5. * atan(x);
	part2 = (1. / 4.) * acos(x);
	part3 = x + 3. * fabs(x - y) + pow(x, 2.);
	part4 = fabs(x - y) * z + pow(x, 2.);

	return part1 - part2 * (part3 / part4);
}