#include <iostream>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNum, string accHolder, double bal) {
        accountNumber = accNum;
        accountHolderName = accHolder;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        }
    }

    void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount accounts[3] = { BankAccount(782, "Murtaza", 5000.0), BankAccount(651, "Adnan", 2000.0), BankAccount(656, "Turab", 3000.0) };
    for (int i = 0; i < 3; i++) {
        accounts[i].display();
        accounts[i].deposit(500.0);
        accounts[i].display();
        accounts[i].withdraw(200.0);
        accounts[i].display(); }
    return 0;
}
