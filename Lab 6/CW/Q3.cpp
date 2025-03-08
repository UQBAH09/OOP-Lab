#include <iostream>
#include <vector>
using namespace std;

// Base class for Employees
class Employee {
    int id;
    string name;
public:
    Employee(string name, int id) : name(name), id(id) {}
    string getName() { return name; }
    virtual ~Employee() {}
};

// Interface for taking orders
class IOrderTaker {
public:
    virtual void takeOrder() = 0;
    virtual ~IOrderTaker() {}
};

// Interface for preparing orders
class IOrderPreparer {
public:
    virtual void prepareOrder() = 0;
    virtual ~IOrderPreparer() {}
};

// Interface for billing
class IBiller {
public:
    virtual void generateBill() = 0;
    virtual ~IBiller() {}
};

// Waiter class implementing IOrderTaker
class Waiter : public Employee, public IOrderTaker {
public:
    Waiter(int id, string name) : Employee(name, id) {}
    void takeOrder() override {
        cout << getName() << " (Waiter) is taking an order..." << endl;
    }
};

// Chef class implementing IOrderPreparer
class Chef : public Employee, public IOrderPreparer {
public:
    Chef(int id, string name) : Employee(name, id) {}
    void prepareOrder() override {
        cout << getName() << " (Chef) is preparing an order..." << endl;
    }
};

// Cashier class implementing IBiller
class Cashier : public Employee, public IBiller {
public:
    Cashier(int id, string name) : Employee(name, id) {}
    void generateBill() override {
        cout << getName() << " (Cashier) is generating a bill..." << endl;
    }
};

// Manager class implementing both IOrderTaker and IBiller
class Manager : public Employee, public IOrderTaker, public IBiller {
public:
    Manager(int id, string name) : Employee(name, id) {}
    void takeOrder() override {
        cout << getName() << " (Manager) is taking an order..." << endl;
    }
    void generateBill() override {
        cout << getName() << " (Manager) is generating a bill..." << endl;
    }
};

// Base class for Menu items
class Menu {
protected:
    string item;
    double price;
public:
    Menu(string item, double price) : item(item), price(price) {}
    virtual double calculateCost() const = 0;
    virtual void showItem() const {
        cout << "Item: " << item << ", Price: $" << price;
    }
    virtual ~Menu() {}
    double getPrice() { return price; }
};

// Food menu class inheriting from Menu
class FoodMenu : public Menu {
public:
    FoodMenu(string item, double price) : Menu(item, price) {}
    double calculateCost() const override { return price; }
    void showItem() const override {
        Menu::showItem();
        cout << " (Food)" << endl;
    }
};

// Beverage menu class inheriting from Menu
class BeverageMenu : public Menu {
private:
    double taxRate = 0.1;
public:
    BeverageMenu(string item, double price) : Menu(item, price) {}
    double calculateCost() const override {
        return price + (price * taxRate);
    }
    void showItem() const override {
        Menu::showItem();
        cout << " (Beverage, includes 10% tax)" << endl;
    }
};

// Main function to test the implementation
int main() {
    // Creating employees
    Waiter waiter(101, "John");
    Chef chef(102, "Alice");
    Cashier cashier(103, "Robert");
    Manager manager(104, "Emma");

    // Demonstrating polymorphism using interface pointers
    vector<IOrderTaker*> orderTakers = { &waiter, &manager };
    vector<IOrderPreparer*> orderPreparers = { &chef };
    vector<IBiller*> billers = { &cashier, &manager };

    cout << "\n--- Order Taking ---\n";
    for (auto taker : orderTakers) {
        taker->takeOrder();
    }

    cout << "\n--- Order Preparation ---\n";
    for (auto preparer : orderPreparers) {
        preparer->prepareOrder();
    }

    cout << "\n--- Bill Generation ---\n";
    for (auto biller : billers) {
        biller->generateBill();
    }

    // Creating menu items
    FoodMenu pizza("Pizza", 15.99);
    BeverageMenu coke("Coke", 2.99);

    cout << "\n--- Menu Items ---\n";
    pizza.showItem();
    coke.showItem();

    cout << "\nTotal cost for " << pizza.getPrice() << " + " << coke.calculateCost() << " = $" << (pizza.calculateCost() + coke.calculateCost()) << endl;

    return 0;
}
