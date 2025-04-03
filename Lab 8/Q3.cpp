#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Currency {
protected:
    double amount;
    string currencyCode;
    string currencySymbol;
    double exchangeRate;

public:
    Currency(double amt, string code, string symbol, double rate)
        : amount(amt), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    virtual double convertToBase() const {
        return amount * exchangeRate;
    }

    virtual double convertTo(const Currency& targetCurrency) const {
        double baseAmount = convertToBase();
        return baseAmount / targetCurrency.getExchangeRate();
    }

    virtual void displayCurrency() const {
        cout << fixed << setprecision(2);
        cout << "Amount: " << currencySymbol << amount << " (" << currencyCode << ")" << endl;
    }

    double getExchangeRate() const {
        return exchangeRate;
    }

    virtual ~Currency() {}
};

class Dollar : public Currency {
public:
    Dollar(double amt) : Currency(amt, "USD", "$", 1.0) {}

    void displayCurrency() const override {
        cout << fixed << setprecision(2);
        cout << "US Dollars: $" << amount << endl;
    }
};

class Euro : public Currency {
public:
    Euro(double amt) : Currency(amt, "EUR", "€", 1.08) {} // 1 EUR = 1.08 USD

    void displayCurrency() const override {
        cout << fixed << setprecision(2);
        cout << "Euros: €" << amount << endl;
    }
};

class Rupee : public Currency {
public:
    Rupee(double amt) : Currency(amt, "INR", "₹", 0.012) {} // 1 INR = 0.012 USD

    void displayCurrency() const override {
        cout << fixed << setprecision(2);
        cout << "Indian Rupees: ₹" << amount << endl;
    }
};

int main() {
    Dollar usd(100);
    Euro eur(100);
    Rupee inr(1000);

    usd.displayCurrency();
    eur.displayCurrency();
    inr.displayCurrency();

    cout << "\nConversion Examples:\n";

    cout << "100 USD to INR: ₹" << usd.convertTo(inr) << endl;
    cout << "100 EUR to USD: $" << eur.convertTo(usd) << endl;
    cout << "1000 INR to EUR: €" << inr.convertTo(eur) << endl;

    return 0;
}