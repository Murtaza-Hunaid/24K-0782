#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    string accountNumber;
    double balance;
    string accountHolderName;
    string accountType;

public:
    Account(string accNum, double bal, string holderName, string accType = "")
        : accountNumber(accNum), balance(bal), accountHolderName(holderName), accountType(accType) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount; } 
        else {
            cout << "Deposit amount must be positive" << endl; }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount; } 
        else {
            cout << "Insufficient balance or invalid amount" << endl; }
    }

    virtual void calculateInterest() {
        cout << "Interest calculation is not defined for this account type" << endl;
    }

    virtual void printStatement() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    void getAccountInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, double bal, string holderName, double rate) : Account(accNum, bal, holderName, "Savings"), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100);
        cout << "Interest on Savings Account: Rs. " << interest << endl;
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }

    void withdraw(double amount) override {
        if (amount <= balance && (balance - amount) >= 100) {
            balance -= amount; } 
        else {
            cout << "Withdrawal failed. Minimum balance of Rs. 100 must be maintained." << endl;
        }
    }
};

class CheckingAccount : public Account {
private:
    double minimumBalance;

public:
    CheckingAccount(string accNum, double bal, string holderName, double minBal) : Account(accNum, bal, holderName, "Checking"), minimumBalance(minBal) {}

    void calculateInterest() override {
        cout << "Checking Account does not earn interest" << endl;
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Minimum Balance: Rs. " << minimumBalance << endl;
    }

    void withdraw(double amount) override {
        if (amount <= balance && (balance - amount) >= minimumBalance) {
            balance -= amount; } 
        else {
            cout << "Withdrawal failed. Minimum balance of Rs. " << minimumBalance << " must be maintained." << endl; }
    }
};

class FixedDepositAccount : public Account {
private:
    double fixedInterestRate;
    string maturityDate;

public:
    FixedDepositAccount(string accNum, double bal, string holderName, double rate, string maturity) : Account(accNum, bal, holderName, "Fixed Deposit"), fixedInterestRate(rate), maturityDate(maturity) {}

    void calculateInterest() override {
        double interest = balance * (fixedInterestRate / 100);
        cout << "Interest on Fixed Deposit: Rs. " << interest << endl;
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Fixed Interest Rate: " << fixedInterestRate << "%" << endl;
        cout << "Maturity Date: " << maturityDate << endl;
    }

    void withdraw(double amount) override {
        cout << "Withdrawal is not allowed before maturity date." << endl;
    }
};

int main() {
    SavingsAccount savings("7820", 10000.0, "Murtaza", 5.0);
    CheckingAccount checking("6560", 1500.0, "Adnan", 200.0);
    FixedDepositAccount fd("6510", 5000.0, "Turab", 7.0, "04-12-2025");
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.calculateInterest();
    savings.printStatement();
    checking.deposit(1000.0);
    checking.withdraw(1300.0);
    checking.calculateInterest();
    checking.printStatement();
    fd.deposit(2000.0);
    fd.withdraw(3000.0);
    fd.calculateInterest();
    fd.printStatement();
    return 0;
}
