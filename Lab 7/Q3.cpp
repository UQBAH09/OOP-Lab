#include <iostream>
using namespace std;

class Person {
protected:
    int empID;

public:
    virtual void getData() {
        cout << "Enter Employee ID: ";
        cin >> empID;
    }

    virtual void displayData() const {
        cout << "Employee ID: " << empID << endl;
    }

    virtual ~Person() {}
};

class Admin : public Person {
private:
    string name;
    double monthlyIncome;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Admin Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Monthly Income: ";
        cin >> monthlyIncome;
    }

    void displayData() const override {
        Person::displayData();
        cout << "Name: " << name << endl;
        cout << "Monthly Income: $" << monthlyIncome << endl;
        cout << "Annual Bonus (5%): $" << bonus() << endl;
    }

    double bonus() const {
        return monthlyIncome * 0.05 * 12;
    }
};

class Accounts : public Person {
private:
    string name;
    double monthlyIncome;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Accounts Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Monthly Income: ";
        cin >> monthlyIncome;
    }

    void displayData() const override {
        Person::displayData();
        cout << "Name: " << name << endl;
        cout << "Monthly Income: $" << monthlyIncome << endl;
        cout << "Annual Bonus (5%): $" << bonus() << endl;
    }

    double bonus() const {
        return monthlyIncome * 0.05 * 12;
    }
};

int main() {
    Admin adminEmp;
    Accounts accountsEmp;

    cout << "Enter details for Admin:\n";
    adminEmp.getData();

    cout << "\nEnter details for Accounts:\n";
    accountsEmp.getData();

    cout << "\nAdmin Employee Details:\n";
    adminEmp.displayData();

    cout << "\nAccounts Employee Details:\n";
    accountsEmp.displayData();

    return 0;
}
