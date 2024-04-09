#ifndef AALTO_ELEC_CPP_VECTOR_STRINGS
#define AALTO_ELEC_CPP_VECTOR_STRINGS

#include <string>
#include <vector>

/**
 * \brief Reads the command from the standard input stream and
 * performs specific operations on a vector of strings.
 *
 * This function first prompts for a command, then gets the commands,
 * and finally performs the described operations according to the command.
 *
 * this function is required to have a local vector of strings variable,
 * which is initially empty. This local variable is used as the argument when
 * calling the other functions.
 */
void CMDReader();

/**
 * \brief Prompts for a string in standard output stream,
 * acquires a string from standard input stream, and appends the input string to
 * the specified vector of strings.
 *
 * \param names The vector strings.
 *
 * \note The & means that the vector is passed as a reference.
 * We will cover references later in the course. For now, it is enough to
 * assume that the changes made to the vector names are reflected to the
 * caller variable in the caller's scope.
 */
void Adder(std::vector<std::string>& names);
/**
 * \brief Removes the last string in the specfied vector of strings and prints
 * the removed string on the standard output stream.
 *
 * \param names The vector of strings
 *
 * \note The & means that the vector is passed as a reference.
 * We will cover references later in the course. For now, it is enough to
 * assume that the changes made to the vector names are reflected to the
 * caller variable in the caller's scope.
 */
void Remover(std::vector<std::string>& names);

/**
 * \brief Prints the string in the specfied vector of strings
 *
 * \param names The vector of strings
 */
void Printer(std::vector<std::string>& names);

#endif
