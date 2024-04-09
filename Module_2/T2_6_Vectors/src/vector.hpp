#ifndef AALTO_ELEC_CPP_VECTOR
#define AALTO_ELEC_CPP_VECTOR

#include <vector>

/**
 * \brief Finds the minimum value in the specfied vector of integers
 *
 * \param v The vector of integers that has at least one element
 * \return The minimum value in the vector
 */
int GetMin(std::vector<int> v);

/**
 * \brief Finds the maximum value in the specfied vector of integers
 *
 * \param v The vector of integers that has at least one element
 * \return The maximum value in the vector
 */
int GetMax(std::vector<int> v);

/**
 * \brief Calculates the average of the integer values in the specfied vector of
 * integers
 *
 * \param v The vector of integers that has at least one element
 * \return The calculated average value
 */
double GetAvg(std::vector<int> v);

#endif
