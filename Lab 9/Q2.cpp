#include <iostream>
using namespace std;

// Abstract base class
class Car {
protected:
    string model;
    double price;

public:
    void setModel(string m) {
        model = m;
    }

    string getModel() const {
        return model;
    }

    double getPrice() const {
        return price;
    }

    // Abstract method
    virtual void setPrice(double p) = 0;

    // Virtual destructor (good practice for base classes)
    virtual ~Car() {}
};

// Derived class: Color
class Color : public Car {
private:
    string color;

public:
    void setColor(string c) {
        color = c;
    }

    string getColor() const {
        return color;
    }

    void setPrice(double p) override {
        // Maybe color adds a fixed cost
        price = p + 500;
    }
};

// Derived class: Company
class Company : public Car {
private:
    string companyName;

public:
    void setCompany(string name) {
        companyName = name;
    }

    string getCompany() const {
        return companyName;
    }

    void setPrice(double p) override {
        // Maybe different companies have markups
        price = p * 1.1;
    }
};

// Demonstration
int main() {
    Color car1;
    car1.setModel("Model X");
    car1.setColor("Red");
    car1.setPrice(30000);

    Company car2;
    car2.setModel("Model Y");
    car2.setCompany("Tesla");
    car2.setPrice(35000);

    cout << "--- Color Car ---" << endl;
    cout << "Model: " << car1.getModel() << endl;
    cout << "Color: " << car1.getColor() << endl;
    cout << "Price: $" << car1.getPrice() << endl;

    cout << "\n--- Company Car ---" << endl;
    cout << "Model: " << car2.getModel() << endl;
    cout << "Company: " << car2.getCompany() << endl;
    cout << "Price: $" << car2.getPrice() << endl;

    return 0;
}
