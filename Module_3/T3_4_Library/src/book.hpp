#ifndef ELEC_AS_CPP_BOOK
#define ELEC_AS_CPP_BOOK

#include <ctime>
#include <string>

/**
 * \brief Date structure
 *
 */
struct Date {
  int day;   /** The day of the date*/
  int month; /** The month of the date*/
  int year;  /** The year of the date*/

  /**
   * \brief Constructs a Date after setting its date field to local calendar
   * date of the computer.
   *
   * \return Date New Date object
   *
   * \note This is a static function. We have not covered static class member
   * functions. But, for this example it is enough to assume that
   * static members are associated with classes not objects. Thus,
   * static members are called with Date::Today() syntax.
   */
  static Date Today() {
    Date d;
    std::time_t t = time(0);
    struct tm* now = localtime(&t);
    d.day = now->tm_mday;
    d.month = now->tm_mon + 1;
    d.year = now->tm_year + 1900;
    return d;
  }
};

class Book {
 public:
    Book(const std::string& name, const std::string& author, const std::string& isbn, bool loaned = false, Date due_date = {0, 0, 0});

    // 获取书籍信息的方法声明
    std::string GetName() const;
    std::string GetAuthor() const;
    std::string GetISBN() const;
    bool GetStatus() const;
    Date GetDueDate() const;

    // 借阅和归还书籍的方法声明
    bool Loan();
    void Restore();

    // 打印书籍信息的方法声明
    void Print() const;
  /**
   * \brief Construct a new Book object
   *
   * \param name the book's name (reference to const string),
   * \param author the book's author (reference to const string),
   * \param isbn the book's ISBN number (reference to const string)
   * \param loaned the status of the book, loaned or not (bool), which is by
   *               default false
   * \param due_date due date as a Date structure (Date), which is by default
   *                  0-0-0
   */
  

  /**
   * \brief Get the Name of the book. It has no parameters.
   *
   * This function should not alter the Book object's state, in other words the
   * function should be const.
   *
   * Function identifier: GetName
   *
   * \return the Book's name as a std::string
   */
  

  /**
   * \brief Get the Book's author as a string, takes no parameters.
   *
   * This function should not alter the Book object's state, in other words the
   * function should be const.
   *
   * Function identifier: GetAuthor
   *
   * \return std::string
   */
  

  /**
   * \brief Get the Book's ISBN as a string, takes no parameters.
   *
   * This function should not alter the Book object's state, in other words the
   * function should be const.
   *
   * Function identifier: GetISBN
   *
   * \return std::string
   */
  

  /**
   * \brief Get the Book's status as a bool, takes no parameters.
   *
   * This function should not alter the Book object's state, in other words the
   * function should be const.
   *
   * Function identifier: GetStatus
   *
   * \return true if the book is loaned
   * \return false otherwise
   */
  

  /**
   * \brief Get the Book's due date, takes no parameters.
   *
   * This function should not alter the Book object's state, in other words the
   * function should be const.
   *
   * Function identifier: GetDueDate
   *
   * \return Date
   */
  

  /**
   * \brief Loans the book
   *
   * 1. Sets the due date to current date + 1 month.
   *    For example, if today is 1.9 ==> due date 1.10.
   *
   * 2. Sets the status to true returns true if loaning was successful
   *
   * 3. Returns the book's new status
   *
   * HINT: There is a function Today in the Date struct that returns the
   *       current date
   *
   * Function identifier: Loan
   *
   * \return true if loaning is successful
   * \return false otherwise.
   */
  

  /**
   * \brief Restores the book status to not loaned
   *
   * 1. sets the due date to 0-0-0
   *
   * 2. sets the status to false
   *
   * Function identifier: Restore
   */
  

  /**
   * \brief Prints the book's information to the standard output stream.
   *
   * The function takes no parameters and returns nothing.
   * This function should not alter the Book object's state, in other words
   * the function should be const.
   *
   * The output format should be like the following:
   *
   * Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due
   * date: <day>.<month>.<year>\n
   *
   * (On a single line)
   *
   * Function identifier: Print
   */
  

 private:
  std::string name_;
  std::string author_;
  std::string isbn_;
  bool loaned_;
  Date due_date_;
};

#endif
