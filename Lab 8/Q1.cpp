#include <iostream>
#include <string>

using namespace std;

class Account {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;
    string accountType;

public:
    Account(int accNo, string name, double bal, string type = "General")
        : accountNumber(accNo), accountHolderName(name), balance(bal), accountType(type) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " to " << accountType << " account." << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << " from " << accountType << " account." << endl;
        } else {
            cout << "Invalid or insufficient funds for withdrawal!" << endl;
        }
    }

    virtual double calculateInterest() const {
        return 0.0; // default
    }

    virtual void printStatement() const {
        cout << "\n--- Account Statement ---\n";
        cout << "Account Holder: " << accountHolderName
             << "\nAccount Number: " << accountNumber
             << "\nAccount Type: " << accountType
             << "\nCurrent Balance: $" << balance << endl;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(int accNo, string name, double bal, double rate, double minBal)
        : Account(accNo, name, bal, "Savings"), interestRate(rate), minimumBalance(minBal) {}

    void withdraw(double amount) override {
        if (balance - amount >= minimumBalance) {
            Account::withdraw(amount);
        } else {
            cout << "Cannot withdraw. Balance would fall below minimum required: $" << minimumBalance << endl;
        }
    }

    double calculateInterest() const override {
        return balance * interestRate;
    }

    void printStatement() const override {
        Account::printStatement();
        cout << "Interest Rate: " << interestRate * 100 << "%" << "\nMinimum Balance: $" << minimumBalance << endl;
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal, "Checking") {}

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            cout << "Checking withdrawal: $" << amount << " processed.\n";
        } else {
            cout << "Overdraft not allowed in Checking Account.\n";
        }
    }

    void printStatement() const override {
        Account::printStatement();
        cout << "Note: No interest for Checking Accounts." << endl;
    }
};

class FixedDepositAccount : public Account {
    int maturityMonths;
    double fixedInterestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int maturity, double rate)
        : Account(accNo, name, bal, "Fixed Deposit"),
          maturityMonths(maturity), fixedInterestRate(rate) {}

    void withdraw(double amount) override {
        cout << "Withdrawals not allowed until maturity of " << maturityMonths << " months." << endl;
    }

    double calculateInterest() const override {
        return balance * fixedInterestRate * (maturityMonths / 12.0);
    }

    void printStatement() const override {
        Account::printStatement();
        cout << "Maturity: " << maturityMonths << " months"
             << "\nFixed Interest Rate: " << fixedInterestRate * 100 << "%" << endl;
    }
};

int main() {
    SavingsAccount savings(101, "Alice", 5000.0, 0.04, 1000.0);
    CheckingAccount checking(102, "Bob", 2000.0);
    FixedDepositAccount fixed(103, "Charlie", 10000.0, 12, 0.06);

    // Interactions
    savings.deposit(500);
    savings.withdraw(4700);
    savings.printStatement();
    cout << "Interest Earned: $" << savings.calculateInterest() << endl;

    checking.withdraw(500);
    checking.printStatement();

    fixed.withdraw(1000); // should be blocked
    fixed.printStatement();
    cout << "Interest Earned: $" << fixed.calculateInterest() << endl;

    return 0;
}
