#include <cstddef>
#include <iostream>

#include "book.hpp"
#include "customer.hpp"
#include "library.hpp"

int main(void) {
  /*TESTING BOOK*/
  std::cout << "****\nCreating a book\n****" << std::endl;
  auto b = Book("C++ primer", "Lippman, Stanley B.", "978-0-321-71411-4");
  std::cout << "\n****\nTesting getters\n****" << std::endl;
  std::cout << "Name: " << b.GetName() << std::endl;
  std::cout << "Author: " << b.GetAuthor() << std::endl;
  std::cout << "ISBN: " << b.GetISBN() << std::endl;
  std::cout << "Loaned: " << (b.GetStatus() ? "yes" : "no") << std::endl;
  std::cout << "\n****\nTesting print\n****" << std::endl;
  b.Print();
  std::cout << "\n****\nTesting loan\n****" << std::endl;
  std::cout << "Loaning " << (b.Loan() ? "succesful" : "failed") << std::endl;
  std::cout << "Loaned: " << (b.GetStatus() ? "yes" : "no") << std::endl;
  b.Print();
  std::cout << "Loaning " << (b.Loan() ? "succesful" : "failed") << std::endl;
  std::cout << "\n****\nTesting restore\n****" << std::endl;
  b.Restore();
  b.Print();

  /*TESTING CUSTOMER*/
  std::cout << "\n****\nCreating customer\n****" << std::endl;
  auto c = Customer("Chris Customer", "34674568");
  std::cout << "\n****\nTesting getters\n****" << std::endl;
  std::cout << "Name: " << c.GetName() << std::endl;
  std::cout << "Customer ID: " << c.GetID() << std::endl;
  std::cout << "Number of loans: " << c.GetLoanAmount() << std::endl;
  std::cout << "\n****\nTesting print\n****" << std::endl;
  c.Print();
  std::cout << "\n****\nTesting loanBook\n****" << std::endl;
  c.LoanBook(b);
  c.Print();
  auto b2 = Book("The C++ programming language", "Stroustrup, Bjarne",
                 "978-0-321-56384-2");
  c.LoanBook(b2);
  c.Print();
  std::cout << "\n****\nTesting returnBook\n****" << std::endl;
  c.ReturnBook(b);
  c.Print();

  /*TESTING LIBRARY*/
  std::cout << "\n****\nCreating library\n****" << std::endl;
  auto l = Library("Test Library");
  std::vector<Book> &books = l.GetBooks();
  books.push_back(b);
  books.push_back(b2);
  auto b3 = Book("Test Book", "Stroustrup, Bjarne", "978-0-123-23564-2");
  books.push_back(b3);
  std::vector<Customer> &customers = l.GetCustomers();
  customers.push_back(c);
  std::cout << "\n****\nTesting getters\n****" << std::endl;
  std::cout << "Name: " << l.GetName() << std::endl;
  std::cout << "Books: " << std::endl;
  for (auto &b : books) b.Print();
  std::cout << "Customers: " << std::endl;
  for (auto &c : customers) c.Print();
  std::cout << "\n****\nTesting finders\n****" << std::endl;
  auto tmp = l.FindBookByName("Test Book");
  tmp.Print();
  auto tmp_v = l.FindBooksByAuthor("Stroustrup, Bjarne");
  for (auto &b : tmp_v) b.Print();
  tmp_v = l.FindAllLoanedBooks();
  for (auto &b : tmp_v) b.Print();
  auto tmp2 = l.FindCustomer("34674568");
  tmp2.Print();

  return 0;
}
