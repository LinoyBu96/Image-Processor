/**
* @file Matrix.cpp
* @author Linoy Bushari linoy.bushari@mail.huji.ac.il
* @date 9 Sep 2020
*/

// ------------------------------- includes -------------------------------
#include "Matrix.h"
#include <iostream>
#include <string>

// ------------------------------- definitions -------------------------------
#define END_OF_ROW 0
#define MINIMAL_MATRIX_SIZE 1

// ------------------------------ using -----------------------------
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

// ------------------------------ functions -----------------------------

/**
 * this file implements the class Matrix in which an object is a matrix with values of type float.
 */

// constructor
Matrix::Matrix(int rows, int cols)
{
    if (rows < MINIMAL_MATRIX_SIZE || cols < MINIMAL_MATRIX_SIZE)
    {
        std::cerr << "Invalid matrix dimensions.\n";
        exit(EXIT_FAILURE);
    }
    _rows = rows;
    _cols = cols;
    _len = rows * cols;
    _matrix = new float[_len];
    for (int i = 0; i < _len; i ++)
    {
        (*this)[i] = 0;
    }
}

// default constractor
Matrix::Matrix() : Matrix(MINIMAL_MATRIX_SIZE, MINIMAL_MATRIX_SIZE) {};

// contructs matrix that is equal to m matrix.
Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols)
{
    for (int i = 0; i < _len; i ++)
    {
        (*this)[i] = m[i];
    }
}

Matrix::~Matrix()
{
    delete[] _matrix;
}

int Matrix::getRows() const
{
    return _rows;
}

int Matrix::getCols() const
{
    return _cols;
}

// turns matrix to be column vector.
Matrix &Matrix::vectorize()
{
    _cols = 1;
    _rows = _len;
    return *this;
}

/**
 * prints the matrix with matrix original format.
 */
void Matrix::print() const
{
    for (int i = 0; i < _len; i ++)
    {
        cout << (*this)[i];
        if ((i + 1) % _cols == END_OF_ROW && (i + 1) != _len)
            //if the current cell is in the end of the row and not the in the last row:
        {
            cout << endl;
        }
        else if ((i + 1) != _len)
        {
            cout << " ";
        }
    }
}

/**
 * Assignment operator - copies the contents of another Matrix object to this.
 * @param other Matrix to copy values from.
 * @return current matrix.
 */
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        delete[] _matrix;
        _rows = other._rows;
        _cols = other._cols;
        _len = other._len;
        _matrix = new float[_len];
        for (int i = 0; i < _len ; ++i)
        {
            (*this)[i] = other[i];
        }
    }
    return (*this);
}

/**
 * Matrix multiplication - multiplicates the matrix with another one.
 * @param other the matrix to multificate with.
 * @return new matrix - the result of operation.
 */
Matrix Matrix::operator*(const Matrix &other) const
{
    if (_cols == other._rows)
    {
        Matrix newMatrix(_rows, other._cols);
        for (int i = 0; i < _rows; i++)
        {
            for (int j = 0; j < other._cols; j++)
            {
                for (int k = 0; k < _cols; k++)
                {
                    newMatrix(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return newMatrix;
    }
    cerr << "Invalid matrix dimensions.\n";
    exit(EXIT_FAILURE);
}

/**
 * scalar multification on the right.
 * @param scalar the scalar to multificate with the matrix.
 * @return new matrix - the result.
 */
Matrix Matrix::operator*(const float scalar) const
{
    if (scalar == 0)
    {
        Matrix newMatrix(_rows, _cols);
        return newMatrix;
    }
    Matrix newMatrix(*this);
    for (int i = 0; i < _len ; ++i)
    {
        newMatrix[i] *= scalar;
    }
    return newMatrix;
}

/**
 * friend function - scalar multification on the left.
 * @param scalar the scalar to multificate with the matrix.
 * @return new matrix - the result.
 */
Matrix operator*(const float scalar, const Matrix &matrix)
{
    if (scalar == 0)
    {
        Matrix newMatrix(matrix._rows, matrix._cols);
        return newMatrix;
    }
    Matrix newMatrix(matrix);
    for (int i = 0; i < newMatrix._len ; ++i)
    {
        newMatrix[i] *= scalar;
    }
    return newMatrix;
}

/**
 * matrix multification of a & b matrix -  it is equivalent to a = a * b.
 * @param other the matrix to multificate with.
 * @return a reference to the left sided matrix - "a".
 */
Matrix &Matrix::operator*=(const Matrix &other)
{
    *this = ((*this) * other);
    return *this;
}

/**
 * matrix multification of a & b matrix -  it is equivalent to a = a * b.
 * @param other the matrix to multificate with.
 * @return a reference to the left sided matrix - "a".
 */
Matrix &Matrix::operator*= (const float scalar)
{
    (*this) = (*this) * scalar;
    return *this;
}

/**
 * Scalar division on the right.
 * @param scalar the scalar to divide with.
 * @return a new matrix - the result.
 */
Matrix Matrix::operator/(const float scalar) const
{
    if (scalar == 0)
    {
        for (int i = 0; i < _len; i++)
        {
            if ((*this)[i] != 0)
            {
                cerr << "Division by zero.\n";
                exit(EXIT_FAILURE);
            }
        }
        return (*this); /** check it really returns copy */
    }
    Matrix newMatrix = ((*this) * (1 / scalar));
    return newMatrix;
}

// Scalar division on the right when the result assigned to original matrix.
Matrix &Matrix::operator/=(const float scalar)
{
    (*this) = ((*this) / scalar);
    return *this;
}

// matrix addition.
Matrix Matrix::operator+(const Matrix &other) const
{
    if (_rows == other._rows && _cols == other._cols)
    {
        Matrix newMatrix = *this;
        for (int i = 0; i < _len; i++)
        {
            newMatrix[i] += other[i];
        }
        return newMatrix;
    }
    cerr << "Invalid matrix dimensions.\n";
    exit(EXIT_FAILURE);
}

// matrix addition when result assigned to current matrix.
Matrix &Matrix::operator+=(const Matrix &other)
{
    (*this) = ((*this) + other);
    return *this;
}

// scalar addition to each cell of the matrix.
Matrix &Matrix::operator+=(const float scalar)
{
    for (int i = 0; i < _len; i++)
    {
        (*this)[i] += scalar;
    }
    return *this;
}

// returns a reference to the cell (i, j) in the matrix.
float &Matrix::operator()(const int i, const int j)
{
    if (0 <= i && i < _rows && 0 <= j && j <_cols)
    {
        return (*this)[i * _cols + j];
    }
    cerr << "Index out of range.\n";
    exit(EXIT_FAILURE);
}

// returns the value of the cell (i, j) in the matrix.
float Matrix::operator()(const int i, const int j) const
{
    if (0 <= i && i < _rows && 0 <= j && _cols)
    {
        return (*this)[i * _cols + j];
    }
    cerr << "Index out of range.\n";
    exit(EXIT_FAILURE);
}

// returns a reference to the k element in matrix (viewed as 1D array).
float &Matrix::operator[](const int k)
{
    if (0 <= k && k < _len)
    {
        return _matrix[k];
    }
    cerr << "Index out of range.\n";
    exit(EXIT_FAILURE);
}

// returns the value of the k element in matrix (viewed as 1D array).
float Matrix::operator[](const int k) const
{
    if (0 <= k && k < _len)
    {
        return _matrix[k];
    }
    cerr << "Index out of range.\n";
    exit(EXIT_FAILURE);
}

// checks if matrixs are equal.
bool Matrix::operator==(const Matrix &other) const
{
    if (_rows != other._rows || _cols != other._cols || _len != other._len)
    {
        return false;
    }
    for (int i = 0; i < _len ; ++i)
    {
        if ((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

// checks if matrixs are not equal.
bool Matrix::operator!=(const Matrix &other) const
{
    if (_rows != other._rows || _cols != other._cols || _len != other._len)
    {
        return true;
    }
    for (int i = 0; i < _len ; ++i)
    {
        if ((*this)[i] != other[i])
        {
            return true;
        }
    }
    return false;
}

// Fills matrix elements. Reads from given input stream.
std::istream &operator>>(std::istream &is, Matrix &matrix)
{
    if (!is.good())
    {
        cerr << "Error loading from input stream.\n";
        exit(EXIT_FAILURE);
    }
    int inx = 0;
    float val;
    while (is >> val)
    {
        matrix[inx] = val;
        inx++;
    }
    return is;
}

//print matrix to output stream. Reads from given output stream.
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (int i = 0; i < matrix._len; i ++)
    {
        os << matrix[i];
        if ((i + 1) % matrix._cols == END_OF_ROW && (i + 1) != matrix._len)
        {
            os << endl;
        }
        else if ((i + 1) != matrix._len)
        {
            os << " ";
        }
    }
    return os;
}
