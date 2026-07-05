#include "Vector.h"
using geometry::Vector3;

int main()
{
    // Create a vector A and C
    Vector3 a(2, -5, 3);
    Vector3 c(4, 9, 0);
    cout << "A = " << a.info() << endl;
    cout << "C = " << c.info() << endl;
    cout << endl;

    // operator =
    Vector3 b;
    b = a;
    cout << "B = A = " << b.info() << endl;
    cout << endl;

    // operators == and !=
    cout << "B == A ? -> " << (b == a ? "true" : "false") << endl;
    cout << "C != A ? -> " << (c != a ? "true" : "false") << endl;
    cout << endl;

    // operator *
    Vector3 d;
    d = a * 10;
    cout << "D = A * 10 = " << d.info() << endl;
    cout << endl;

    // operator -
    Vector3 e = c - a;
    cout << "E = C - A = " << e.info();
    cout << endl;

    system("PAUSE");
    return 0;
}
