#ifndef AALTO_ELEC_CPP_LIST
#define AALTO_ELEC_CPP_LIST

#include <iostream>
#include <list>
#include <string>

/**
 * \brief Reads all lines from the stream into the specfied list. The stored
 * lines should not contain the newline characters. Returns the input
 * stream object after reading all the lines.
 *
 * \param is The input stream object
 * \param list The list that contains all the lines in the input stream
 * \return std::istream& The input stream object after reading all the lines
 */
std::istream& GetLines(std::istream& is, std::list<std::string>& list);

/**
 * \brief Print the list, with a newline after each entry.
 *
 * \param list The list of lines
 */
void Print(const std::list<std::string>& list);

/**
 * \brief Sorts the list and removes all duplicate entries.
 *
 * \param list The list of lines
 */
void SortAndUnique(std::list<std::string>& list);

#endif
