#ifndef MATRIX_H
#define MATRIX_H
/**
* @file Matrix.h
* @author Linoy Bushari linoy.bushari@mail.huji.ac.il
* @date 9 Sep 2020
*/

// ------------------------------- includes -------------------------------
#include <iostream>
#include <string>

// ------------------------------ functions -----------------------------

/**
 * this class represent a matrix with values of type float.
 */
class Matrix
{
    //************************************************//
    //****************** members *********************//
    //************************************************//

    float *_matrix;
    int _rows, _cols, _len;

public:
    //************************************************//
    //**************** constructors ******************//
    //************************************************//

    /**
     * Constructs matrix rows * cols with 0 in each val.
     * @param rows num of rows in new matrix
     * @param cols num of cols in new matrix
     */
    Matrix(int rows, int cols);

    /**
     * Constructs 1*1 matrix, where the single element is initiated to 0.
     */
    Matrix();

    /**
     * Constructs matrix which is a copy of another matrix.
     * @param m the matrix that is copied
     */
    Matrix(const Matrix &m);

    /**
     * Destroys the matrix while removes _matrix from heap.
     */
    ~Matrix();

    //****************** getters *******************//

    /**
     * Returns the amount of rows (int).
     * @return the amount of rows (int).
     */
    int getRows() const;

    /**
     * Returns the amount of cols (int).
     * @return the amount of cols.
     */
    int getCols() const;

    //****************** another functions *******************//

    /**
     * Transforms a matrix into a column vector.
     * @return reference to the matrix after being editted.
     */
    Matrix &vectorize();

    /**
     * prints the matrix with matrix original format.
     */
    void print() const;

    //************************************************//
    //****************** operators *******************//
    //************************************************//

    /**
     * Assignment operator - copies the contents of another Matrix object to this.
     * @param other Matrix to copy values from.
     * @return current matrix.
     */
    Matrix &operator=(const Matrix &other);

    /**
     * Matrix multiplication - multiplicates the matrix with another one.
     * @param other the matrix to multificate with.
     * @return new matrix - the result of operation.
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * scalar multification on the right.
     * @param scalar the scalar to multificate with the matrix.
     * @return new matrix - the result.
     */
    Matrix operator*(const float scalar) const;

    /**
     * friend function - scalar multification on the left.
     * @param scalar the scalar to multificate with the matrix.
     * @return new matrix - the result.
     */
    friend Matrix operator*(const float scalar, const Matrix &matrix);

    /**
     * matrix multification of a & b matrix -  it is equivalent to a = a * b.
     * @param other the matrix to multificate with.
     * @return a reference to the left sided matrix - "a".
     */
    Matrix &operator*=(const Matrix &other);

    /**
     * scalar multification when the result assigned to the old matrix.
     * @param scalar the scalar that used in multification.
     * @return a reference to the current matrix.
     */
    Matrix &operator*= (const float scalar);

    /**
     * Scalar division on the right.
     * @param scalar the scalar to divide with.
     * @return a new matrix - the result.
     */
    Matrix operator/(const float scalar) const;

    /**
     * Scalar division on the right when the result assigned to original matrix
     * @param scalar the scalar to divide with.
     * @return a reference to original matrix.
     */
    Matrix &operator/=(const float scalar);

    /**
     * matrix addition.
     * @param other the another matrix for the addition.
     * @return the result - a new matrix.
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * matrix addition when result assigned to current matrix.
     * @param other the another matrix for the addition.
     * @return a reference to current matrix.
     */
    Matrix &operator+=(const Matrix &other);

    /**
     * scalar addition to each cell of the matrix.
     * @param scalar the scalar to add.
     * @return a reference to current matrix afted being eddited.
     */
    Matrix &operator+=(const float scalar);

    /**
     * returns a reference to the cell (i, j) in the matrix.
     * @param i row of the cell
     * @param j col of the cell
     * @return a reference to the (i, j) cell.
     */
    float &operator()(const int i, const int j);

    /**
     * returns the value of the cell (i, j) in the matrix.
     * @param i row of the cell
     * @param j col of the cell
     * @return the value of the (i, j) cell.
     */
    float operator()(const int i, const int j) const;

    /**
     * returns a reference to the k element in matrix (viewed as 1D array).
     * @param k the index of element.
     * @return a reference to the k element in matrix.
     */
    float &operator[](const int k);

    /**
     * returns the value of the k element in matrix (viewed as 1D array).
     * @param k the index of element.
     * @return returns the value of the k element in matrix.
     */
    float operator[](const int k) const ;

    /**
     * checks if matrixs are equal.
     * @param other the other matrix to compare with.
     * @return true if equals, otherwise false.
     */
    bool operator==(const Matrix &other) const;

    /**
     * checks if matrixs are not equal.
     * @param other the other matrix to compare with.
     * @return true if not equals, otherwise false.
     */
    bool operator!=(const Matrix &other) const;

    /**
     * Fills matrix elements. Reads from given input stream.
     * @param is the input stream to read from.
     * @param matrix the matrix to write to.
     * @return reference to the input steam.
     */
    friend std::istream &operator>>(std::istream &is, Matrix &matrix);

    /**
     * prints matrix to output stream. Reads from given output stream.
     * @param is the output stream to read from.
     * @param matrix the matrix to read from.
     * @return reference to the output steam.
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix); /** need to test with file*/ //cant be const - not a member!!

};

#endif