/**
* @file Filters.cpp
* @author Linoy Bushari linoy.bushari@mail.huji.ac.il
* @date 9 Sep 2020
*/

// ------------------------------- includes -------------------------------
#include "Matrix.h"
#include <cmath>

// ------------------------------- definitions -------------------------------
/**
 * define limits of color tables.
 */
#define TOTAL_COLORS_SUM 256
#define LAST_COLOR 255
#define FIRST_COLOR 0

/**
 * define the center indexes of matB for conv func - (1, 1).
 */
#define CENTER_OF_B 1

// ------------------------------ functions -----------------------------

/**
 * @brief normalize matrix impage to be on 0-255.
 * @param image a matrix represents an image
 * @return reference to the image.
 */
Matrix &normalize(Matrix &image)
{
    for (int i = 0; i < image.getRows() * image.getCols() ; ++i)
    {
        if (image[i] < 0)
        {
            image[i] = FIRST_COLOR;
        }
        else if (image[i] >= TOTAL_COLORS_SUM)
        {
            image[i] = LAST_COLOR;
        }
    }
    return image;
}

void calculateValue(const Matrix &matA, const Matrix &matB, const int i, const int j,
                    Matrix &newMatrix)
{
    float newVal = 0;
    for (int k = -1; k < 2; k ++)
    {
        for (int l = -1; l < 2; l ++)
        {
            if (i + k >= 0 && j + l >= 0 && i + k < matA.getRows() &&
                j + l < matA.getCols()) //if not out of range of matrix A.
            {
                newVal += matA(i + k, j + l) *
                          matB(CENTER_OF_B + k, CENTER_OF_B + l);
            }
        }
    }
    newMatrix(i, j) = rintf(newVal);
}

/**
 * @brief make convolution on 2 matrix
 * @param matA the matrix to convoluate - the lower matrix.
 * @param matB the upper matrix.
 * @return a new matrix - the result.
 */
Matrix convolution(const Matrix &matA, const Matrix &matB)
{
    Matrix newMatrix(matA.getRows(), matA.getCols());
    for (int i = 0; i < matA.getRows(); ++i)
    {
        for (int j = 0; j < matA.getCols(); ++j)
        {
            calculateValue(matA, matB, i, j, newMatrix);
        }
    }
    return newMatrix;
}

/**
 * @brief Performs quantization on the input image by the given number of levels.
 * @param image the imput image.
 * @param levels int - the level of operation.
 * @return  Returns new matrix which is the result of running the operator on the image.
 */
Matrix quantization(const Matrix &image, int levels)
{
    Matrix newImage(image.getRows(), image.getCols());
    int *colors = new int[levels + 1];
    for (int i = 0; i < levels + 1 ; i++)
    {
        colors[i] = i * (TOTAL_COLORS_SUM / levels);
    }
    int *averages = new int[levels];
    for (int i = 0; i < levels ; i++)
    {
        averages[i] = (colors[i] + colors[i + 1] -1) / 2;
    }

    for (int i = 0; i < image.getRows() * image.getCols(); i++)
    {
        int indOfAvg = (int) (image[i] / (TOTAL_COLORS_SUM / levels));
        // value is in range of the int part to int + 1 - therefor the index is the int part.
        newImage[i] = (float) averages[indOfAvg];
    }
    delete[] colors;
    delete[] averages;
    return newImage;
}

/**
 * @brief Performs gaussian blurring on the input image.
 * @param image the matrix of image to blur.
 * @return new matrix which is the result of running the operator on the image.
 */
Matrix blur(const Matrix &image)
{
    Matrix convoluator(3, 3);
    int values[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    for (int i = 0; i < 9; i++)
    {
        convoluator[i] = ((float) 1 / 16) * values[i];
    }
    Matrix result = convolution(image, convoluator);
    return normalize(result);
}

 /**
  * @brief Performs sobel edge detection on the input image.
  * @param image a matrix, the input image.
  * @return Returns new matrix which is the result of running the operator on the image.
  */
Matrix sobel(const Matrix &image)
{
    Matrix xConvoluator(3, 3);
    int xValues[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    for (int i = 0; i < 9; i++)
    {
        xConvoluator[i] = ((float) 1 / 8) * xValues[i];
    }
    Matrix xMat = convolution(image, xConvoluator);
    Matrix yConvoluator(3, 3);
    int yValues[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    for (int i = 0; i < 9; i++)
    {
        yConvoluator[i] = ((float) 1 / 8) * yValues[i];
    }
    Matrix yMat = convolution(image, yConvoluator);
    Matrix result = xMat + yMat;
    return normalize(result);
}