#ifndef ELEC_AS_CPP_CUSTOMER
#define ELEC_AS_CPP_CUSTOMER

#include <string>
#include <vector>

#include "book.hpp"

class Customer {
 public:
    Customer(const std::string& name, const std::string& id);

    std::string GetName() const;

    std::string GetID() const;

    int GetLoanAmount() const;

    std::vector<Book> GetLoans() const;

    bool LoanBook(Book& b);

    void ReturnBook(Book& b);

    void Print() const;
  /**
   * \brief Construct a new Customer
   *
   * \param name the customer's name (reference to const string)
   * \param id the customer number (reference to const string)
   */
  

  /**
   * \brief Get the Customer's name as a string, takes no parameters.
   *
   * This function should not alter the Customer object's state, in other
   * words the function should be const.
   *
   * Function identifier: GetName
   *
   * \return std::string
   */
  

  /**
   * \brief Get the Customer's customer number as a string, takes no
   * parameters.
   *
   * This function should not alter the Customer object's state, in other words
   * the function should be const.
   *
   * Function identifier: GetID
   *
   * \return std::string
   */
  

  /**
   * \brief Get the Customer's number of loans as an int, takes no parameters.
   *
   * This function should not alter the Customer object's state, in other words
   * the function should be const.
   *
   * Function identifier: GetLoanAmount
   *
   * \return int
   */
  

  /**
   * \brief Get the Customer's loans as a vector<Book>, takes no parameters.
   *
   * This function should not alter the Customer object's state, in other words
   * the function should be const.
   *
   * Function identifier: GetLoans
   *
   * \return std::vector<Book>
   */
  

  /**
   * \brief loans a book for the customer
   *
   * Function identifier: LoanBook
   *
   * \param b  a reference to the book to be loaned
   *
   * \return  the result of loaning (from Book::loan function).
   */
  

  /**
   * \brief Returns a book loaned by the customer. The function returns
   * nothing.
   *
   * Function identifier: ReturnBook
   *
   * \param b a reference to a book
   */
  

  /**
   * \brief write the customer's information to the standard output stream.
   *
   * The function takes no parameters and returns nothing.
   *
   * This function should not alter the Customer object's state, in other words
   * the function should be const.
   *
   * Function identifier: Print
   *
   * The output format should be like the following (for 2 loans):
   *
   * Customer: <name>, <customer_id>, has <number_of_loans> books on loan:\n
   * - Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due
   * date: <day>.<month>.<year>\n
   * - Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due
   * date: <day>.<month>.<year>\n
   *
   * (Book details must be printed on a single line)
   */
  

 private:
    std::string name_;
    std::string customer_id_;
    std::vector<Book> loans_;
  /* Member variables:
   * name (string)
   * customer id (string)
   * vector of loaned books (vector<Book>)
   */
  
};

#endif
