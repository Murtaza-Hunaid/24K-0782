#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    Account() {
        balance = 0.0;
    }

    Account(string acc_num, string acc_holder, double bal) {
        accountNumber = acc_num;
        accountHolderName = acc_holder;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << "\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds\n"; } 
        else {
            balance -= amount;
            cout << "Withdrawn: " << amount << "\n"; }
    }

    void checkBalance() const {
        cout << "Current Balance: " << balance << "\n";
    }
};

int main() {
    Account acc1("123456", "Bruce Wayne", 7800.0);
    Account acc2("789101", "Barry Allen", 700.0);
    acc1.checkBalance();
    acc1.deposit(200.0);
    acc1.checkBalance();
    acc1.withdraw(150.0);
    acc1.checkBalance();
    acc1.withdraw(1200.0); 
    acc2.checkBalance();
    acc2.deposit(300.0);
    acc2.checkBalance();
    return 0;
}
