#include <iostream>
using namespace std;

class Circle{
    private:
        float radius;

    public:
        Circle(float r): radius(r){}

        float getArea() {return 3.14*radius*radius;}
        float getPerimeter() {return 2*radius*3.14;}
};

int main(){
    Circle circle (4);

    cout << "Area of the circle: " << circle.getArea() << endl;
    cout << "Parameter of the circle: " << circle.getPerimeter() << endl;
}