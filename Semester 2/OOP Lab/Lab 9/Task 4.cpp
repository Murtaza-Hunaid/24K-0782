#include <iostream>
#include <string>
using namespace std;

class PaymentMethod {
public:
    virtual bool processPayment(double amount) = 0; 
    virtual ~PaymentMethod() {}
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;

public:
    CreditCard(string number) : cardNumber(number) {}

    bool processPayment(double amount) override {
        if (cardNumber.length() == 16 && amount > 0) {
            cout << "Credit Card Payment of Rs." << amount << " processed successfully." << endl;
            return true; } 
        else {
            cout << "Credit Card Payment failed. Invalid card or amount." << endl;
            return false; }
    }
};

class DigitalWallet : public PaymentMethod {
private:
    double balance;

public:
    DigitalWallet(double initialBalance) : balance(initialBalance) {}

    bool processPayment(double amount) override {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Digital Wallet Payment of Rs." << amount << " successful. Remaining balance: Rs." << balance << endl;
            return true; } 
        else {
            cout << "Digital Wallet Payment failed. Insufficient balance or invalid amount." << endl;
            return false; }
    }
};

int main() {
    CreditCard card("1234567812345678");
    DigitalWallet wallet(50000.0);

    PaymentMethod* payment1 = &card;
    PaymentMethod* payment2 = &wallet;

    cout << "Processing Rs.25000 with Credit Card:" << endl;
    payment1->processPayment(25000.0);
    cout << "\nProcessing Rs.3000 with Digital Wallet:" << endl;
    payment2->processPayment(3000.0);
    cout << "\nProcessing Rs.8000 with Digital Wallet:" << endl;
    payment2->processPayment(8000.0); 
    return 0;
}
