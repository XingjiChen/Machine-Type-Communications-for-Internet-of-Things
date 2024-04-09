#include "library.hpp"

#include <iostream>

#include "book.hpp"
#include "customer.hpp"

Library::Library(const std::string& name) : name_(name) {}

std::string Library::GetName() const {
    return name_;
}

std::vector<Book>& Library::GetBooks() {
    return books_;
}

std::vector<Customer>& Library::GetCustomers() {
    return customers_;
}

Book Library::FindBookByName(const std::string& name) {
    for (const auto& book : books_) {
        if (book.GetName() == name) {
            return book;
        }
    }
    return Book("", "", "", false); // 返回一个空的书籍对象
}

std::vector<Book> Library::FindBooksByAuthor(const std::string& name) {
    std::vector<Book> foundBooks;
    for (const auto& book : books_) {
        if (book.GetAuthor() == name) {
            foundBooks.push_back(book);
        }
    }
    return foundBooks;
}

std::vector<Book> Library::FindAllLoanedBooks() {
    std::vector<Book> loanedBooks;
    for (const auto& book : books_) {
        if (book.GetStatus()) {
            loanedBooks.push_back(book);
        }
    }
    return loanedBooks;
}

Customer Library::FindCustomer(const std::string& id) {
    for (const auto& customer : customers_) {
        if (customer.GetID() == id) {
            return customer;
        }
    }
    return Customer("", "");
}
