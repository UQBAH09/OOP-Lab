#include <iostream>
using namespace std;

class Vehical{
    float price;
public:
    Vehical(float price): price(price){}
    float getPrice()const{return price;}

    void display(){
        cout << "Price: " << price << endl;
    }
};

class Car: public Vehical{
    int seatingCapacity;
    int numOfDoors;
    string fuleType;
public:
    Car(int seatingCapacity, int numOfDoors, string fuleType, float price): Vehical(price), seatingCapacity(seatingCapacity), numOfDoors(numOfDoors), fuleType(fuleType){}
    void display(){
        Vehical::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Number of Doors: " << numOfDoors << endl;
        cout << "Fuel Type: " << fuleType << endl;
    }
};

class MotorCycle: public Vehical{
    int numOfCylenders;
    int numOfGears;
    int numOfWheels;
public:
    MotorCycle(int numOfCylenders,int numOfGears, int numOfWheels, float price): Vehical(price), numOfCylenders(numOfCylenders), numOfGears(numOfGears), numOfWheels(numOfWheels){}
    void display(){
        Vehical::display();
        cout << "Number of Cylenders: " << numOfCylenders << endl;
        cout << "Number of Gears: " << numOfGears << endl;
        cout << "Number of Wheels: " << numOfWheels << endl;
    }
};

class Audi: public Car{
    string model;
public:
    Audi(string model, int seatingCapacity, int numOfDoors, string fuleType, float price): Car(seatingCapacity,numOfDoors,fuleType,price), model(model){}
    
    void display(){
        cout << "Model: " << model << endl;
        Car::display();
    }
};

class Yamaha : public MotorCycle{
    string makeType;

public:
    Yamaha(string makeType, int numOfCylenders,int numOfGears, int numOfWheels, float price): MotorCycle(numOfCylenders, numOfGears, numOfWheels, price), makeType(makeType){}
    void display(){
        cout << "Make Type: " << makeType << endl;
        MotorCycle::display();
    }
};

int main() {
    // Creating an Audi car
    Audi myAudi("A6", 5, 4, "Petrol", 60000);
    
    // Creating a Yamaha motorcycle
    Yamaha myYamaha("Sport", 2, 6, 2, 15000);

    cout << "=== Audi Car Details ===" << endl;
    myAudi.display();

    cout << "\n=== Yamaha Motorcycle Details ===" << endl;
    myYamaha.display();

    return 0;
}