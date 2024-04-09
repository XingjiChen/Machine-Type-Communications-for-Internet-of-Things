#include "customer.hpp"
#include <iostream>

Customer::Customer(const std::string& name, const std::string& id)
        : name_(name), customer_id_(id) {}

std::string Customer::GetName() const {
    return name_;
}

std::string Customer::GetID() const {
    return customer_id_;
}

int Customer::GetLoanAmount() const {
    return loans_.size();
}

std::vector<Book> Customer::GetLoans() const {
    return loans_;
}

bool Customer::LoanBook(Book& b) {
    if (b.Loan()) {
        loans_.push_back(b);
        return true;
    }
    return false;
}

void Customer::ReturnBook(Book& b) {
    for (auto it = loans_.begin(); it != loans_.end(); ++it) {
        if (it->GetISBN() == b.GetISBN()) {
            it->Restore();
            loans_.erase(it);
            break;
        }
    }
}


//void Customer::Print() const {
//    std::cout << "Customer: " << name_ << ", " << customer_id_ << ", has " << loans_.size() << " books on loan:" << std::endl;
//    for (const auto& book : loans_) {
//        book.Print();
//    }
//}

void Customer::Print() const {
    std::cout << "Customer: " << name_ << ", " << customer_id_ << ", has " << loans_.size() << " books on loan:" << std::endl;
    for (const auto& book : loans_) {
        std::cout << "- Book: " << book.GetName() << ", author: " << book.GetAuthor()
                  << ", ISBN: " << book.GetISBN() << ", loaned " << (book.GetStatus() ? "true" : "false")
                  << ", due date: " << book.GetDueDate().day << "." << book.GetDueDate().month << "."
                  << book.GetDueDate().year << std::endl;
    }
}


