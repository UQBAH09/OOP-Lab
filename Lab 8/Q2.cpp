#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Shape {
protected:
    vector<int> position; // e.g., [x, y]
    string color;
    int borderThickness;
public:
    Shape(vector<int> pos, string color, int border)
        : position(pos), color(color), borderThickness(border) {}

    virtual void draw() {
        cout << "Rendering a Shape..." << endl;
    }

    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;

    virtual ~Shape() {} // Virtual destructor for polymorphic behavior
};

class Circle : public Shape {
    double radius;
public:
    Circle(vector<int> pos, string color, int border, double radius)
        : Shape(pos, color, border), radius(radius) {}

    void draw() override {
        cout << "Rendering a Circle..." << endl;
    }

    double calculateArea() override {
        return M_PI * pow(radius, 2);
    }

    double calculatePerimeter() override {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape {
    double width;
    double height;
public:
    Rectangle(vector<int> pos, string color, int border, double width, double height)
        : Shape(pos, color, border), width(width), height(height) {}

    void draw() override {
        cout << "Rendering a Rectangle..." << endl;
    }

    double calculateArea() override {
        return width * height;
    }

    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
    double base;
    double height;
public:
    Triangle(vector<int> pos, string color, int border, double base, double height)
        : Shape(pos, color, border), base(base), height(height) {}

    void draw() override {
        cout << "Rendering a Triangle..." << endl;
    }

    double calculateArea() override {
        return 0.5 * base * height;
    }

    double calculatePerimeter() override {
        // Assuming an isosceles triangle for simplicity
        double side = sqrt(pow(base / 2, 2) + pow(height, 2));
        return base + 2 * side;
    }
};

class Polygon : public Shape {
    int sides;
    double sideLength;
public:
    Polygon(vector<int> pos, string color, int border, int sides, double sideLength)
        : Shape(pos, color, border), sides(sides), sideLength(sideLength) {}

    void draw() override {
        cout << "Rendering a Polygon..." << endl;
    }

    double calculateArea() override {
        // Regular polygon area formula
        return (sides * pow(sideLength, 2)) / (4 * tan(M_PI / sides));
    }

    double calculatePerimeter() override {
        return sides * sideLength;
    }
};

int main() {
    // Create some shapes
    Shape* circle = new Circle({0, 0}, "Red", 2, 5.0); // radius = 5
    Shape* rectangle = new Rectangle({10, 10}, "Blue", 1, 4.0, 6.0); // width=4, height=6
    Shape* triangle = new Triangle({5, 5}, "Green", 2, 6.0, 4.0); // base=6, height=4
    Shape* polygon = new Polygon({2, 2}, "Purple", 1, 5, 3.0); // regular pentagon with side = 3

    // Store them in a vector for polymorphic access
    vector<Shape*> shapes = {circle, rectangle, triangle, polygon};

    // Loop through and draw + calculate
    for (Shape* shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->calculateArea() << endl;
        cout << "Perimeter: " << shape->calculatePerimeter() << endl;
        cout << "---------------------------" << endl;
    }

    // Free memory
    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
