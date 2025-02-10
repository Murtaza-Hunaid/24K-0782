#include <iostream>
#include <string>

using namespace std;

struct Account {
    int account_number;
    string owner_name;
    double balance;
};

void createAccount(Account &acc, int account_number, const string &owner_name, double initial_bal = 0) {
    acc.account_number = account_number;
    acc.owner_name = owner_name;
    acc.balance = initial_bal;
}

void deposit(Account &acc, double amount) {
    if (amount > 0) {
        acc.balance += amount;
        cout << "Deposit successful\n"; } 
	else {
        cout << "Invalid deposit amount\n"; }
}

void withdraw(Account &acc, double amount) {
    if (amount > 0) {
        if (amount <= acc.balance) {
            acc.balance -= amount;
            cout << "Withdrawal successful\n"; } 
		else {
            cout << "Insufficient balance\n"; } } 
	else {
        cout << "Invalid withdrawal amount\n"; }
}

void displayAccountDetails(const Account &acc) {
    cout << "Account Number: " << acc.account_number << "\n";
    cout << "Owner Name: " << acc.owner_name << "\n";
    cout << "Current Balance: " << acc.balance << "\n";
}

int main() {
    Account customer_account;
    int account_num;
    string owner_name;
    double initial_bal;
    double amount;

    cout << "Enter account number: ";
    cin >> account_num;
    cin.ignore(); 
    cout << "Enter owner's name: ";
    getline(cin, owner_name);
    cout << "Enter initial balance: ";
    cin >> initial_bal;
    createAccount(customer_account, account_num, owner_name, initial_bal);
    while (true) {
        int choice;
        cout << "\nChoose an operation:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Account Details\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter deposit amount: ";
            cin >> amount;
            deposit(customer_account, amount); } 
		else if (choice == 2) {
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            withdraw(customer_account, amount); } 
		else if (choice == 3) {
            displayAccountDetails(customer_account); } 
		else if (choice == 4) {
            cout << "Exiting program.\n";
            break; } 
		else {
            cout << "Invalid choice. Please try again.\n"; } }
    return 0;
}
