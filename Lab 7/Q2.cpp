#include <iostream>
#include <vector>

using namespace std;

class Shape{
    float area;
public:
    Shape(int a): area(a){}

    float getArea(){return area;}

    Shape operator+(Shape& s){
        return Shape(area + s.area);
    }
};

int main(){
    Shape shape1(10);
    Shape shape2(30);
    
    Shape s3 = shape1 + shape2;
    cout << "Area of shape 1 + shape 2: " << s3.getArea() << endl;
}