#include <iostream>
#include <string>
using namespace std;

class Currency {
protected:
    double amount;
    string currencyCode;
    string currencySymbol;
    double exchangeRate;

public:
    Currency(double amt, string code, string symbol, double rate = 1.0) : amount(amt), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    virtual double convertToBase() {
        return amount * exchangeRate;
    }

    virtual double convertTo(Currency &targetCurrency) {
        double baseAmount = convertToBase();
        return baseAmount / targetCurrency.exchangeRate;
    }

    virtual void displayCurrency() {
        cout << currencySymbol << amount << " (" << currencyCode << ")" << endl;
    }
};

class Dollar : public Currency {
public:
    Dollar(double amt, double rate = 1.0) : Currency(amt, "USD", "$", rate) {}

    double convertToBase() {
        return amount * exchangeRate;
    }

    void displayCurrency() {
        cout << currencySymbol << amount << " " << currencyCode << endl;
    }
};

class Euro : public Currency {
public:
    Euro(double amt, double rate = 1.0) : Currency(amt, "EUR", "€", rate) {}

    double convertToBase() {
        return amount * exchangeRate;
    }

    void displayCurrency() {
        cout << currencySymbol << amount << " " << currencyCode << endl;
    }
};

class Rupee : public Currency {
public:
    Rupee(double amt, double rate = 1.0) : Currency(amt, "PKR", "Rs.", rate) {}

    double convertToBase() {
        return amount * exchangeRate;
    }

    void displayCurrency() {
        cout << currencySymbol << amount << " " << currencyCode << endl;
    }
};

int main() {
    Dollar usd(100, 1.0);
    Euro eur(50, 1.1);
    Rupee pkr(5000, 0.0036);
    usd.displayCurrency();
    eur.displayCurrency();
    pkr.displayCurrency();
    double usdToEur = usd.convertTo(eur);
    double eurToPkr = eur.convertTo(pkr);
    cout << "USD to EUR: " << usdToEur << endl;
    cout << "EUR to PKR: " << eurToPkr << endl;
    return 0;
}
