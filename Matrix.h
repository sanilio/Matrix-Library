/**

This is a matrix library that supports the
creation of matricies with given parameters
or from a formatted text file.

The standard operators are overloaded to work
with matrix arithmetic. Currently supported
functions include addition, scalar multiplication
of both ways (e.g. 5*A, A*5), matrix multiplication,
transposition, and checking for equality and
inequality.

Future plans currently include optimizing matrix
multiplication with Strassen's algorithm, supporting
determinants, and ultimately to extend this class
to a linear algebra toolkit.

NOTE: This implementation takes advantage of
      optimizations found in C++11/C++0x,
      particularlly move construction, so
      compile accordingly.

Author: Sanil Sampat
Date  : 2 / 2 / 12 (last update)

**/

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
using namespace std;

class Matrix
{

    // declare << and >> as friend functions
    // since the streams don't belong to me
    // and reference private data
    friend ostream & operator<<(ostream& output, Matrix& m);
    friend istream & operator>>(istream& input , Matrix& m);

    public:

        // constructors
        Matrix();                     // default
        Matrix(const Matrix& other);  // copy constructor
        Matrix(Matrix&& that      );  // move constructor, compile as C++11/C++0x
        Matrix(char* fileName     );  // given text file
        Matrix(int rows, int cols );  // given row/col

        // destructor
        ~Matrix();

        // accessors, const since value does not change
        int getRowCount() const { return m_rows; }
        int getColCount() const { return m_cols; }

        // mutators
        void setRowCount(int rows) { m_rows = rows; }
        void setColCount(int cols) { m_cols = cols; }



        // retrieve the value at matrix[row][col]
        // const function since it does not change values
        float& access(int row, int col) const;

        // used in memory management to avoid expensive copying
        friend void swap(Matrix& first, Matrix& second);

        // assignment operator must be a member function
        Matrix& operator=(Matrix m);

    protected:

    private:

        int m_rows;
        int m_cols;

        /**

         a pointer-to-pointer-to-float
         represents the 2d float array
         as the matrix data structure.

         theMatrix first points to an array
         of float pointers (the rows), and those
         pointers point to an array of floats

        **/

        float** theMatrix;
};

// remaining operators defined as free functions.
// we dont want to modify the implicit object,
// e.g. 'a' should not change in c = a+b

Matrix operator+  (const Matrix &lhs, const Matrix &rhs);
Matrix operator*  (const float  &lhs, const Matrix &rhs);
Matrix operator*  (const Matrix &rhs, const float  &lhs);
Matrix operator*  (const Matrix &lhs, const Matrix &rhs);

bool   operator== (const Matrix &lhs, const Matrix &rhs);
bool   operator!= (const Matrix &lhs, const Matrix &rhs);
Matrix operator!  (const Matrix &m                     );

#endif // MATRIX_H
