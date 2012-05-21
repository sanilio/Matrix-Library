/**

This is the implementation of the
functions defined in the header
file.

**/

#include "Matrix.h"

// default constructor, set rows/cols to 0
Matrix::Matrix()
{
    setRowCount(0);
    setColCount(0);
    theMatrix = 0;
}

// create matrix with given rows/col
Matrix::Matrix(int rows, int cols)
{
    if((rows < 0) | (cols < 0)) {
        cout << "Dimensions must be greater or equal to 0." << endl;
    }

    // set rows and columns
    setRowCount(rows);
    setColCount(cols);

    // allocate memory to rows of the matrix
    // by creating an array of float pointers
    // with size of rows
    theMatrix = new float* [getRowCount()];

    // allocate memory to cols of the matrix
    // by setting each row pointer to another
    // array of floats with size of cols

    for(int i=0; i<getRowCount(); i++) {
        theMatrix[i] = new float [getColCount()];
    }

    // zero each element of the matrix
    for(int i=0; i<getRowCount(); i++) {
        for(int j=0; j<getColCount(); j++) {
            theMatrix[i][j] = 0;
        }
    }

}

// copy constructor
Matrix::Matrix(const Matrix& other)
{
    // set the dimensions
    setRowCount(other.getRowCount());
    setColCount(other.getColCount());

    // allocate the memory
    theMatrix = new float* [other.getRowCount()];
        for(int i=0; i<other.getRowCount(); i++) {
            theMatrix[i] = new float [other.getColCount()];
        }

        // assign each value
        for(int i=0; i<other.getRowCount(); i++) {
            for(int j=0; j<other.getColCount(); j++) {
                this->access(i, j) = other.access(i, j);
            }
        }
}

// move constructor, efficient in expressions
// like a = x + y;
Matrix::Matrix(Matrix&& that)
{
    // set "this" matrix's data to "that" matrix's data
    m_rows = that.m_rows;
    m_cols = that.m_cols;
    theMatrix = that.theMatrix;

    // delete data in "that" matrix
    that.setRowCount(0);
    that.setColCount(0);
    that.theMatrix = 0;
}

// create matrix from a file
// NOTE: the file must not have blank lines at the end
Matrix::Matrix(char* fileName)
{
    // declare and open the file
    ifstream theFile;
    theFile.open(fileName);

    // if the file is there..
    if(theFile != NULL) {

        // till the end of the file..
        while( !theFile.eof() ) {

            // place file info into calling matrix object
            // using the >> operator we defined

            theFile >> *this;
        }
        // close file
        theFile.close();
    }
    else {
        cout << "Unable to open: " << fileName << endl;
    }
}

Matrix::~Matrix()
{
    // destroy each col in each row
    for(int i=0; i<getRowCount(); ++i) {
        delete [] theMatrix[i];
    }

    // destroy the rows
    delete [] theMatrix;
}

// used in operator= overloading,
// simply swap all data members from
// the first to the second matrix instead
// of copying

void swap(Matrix& first, Matrix& second)
{
    swap(first.m_rows, second.m_rows);
    swap(first.m_cols, second.m_cols);
    swap(first.theMatrix, second.theMatrix);
}

// returns a reference to a
// position row,col in the matrix
float& Matrix::access(int row, int col) const
{
    // check dimensions
    if((row > this->getRowCount()) | (col > this->getColCount()) |
       (row < 0) | (col < 0)) {

        cout << "Dimensions are out of range." << endl;

    }
    else { // dimensions are good, so return position
        return theMatrix[row][col];
    }

}

// overloads << and writes matrix to console
ostream& operator<<(ostream& output, Matrix& m)
{
    // print row/col
    output << m.getRowCount() << " " << m.getColCount() << " " << endl;

    // iterate through and print each i,j of the matrix
    for(int i=0; i<m.getRowCount(); i++){
        for(int j=0; j<m.getColCount(); j++) {

            output << m.access(i, j) << " ";

            // newline for each row
            if( j == m.getColCount() - 1) {
                output << endl;
            }

        }
    }

    output << endl;

    return output;
}

istream &operator>>(istream& input, Matrix& m)
{
    // get the rows and columns
    input >> skipws >> m.m_rows >> m.m_cols;

    // allocate memory
    m.theMatrix = new float* [m.getRowCount()];

    for(int i=0; i<m.getRowCount(); i++) {
        m.theMatrix[i] = new float [m.getColCount()];
    }

    // get each element
    for(int i=0; i<m.getRowCount(); i++) {
        for(int j=0; j<m.getColCount(); j++) {
            input >> skipws >> m.access(i,j);
        }
    }
    return input;
}

// returns the transpose of the matrix
Matrix operator!(const Matrix &m)
{
    // create the result, it has reverse dimensions
    Matrix result(m.getColCount(), m.getRowCount());

    // iterate through
    for(int i=0; i<m.getRowCount(); i++) {
        for(int j=0; j<m.getColCount(); j++) {

            // reverse the entries
            result.access(j,i) = m.access(i, j);
        }
    }
    return result;
}

// assignment operator is overloaded so
// the lhs (this) is idential to the rhs

// note that the parameter is passed-by-value
// for optimization, lets the compiler do the work

Matrix& Matrix::operator=(Matrix m)
{
    // check for self assignment
    if(this != &m)
    {
         // use swap for efficieny
        swap(*this, m);
        return *this;
    }
}

// returns a matrix that is equal to lhs+rhs
Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    // the result to return
    Matrix result(rhs.getRowCount(), rhs.getColCount());


    // check dimensions
    if((lhs.getRowCount() != rhs.getRowCount()) |
       (lhs.getColCount() != rhs.getColCount())) {
            cout << "Dimensions are not equal, cannot add matrices." << endl;
       }

   // dimensions are good, so add each element together
   else {
            // iterate through rhs and lhs
            for(int i=0; i<rhs.getRowCount(); i++) {
                for(int j=0; j<rhs.getColCount(); j++) {

                    // put rhs+lhs in result
                    result.access(i,j) = rhs.access(i, j) + lhs.access(i, j);

                }
            }
   }

    return result;

}

// scalar multiplication
Matrix operator*(const float &lhs, const Matrix &rhs)
{

    // create the result matrix
    Matrix result(rhs.getRowCount(), rhs.getColCount());


    // iterate through
    for(int i=0; i<rhs.getRowCount(); i++) {
        for(int j=0; j<rhs.getColCount(); j++) {

            // put lhs * rhs (where lhs is a scalar)
            // in result
            result.access(i,j) = rhs.access(i, j) * lhs;

        }
    }

    return result;

}

// scalar the other way around
Matrix operator*(const Matrix &rhs, const float &lhs)
{
    // create the result matrix
    Matrix result(rhs.getRowCount(), rhs.getColCount());


    // iterate through
    for(int i=0; i<rhs.getRowCount(); i++) {
        for(int j=0; j<rhs.getColCount(); j++) {

            // put lhs * rhs (where lhs is a scalar)
            // in result
            result.access(i,j) = rhs.access(i, j) * lhs;
        }
    }
    return result;
}

// multiplication is currently O(n^3) but
// working on implementing Strassen's algo
// to optimize..

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    // create the result matrix
    // it has rows of lhs and cols of rhs
    Matrix result(lhs.getRowCount(), rhs.getColCount());

    // check dimensions
    if( (lhs.getRowCount() != rhs.getColCount()) |
        (lhs.getColCount() != rhs.getRowCount()) ) {
            cout << "Dimensions are not condusive for matrix multiplication." << endl;
        }
    else {
            // iterate through
            for(int i=0; i<lhs.getRowCount(); i++) {
                for(int j=0; j<rhs.getColCount(); j++) {

                    float sum =0;

                    for(int k=0; k < rhs.getRowCount(); k++ ) {
                        sum += lhs.access(i, k) * rhs.access(k, j);
                    }
                    result.access(i,j) = sum;
                }
            }
    }

    return result;
}

// equality operator returns true if matricies are identical
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
    // check dimensions
    if( (lhs.getRowCount() != rhs.getRowCount()) |
        (lhs.getColCount() != rhs.getColCount()) ) {

            // dimensions are not equal
            return false;
        }
   else {
            // check each element
            for(int i=0; i<lhs.getRowCount(); i++) {
                for(int j=0; j<lhs.getColCount(); j++) {

                    if(lhs.access(i,j) != rhs.access(i,j)) {
                        return false;
                    }
                }
            }
   }
   return true;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs)
{
    // simply the opposite of the == operand
   return !(lhs == rhs);
}
