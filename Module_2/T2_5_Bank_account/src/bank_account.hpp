#ifndef ELEC_AS_CPP_BANK
#define ELEC_AS_CPP_BANK

#include <string>

/**
 * \brief Bank account class
 *
 */
class BankAccount {
 public:
  /**
   * \brief Construct a new Bank Account object
   *
   * \param owner the account's owner
   * \param account_number the account number
   * \param balance The current balance. Default 0.0.
   */
  BankAccount(std::string const& owner, std::string const& account_number,
              double balance = 0.0);

  /**
   * \brief Returns the Owner of the account
   *
   * \return BankAccount's owner as constant std::string
   */
  std::string GetOwner() const;

  /**
   * \brief Returns the BankAccount's number as a string.
   *
   * \return BankAccount's number as a constant std::string
   */
  std::string GetNumber() const;

  /**
   * \brief Returns the BankAccount's balance as a double.
   *
   * \return BankAccount's balance as double value
   */
  double GetBalance() const;

  /**
   * \brief Adds the specfied amount to the BankAccount's balance.
   *
   * \param amount The amount to be added to the balance
   */
  void Deposit(double amount);

  /**
   * \brief Withdraws the specfied amount from the BankAccount's balance
   *
   * \details If the parameter amount is bigger than the BankAccount's current
   * balance, no withdraw is made and the function returns false.
   * If the amount is smaller or equal to the current balance
   * the balance is reduced by the parameter amount and the function returns
   * true.
   *
   * \param amount The amount to be withdrawn
   *
   * \return true If the amount is smaller or equal to the current balance
   *              the balance is reduced by the specified amount
   * \return false if the specified amount is bigger than the BankAccount's
   *               current balance, no withdraw is made.
   */
  bool Withdraw(double amount);

  /* Print:
   * Prints the account information to the standard output stream.
   * The function takes no parameters and returns nothing.
   * The output format should be like the following (ends with a newline):
   Account num: <account number>, owned by: <owner>, balance: <balance> eur.
   */

  /**
   * \brief Prints the account information to the standard output stream.
   *
   * \details The output format is
   *
   * Account num: <account number>, owned by: <owner>, balance: <balance> eur.
   *
   * (ends with a newline).
   */
  void Print() const;

 private:
  std::string owner_;
  std::string account_number_;
  double balance_;
};

/**
 * \brief Transfers money from the source account to the target account.
 *
 * \details If the specified amount is bigger than the current balance of the
 * source account, the function returns false and no transfer is made. If the
 * amount is valid, that is smaller than the source account's current balance,
 * the function adds the parameter amount to the target account's balance,
 * reduces the amount from the source account's balance and returns true.
 *
 * \param source_account The source account from which the amount will be
 *        withdrawn
 * \param target_account The target account to which the amount will
 *                       be deposited
 * \param amount The amount that will be transferred from source
 *               account to destination account
 *
 * \return true if source account has enough balance to realize the transfer
 * \return false if source account has enough balance to realize the transfer
 */
bool Transfer(BankAccount& source_account, BankAccount& target_account,
              double amount);

#endif