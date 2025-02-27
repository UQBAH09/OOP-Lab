#include <iostream>
using namespace std;
class Car
{
    string engine;
    int horsePower;
    int seating_capacity;
    int no_of_speaker;

public:
    Car(string e, int h, int s, int n) : engine(e), horsePower(h), seating_capacity(s), no_of_speaker(n) {}

    Car updateCar(string e, int h, int s, int n) const
    {
        return Car(e, h, s, n);
    };

    void display()
    {
        cout << "Engine: " << engine << endl;
        cout << "Horse Power: " << horsePower << endl;
        cout << "Seating Capacity: " << seating_capacity << endl;
        cout << "No of Speaker: " << no_of_speaker << endl;
    }
};

#include <iostream>
using namespace std;

int main()
{
    Car myCar("V8", 400, 5, 6);

    cout << "Initial Car Details:" << endl;
    myCar.display();

    Car updatedCar = myCar.updateCar("V6", 350, 4, 8);

    cout << "\nUpdated Car Details:" << endl;
    updatedCar.display();

    return 0;
}