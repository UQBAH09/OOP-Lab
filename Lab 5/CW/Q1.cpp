#include <iostream>
using namespace std;

class Engine {
    bool isRunning;

public:
    Engine() : isRunning(false) {}

    void start() {
        if (!isRunning) {
            isRunning = true;
            cout << "Engine started" << endl;
        } else {
            cout << "Engine is already running" << endl;
        }
    }

    void stop() {
        if (isRunning) {
            isRunning = false;
            cout << "Engine stopped" << endl;
        } else {
            cout << "Engine is already off" << endl;
        }
    }

    bool isEngineRunning() const {
        return isRunning;
    }
};

class Car {
    Engine engine; 

public:
    void startCar() {
        cout << "Starting the car..." << endl;
        engine.start();
    }

    void stopCar() {
        cout << "Stopping the car..." << endl;
        engine.stop();
    }
};

int main() {
    Car myCar;
    
    myCar.startCar(); 
    myCar.stopCar();  

    return 0;
}   