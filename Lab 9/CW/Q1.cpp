#include <iostream>
#include <string>
using namespace std;

class Wallet {
private:
    double balance;
    double dailyDepositLimit;
    double dailyWithdrawalLimit;
    double depositToday;
    double withdrawalToday;

public:
    Wallet(double depositLimit, double withdrawalLimit) {
        balance = 0.0;
        depositToday = 0.0;
        withdrawalToday = 0.0;
        dailyDepositLimit = depositLimit;
        dailyWithdrawalLimit = withdrawalLimit;
    }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit must be positive.\n";
            return false;
        }

        if (depositToday + amount > dailyDepositLimit) {
            cout << "Deposit exceeds daily limit.\n";
            return false;
        }

        balance += amount;
        depositToday += amount;
        cout << "Deposited: $" << amount << endl;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal must be positive.\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }

        if (withdrawalToday + amount > dailyWithdrawalLimit) {
            cout << "Withdrawal exceeds daily limit.\n";
            return false;
        }

        balance -= amount;
        withdrawalToday += amount;
        cout << "Withdrawn: $" << amount << endl;
        return true;
    }

    double getBalance() const {
        return balance;
    }

    void resetDailyLimits() {
        depositToday = 0.0;
        withdrawalToday = 0.0;
    }
};

class User {
private:
    int ID;
    string name;
    Wallet wallet;

public:
    User(int id, string userName, double depositLimit, double withdrawLimit)
        : ID(id), name(userName), wallet(depositLimit, withdrawLimit) {}

    void deposit(double amount) {
        cout << name << " trying to deposit $" << amount << "...\n";
        wallet.deposit(amount);
    }

    void withdraw(double amount) {
        cout << name << " trying to withdraw $" << amount << "...\n";
        wallet.withdraw(amount);
    }

    void checkBalance() const {
        cout << name << "'s balance: $" << wallet.getBalance() << endl;
    }

    void newDay() {
        wallet.resetDailyLimits();
    }
};

int main() {
    User user1(101, "Alice", 500.0, 300.0);
    User user2(102, "Bob", 1000.0, 500.0);

    // Simulate transactions
    user1.deposit(200);
    user1.deposit(400);  // Should exceed limit
    user1.checkBalance();

    user1.withdraw(100);
    user1.withdraw(250); // Should exceed withdrawal limit
    user1.withdraw(500); // Should be blocked (insufficient)

    user1.checkBalance();

    cout << "\n--- New Day ---\n";
    user1.newDay();
    user1.deposit(300);  // Should work now
    user1.withdraw(200); // Should work now
    user1.checkBalance();

    cout << "\n--- Bob's Wallet ---\n";
    user2.deposit(600);
    user2.withdraw(100);
    user2.checkBalance();

    return 0;
}
