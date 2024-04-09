#ifndef AALTO_ELEC_CPP_VECTOR_IT
#define AALTO_ELEC_CPP_VECTOR_IT

#include <vector>

/**
 * \brief Reads a sequence of integers into a vector. Stops when user gives
 * something other than an integer.
 *
 * For example, if the user writes
 *  1 2 3 4 !\n
 *
 * the function should return a vector with values {1, 2, 3, 4}
 * \return std::vector<int> that contains the read integers
 */
std::vector<int> ReadVector(void);

/**
 * \brief Prints the sum of each pair of adjacent elements in the vector of
 * integer values.
 *
 * For example, if values = {1, 2, 3, 4} it should print
 *
 * 3 5 7
 *
 * \param values a constant vector of integer values.
 */
void PrintSum1(const std::vector<int> &values);

/**
 * \brief Prints the sum of the first and last elements, followed by the sum of
 * the second and second-to-last, and so on.
 *
 * \param values a constant vector of integer values.
 */
void PrintSum2(const std::vector<int> &values);

#endif
