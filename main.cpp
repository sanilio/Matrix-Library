/**

This is a testing routine and
illustrates how this matrix
library can be used.

**/

#include "Matrix.h"

using namespace std;

bool isSquare(Matrix);
Matrix makeIdentity(int);

int main ()
{
//    Matrix a("matrix5x4.data");
//
//    Matrix b("matrix5x4.data");
//
//    Matrix d("matrix5x4.data");
//
//    Matrix e("matrix5x4.data");
//
//    Matrix f("matrix5x4.data");
//
//    Matrix g("matrix5x4.data");
//
//    Matrix c;
//    Matrix z;
//    Matrix y;
//    Matrix x;
//
//    c = a + b;
//
//    x = d + e;
//
//    z = x + g;
//
//    y = z + x;
//
//    cout << c;
//    cout << x;
//    cout << z;
//    cout << y;
//
//    Matrix i;
//
//    cout << "Enter info for matrix i: " << endl;
//
//    cin >> i;
//
//    cout << "Printing matrix i: " << endl << i;
//
//    Matrix it;
//    it = !i;
//
//    cout << "Priting i transpose: " << endl;
//
//    cout << it;

    Matrix a(4,5), b("matrix5x4.data"), c, d, e;

    a.access(0,0) = 1;
    a.access(0,1) = 2;
    a.access(0,2) = 3;
    a.access(0,3) = 4;
    a.access(0,4) = 5;
    a.access(1,0) = 1.125;
    a.access(1,1) = 2.125;
    a.access(1,2) = 3.125;
    a.access(1,3) = 4.125;
    a.access(1,4) = 5.125;
    a.access(2,0) = 0;
    a.access(2,1) = 0;
    a.access(2,2) = 0;
    a.access(2,3) = 0;
    a.access(2,4) = 0;
    a.access(3,0) = a.access(0,0) ;
    a.access(3,1) = a.access(0,1) + a.access(1,1);
    a.access(3,2) = a.access(0,2) + 5;
    a.access(3,3) = 8 * a.access(0,3) ;
    a.access(3,4) = -a.access(0,4) ;

    // scalar multiplication
    e = a * 5;
    d = 4.25 * a;
    c = a * -3.14;
    cout << e << d << c << b;

    cout << "b: " << b;
    cout << "a: " << a;

    cout << endl << "Enter info for a matrix:"  << endl;
    cin >> b;

    cout << "b: " << b;

    // matrix multiplcation
    c = a * b;
    d = b * a;
    cout << c << d;

    cout << "a after *: " << a;
    cout << "b after *: " << a;

    // check function calls
    if (isSquare(a))
    cout << "Matrix a is a square matrix of size " << a.getRowCount() << endl;
    else
    cout << "Matrix a is not a square matrix" << endl;
    if (isSquare(c))
    cout << "Matrix c is a square matrix of size " << c.getRowCount() << endl;
    else
    cout << "Matrix c is not a square matrix" << endl;

    cout << "a after isSquare: " << a;
    cout << "c after isSquare: " << c;
    // transpose
    e = !a;
    cout << a << e;

    // matrix addition
    c = b + e;
    d = e + b;
    cout << c << d;

    // check function calls
    c = makeIdentity(4);
    if (isSquare(c))
    cout << "Matrix c is a square matrix of size " << c.getRowCount() << endl;
    else
    cout << "Matrix c is not a square matrix" << endl;
    cout << c;

    cout << endl << "Goodbye" << endl;

}

bool isSquare(Matrix m)
{
    return (m.getRowCount() == m.getColCount());
}

Matrix makeIdentity (int size)
{
    int i;
    Matrix retVal(size, size);

    for (i = 0; i < size; i++)
    retVal.access(i, i) = 1;

    return retVal;
}
