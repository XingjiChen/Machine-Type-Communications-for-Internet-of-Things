#include "bank_account.hpp"
#include <iostream>

// Constructor
BankAccount::BankAccount(std::string const& owner, std::string const& account_number, double balance)
        : owner_(owner), account_number_(account_number), balance_(balance) {}

// GetOwner
std::string BankAccount::GetOwner() const {
    return owner_;
}

// GetNumber
std::string BankAccount::GetNumber() const {
    return account_number_;
}

// GetBalance
double BankAccount::GetBalance() const {
    return balance_;
}

// Deposit
void BankAccount::Deposit(double amount) {
    if (amount > 0) {
        balance_ += amount;
    }
}

// Withdraw
bool BankAccount::Withdraw(double amount) {
    if (amount > 0 && amount <= balance_) {
        balance_ -= amount;
        return true;
    }
    return false;
}

// Print
void BankAccount::Print() const {
    std::cout << "Account num: " << account_number_
              << ", owned by: " << owner_
              << ", balance: " << balance_ << " eur.\n";
}

// Transfer
bool Transfer(BankAccount& source_account, BankAccount& target_account, double amount) {
    if (source_account.GetBalance() >= amount) {
        source_account.Withdraw(amount);
        target_account.Deposit(amount);
        return true;
    }
    return false;
}
