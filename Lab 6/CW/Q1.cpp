#include <iostream>
#include <vector>
using namespace std;

class BankAccount {
protected:
    int accountNum;
    float balance;
    bool freeze;
    float limit;

public:
    BankAccount(int accNum, float initialBalance, float withdrawalLimit)
        : accountNum(accNum), balance(initialBalance), freeze(false), limit(withdrawalLimit) {}

    int getAccountNum() { return accountNum; }
    float getBalance() { return balance; }
    bool isFrozen() { return freeze; }

    void setLimit(float l) { limit = l; }

    void deposit(float amount) {
        if (amount > 0 && !freeze) {
            balance += amount;
            cout << "Deposited: $" << amount << " | New Balance: $" << balance << endl;
        } else {
            cout << "Deposit failed. Account frozen or invalid amount." << endl;
        }
    }

    void withdraw(float amount) {
        if (amount > 0 && amount <= balance && !freeze && amount <= limit) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << " | New Balance: $" << balance << endl;
        } else {
            cout << "Withdrawal failed. Check balance, freeze status, or limit." << endl;
        }
    }

    void freezeAccount(bool status) {
        freeze = status;
        cout << "Account " << (status ? "frozen." : "unfrozen.") << endl;
    }
};

class SavingAccount : public BankAccount {
    float interestRate;

public:
    SavingAccount(int accNum, float initialBalance, float withdrawalLimit, float rate)
        : BankAccount(accNum, initialBalance, withdrawalLimit), interestRate(rate) {}

    void addInterest() {
        if (!freeze) {
            float interest = balance * (interestRate / 100);
            deposit(interest);
            cout << "Interest added: $" << interest << " | New Balance: $" << balance << endl;
        } else {
            cout << "Interest addition failed. Account is frozen." << endl;
        }
    }
};

class CheckingAccount : public BankAccount {
    float overdraftLimit;

public:
    CheckingAccount(int accNum, float initialBalance, float withdrawalLimit, float overdraft)
        : BankAccount(accNum, initialBalance, withdrawalLimit), overdraftLimit(overdraft) {}

    void withdraw(float amount) {
        if (amount > 0 && amount <= (balance + overdraftLimit) && !freeze) {
            if (amount > balance) {
                cout << "Warning: Overdraft used!" << endl;
            }
            balance -= amount;
            cout << "Withdrawn: $" << amount << " | New Balance: $" << balance << endl;
        } else {
            cout << "Withdrawal failed. Check balance, overdraft limit, or freeze status." << endl;
        }
    }
};

class BusinessAccount : public BankAccount {
    float corporateTax;

public:
    BusinessAccount(int accNum, float initialBalance, float withdrawalLimit, float tax)
        : BankAccount(accNum, initialBalance, withdrawalLimit), corporateTax(tax) {}

    void deposit(float amount) {
        if (amount > 0 && !freeze) {
            float taxAmount = amount * (corporateTax / 100);
            float finalDeposit = amount - taxAmount;
            balance += finalDeposit;
            cout << "Deposited: $" << finalDeposit << " (Tax Deducted: $" << taxAmount << ") | New Balance: $" << balance << endl;
        } else {
            cout << "Deposit failed. Account frozen or invalid amount." << endl;
        }
    }
};

class Customer {
    string name;
    vector<BankAccount*> accounts;

public:
    Customer(string customerName) : name(customerName) {}

    void addAccount(BankAccount* account) {
        accounts.push_back(account);
    }

    void depositAmount(int accNum, float amount) {
        for (auto acc : accounts) {
            if (acc->getAccountNum() == accNum) {
                acc->deposit(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void withdrawAmount(int accNum, float amount) {
        for (auto acc : accounts) {
            if (acc->getAccountNum() == accNum) {
                acc->withdraw(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }
};

class Employee {
public:
    int id;
    string name;

    Employee(int empId, string empName) : id(empId), name(empName) {}
};

class Teller : public Employee {
public:
    Teller(int empId, string empName) : Employee(empId, empName) {}

    void freezeAccount(BankAccount& account) {
        account.freezeAccount(true);
    }

    void unfreezeAccount(BankAccount& account) {
        account.freezeAccount(false);
    }

    void depositAmount(BankAccount& account, float amount) {
        account.deposit(amount);
    }

    void withdrawAmount(BankAccount& account, float amount) {
        account.withdraw(amount);
    }
};

class Manager : public Employee {
public:
    Manager(int empId, string empName) : Employee(empId, empName) {}

    void freezeAccount(BankAccount& account) {
        account.freezeAccount(true);
    }

    void unfreezeAccount(BankAccount& account) {
        account.freezeAccount(false);
    }

    void depositAmount(BankAccount& account, float amount) {
        account.deposit(amount);
    }

    void withdrawAmount(BankAccount& account, float amount) {
        account.withdraw(amount);
    }

    void setLimit(BankAccount& account, float limit) {
        account.setLimit(limit);
        cout << "New withdrawal limit set: $" << limit << endl;
    }
};

int main() {
    // Creating accounts
    SavingAccount saveAcc(1001, 5000, 1000, 2.5);
    CheckingAccount checkAcc(1002, 3000, 1500, 500);
    BusinessAccount bizAcc(1003, 10000, 5000, 10);

    // Creating customer and linking accounts
    Customer cust("Alice");
    cust.addAccount(&saveAcc);
    cust.addAccount(&checkAcc);
    cust.addAccount(&bizAcc);

    // Performing transactions
    cout << "\n-- Customer Transactions --\n";
    cust.depositAmount(1001, 1000);
    cust.withdrawAmount(1002, 3500);  // Uses overdraft
    cust.depositAmount(1003, 2000);  // Corporate tax applied

    // Teller Operations
    cout << "\n-- Teller Transactions --\n";
    Teller teller(101, "John");
    teller.freezeAccount(checkAcc);
    teller.depositAmount(checkAcc, 500); // Should fail since account is frozen
    teller.unfreezeAccount(checkAcc);
    teller.depositAmount(checkAcc, 500); // Should succeed

    // Manager Operations
    cout << "\n-- Manager Transactions --\n";
    Manager manager(102, "Sophia");
    manager.setLimit(bizAcc, 7000);  // Adjusting withdrawal limit
    manager.withdrawAmount(bizAcc, 6000); // Should succeed within limit

    return 0;
}
