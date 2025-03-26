#include <iostream>
using namespace std;

class Account {
    string accountNumber, accountHolder;
    double balance;
public:
    Account(string accNum, string accHolder, double bal) : accountNumber(accNum), accountHolder(accHolder), balance(bal) {}
    Account operator+(const Account &a) {
        return Account(accountNumber, accountHolder, balance + a.balance);
    }
    Account &operator=(double amount) {
        balance = amount;
        return *this;
    }
    bool operator>(const Account &a) {
        return balance > a.balance;
    }
    friend ostream &operator<<(ostream &out, const Account &a) {
        out << "Account Number: " << a.accountNumber << " | Holder: " << a.accountHolder << " | Balance: $" << a.balance;
        return out;
    }
    void updateBalance(double amount) {
        balance = amount;
    }
    double getBalance() const {
        return balance;
    }
    string getHolder() const {
        return accountHolder;
    }
};

int main() {
    Account a1("101", "Shafique Rehman", 5000.0), a2("102", "Talha", 3000.0);
    Account total = a1 + a2;
    cout << "Total Balance (After Addition): " << total.getBalance() << endl;
    
    a1.updateBalance(3000);
    a2.updateBalance(5000);
    
    cout << "After Transfer:" << endl;
    cout << a1.getHolder() << "'s New Balance: " << a1.getBalance() << endl;
    cout << a2.getHolder() << "'s New Balance: " << a2.getBalance() << endl;
    
    cout << "Comparison:" << endl;
    if (a1 > a2)
        cout << a1.getHolder() << " has more balance than " << a2.getHolder() << "." << endl;
    else
        cout << a1.getHolder() << " has less balance than " << a2.getHolder() << "." << endl;
    
    cout << "Final Account Details:" << endl;
    cout << a1 << endl;
    cout << a2 << endl;
    
    return 0;
}
