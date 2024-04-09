**Objective:** Get familiar with basic use of classes and methods,
learning to implement your own classes based on a given class
declaration.

In this task you are required to implement a full class that handles 
a bank account, starting from constructor, along with a few functions 
for accessing the class attributes and some functions that perform bank 
account operations. There is also one function outside
the class, `Transfer`, that will transfer money between two bank
accounts.

1. Start by going over the class declaration in `bank_account.hpp`.
The class declaration has doxygen comments that explains the intended 
purpose of each function.  

2. Check `main` function in `main.cpp` file to see how these functions are used. 

3. Implement each function definition in `bank_account.cpp`.

The given `main` function prints the following output when everything works as 
intended.

```
Owner: Rasse Rikas
Number: 21345
Balance: 0
Depositing 100 to account.
Balance: 100
Withdrawing 50 from account.
Balance: 50
Trying to withdraw 100.
Balance: 50
Account num: 43662, owned by: Kaisa Kroisos, balance: 1000 eur.
Transfering 100.0 from Kaisa Kroisos to Rasse Rikas.
Transfer succesful!
Transfering 500.0 from Rasse Rikas to Kaisa Kroisos.
Transfer failed!
```