#ifndef AALTO_ELEC_CPP_MATRIX
#define AALTO_ELEC_CPP_MATRIX

#include <vector>

typedef std::vector<std::vector<int>> Matrix;

/**
 * \brief Reads n x n matrix elements from the standard input stream one number
 * at a time.
 *
 * \param n The number of rows and columns of the matrix.
 * \return The matrix filled with read elements
 */
Matrix ReadMatrix(int n);

/**
 * \brief Returns 90 degrees clockwise rotated version of the input matrix. The
 * input matrix cannot be modified since it is const.
 *
 * \param m The matrix to be rotated
 * \return A new Matrix object that is 90 degrees clockwise rotated version of
 * input matrix.
 */
Matrix Rotate90Deg(const Matrix& m);

/**
 * \brief Prints the matrix on the standard output stream
 *
 * When m = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}, the function
 * should print
 *
 * Printing out a 3 x 3 matrix:\n
 * 1 2 3 \n
 * 1 2 3 \n
 * 1 2 3 \n
 *
 * \param m The matrix to be printed
 */
void Print(const Matrix& m);

#endif
