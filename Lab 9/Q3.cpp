#include <iostream>
#include <string>
using namespace std;

// Base Class
class Person {
protected:
    string name;
    int age;

public:
    virtual void getData() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
    }

    virtual void displayData() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual void bonus() const {
        cout << "No bonus for base person class.\n";
    }

    virtual ~Person() {}
};

// Derived Class: Admin
class Admin : virtual public Person {
protected:
    double salary;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Admin Salary: ";
        cin >> salary;
    }

    void displayData() const override {
        Person::displayData();
        cout << "Admin Salary: $" << salary << endl;
    }

    void bonus() const override {
        cout << "Admin Bonus: $" << (0.15 * salary) << endl;
    }
};

// Derived Class: Account
class Account : virtual public Person {
protected:
    double allowance;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Account Allowance: ";
        cin >> allowance;
    }

    void displayData() const override {
        Person::displayData();
        cout << "Account Allowance: $" << allowance << endl;
    }

    void bonus() const override {
        cout << "Account Bonus: $" << (0.10 * allowance) << endl;
    }
};

// Derived Class: Master (inherits from both Admin and Account)
class Master : public Admin, public Account {
public:
    void getData() override {
        Admin::getData();  // Will call Person::getData through Admin
        cout << "Enter Account Allowance (for Master): ";
        cin >> allowance;
    }

    void displayData() const override {
        Person::displayData();
        cout << "Master Salary: $" << salary << ", Allowance: $" << allowance << endl;
    }

    void bonus() const override {
        double totalBonus = 0.15 * salary + 0.10 * allowance;
        cout << "Master Bonus: $" << totalBonus << endl;
    }
};

// Demonstration
int main() {
    Person* ptr;

    Master masterObj;
    cout << "--- Enter Master Employee Data ---\n";
    ptr = &masterObj;
    ptr->getData();

    cout << "\n--- Display Master Employee Info ---\n";
    ptr->displayData();

    cout << "\n--- Calculating Bonus ---\n";
    ptr->bonus();

    return 0;
}
