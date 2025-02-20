#include <iostream>
using namespace std;

class Account {
private:
    int balance;

public:
    Account(int bal = 0) : balance(bal) {}

    void credit(int amount) {
        if (amount >= 0) {
            balance += amount;
            cout << "Amount credited: " << amount << endl;
        } else {
            cout << "Invalid credit amount!" << endl;
        }
    }

    void debit(int amount) {
        if (amount > balance) {
            cout << "Debit amount exceeded account balance!" << endl;
        } else {
            balance -= amount;
            cout << "Amount debited: " << amount << endl;
        }
    }

    int getBalance() const { return balance; }
};

int main() {
    int initialBalance;
    cout << "Enter initial account balance: ";
    cin >> initialBalance;

    if (initialBalance < 0) {
        cout << "Invalid initial balance! Setting balance to 0." << endl;
        initialBalance = 0;
    }

    Account myAccount(initialBalance);

    int choice, amount;
    do {
        cout << "\n1. Credit\n2. Debit\n3. Check Balance\n4. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter amount to credit: ";
                cin >> amount;
                myAccount.credit(amount);
                break;

            case 2:
                cout << "Enter amount to debit: ";
                cin >> amount;
                myAccount.debit(amount);
                break;

            case 3:
                cout << "Current balance: " << myAccount.getBalance() << endl;
                break;

            case 4:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
