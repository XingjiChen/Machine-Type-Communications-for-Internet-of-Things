#ifndef ELEC_AS_CPP_LIBRARY
#define ELEC_AS_CPP_LIBRARY

#include <string>
#include <vector>

#include "book.hpp"
#include "customer.hpp"

class Library {
 public:
    Library(const std::string& name);

    std::string GetName() const;

    std::vector<Book>& GetBooks();

    std::vector<Customer>& GetCustomers();

    Book FindBookByName(const std::string& name);

    std::vector<Book> FindBooksByAuthor(const std::string& name);

    std::vector<Book> FindAllLoanedBooks();

    Customer FindCustomer(const std::string& id);
  /**
   * \brief Construct a new Library object
   *
   * \param name the library's name (const reference to string)
   */
  

  /**
   * \brief Get the library's name as a string, takes no parameters.
   *
   * This function should not alter the Library object's state, in other words
   * the function should be const.
   *
   * Function identifier: GetName
   *
   * \return std::string
   */
  

  /**
   * \brief Get the Library's books as a reference to a vector<Book>, takes no
   * parameters.
   *
   * Function identifier: GetBooks
   *
   * \return std::vector<Book>&
   */
  

  /**
   * \brief Get the Library's customers as a reference to a vector<Customer>,
   * takes no parameters.
   *
   * Function identifier: GetCustomers
   *
   * \return std::vector<Customer>&
   */
  

  /**
   * \brief Searches for a book by its name.
   *
   * Function identifier: FindBookByName
   *
   * \param name the name of the book (a const reference to a string)
   *
   * \return a copy of the found Book object if it can be found. If a Book is
   * not found, a new book with an empty strings as parameters for the name,
   * author and isbn is returned.
   */
  

  /**
   * \brief Searches for books by their author.
   *
   * Function identifier: FindBooksByAuthor
   *
   * \param name the author name (a const reference to a string)
   *
   * \return a vector of Books with the specified author. If no books are found,
   * an empty vector is returned.
   */
  

  /**
   * \brief Returns  a vector of loaned Books, takes no parameters.
   *
   * Function identifier: FindAllLoanedBooks
   *
   * \return a vector of loaned Books. If no books are found,
   * an empty vector is returned.
   */
  

  /**
   * \brief Searches for a customer with specfied id
   *
   * Function identifier: FindCustomer
   *
   * \param id the id of the customer (a const reference to a string)
   *
   * \return A copy of the found customer. if a Customer is not found, a new
   * Customer with empty name and id is returned.
   */
  

 private:
  /* Member variables:
   * name (string)
   * books (vector<Book>)
   * customers (vector<Customer>)
   */
    std::string name_;
    std::vector<Book> books_;
    std::vector<Customer> customers_;
};

#endif
