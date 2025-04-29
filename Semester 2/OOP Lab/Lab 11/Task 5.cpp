#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip> 

using namespace std;

class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException(const string& message) : runtime_error(message) {}
};

template <typename T>
class BankAccount {
private:
    T balance;

public:
    BankAccount(T initialBalance) : balance(initialBalance) {}

    void withdraw(T amount) {
        if (amount > balance) {
            T deficit = amount - balance;
            throw InsufficientFundsException("InsufficientFundsException - Deficit: $" + to_string(deficit)); }
        balance -= amount;
        cout << fixed << setprecision(2);
        cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
    }

    T getBalance() const {
        return balance;
    }

    void displayBalance() const {
        cout << fixed << setprecision(2);
        cout << "Balance: $" << balance << endl;
    }
};

int main() {
    try {
        BankAccount<double> account(500.00);
        account.displayBalance();
        cout << "Withdraw $600: ";
        account.withdraw(600.00); } 
    catch (const InsufficientFundsException& e) {
        cerr << e.what() << endl; }
    return 0;
}
