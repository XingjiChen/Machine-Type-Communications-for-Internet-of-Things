#include <cstddef>
#include <iostream>

#include "bank_account.hpp"

int main(void) {
    BankAccount rasse_account("Rasse Rikas", "21345");
    std::cout << "Owner: " <<  rasse_account.GetOwner() << std::endl;
    std::cout << "Number: " << rasse_account.GetNumber() << std::endl;
    std::cout << "Balance: " << rasse_account.GetBalance() << std::endl;
    
    std::cout << "Depositing 100 to account." << std::endl;
    rasse_account.Deposit(100.0);
    std::cout << "Balance: " << rasse_account.GetBalance() << std::endl;

    std::cout << "Withdrawing 50 from account." << std::endl;
    rasse_account.Withdraw(50.0);
    std::cout << "Balance: " << rasse_account.GetBalance() << std::endl;

    std::cout << "Trying to withdraw 100." << std::endl;
    rasse_account.Withdraw(100.0); //should do nothing!
    std::cout << "Balance: " << rasse_account.GetBalance() << std::endl;

    BankAccount kaisa_account("Kaisa Kroisos", "43662", 1000.0);
    kaisa_account.Print();

    std::cout << "Transfering 100.0 from " << kaisa_account.GetOwner() << " to " << rasse_account.GetOwner() << "." << std::endl;
    bool t = Transfer(kaisa_account, rasse_account, 100.0);
    std::cout << "Transfer " << (t ? "succesful!" : "failed!") << std::endl;

    std::cout << "Transfering 500.0 from " << rasse_account.GetOwner() << " to " << kaisa_account.GetOwner() << "." << std::endl;
    t = Transfer(rasse_account, kaisa_account, 500.0); //should fail!
    std::cout << "Transfer " << (t ? "succesful!" : "failed!") << std::endl;

    return 0;
}
