#include <iostream>
using namespace std;

// Abstract Base Class
class Shape {
public:
    // Pure virtual function
    virtual double getArea() = 0;
};

// Derived Class: Rectangle
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double getArea() override {
        return length * width;
    }
};

// Derived Class: Triangle
class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double getArea() override {
        return 0.5 * base * height;
    }
};

// Demonstration
int main() {
    Shape* shape;

    Rectangle rect(5.0, 3.0);
    Triangle tri(4.0, 6.0);

    shape = &rect;
    cout << "Area of Rectangle: " << shape->getArea() << endl;

    shape = &tri;
    cout << "Area of Triangle: " << shape->getArea() << endl;

    return 0;
}
