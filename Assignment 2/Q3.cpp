#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "UQBAH KHAN"
#define STUDENT_ID "24K-0614"

class Vehical {
protected:
    int id;
    double maxSpeed;
    double capacity;
    double energyEfficiency;
    static int totalActiveDeliveries;

public:
    Vehical(int id, double speed, double cap, double efficiency)
        : id(id), maxSpeed(speed), capacity(cap), energyEfficiency(efficiency) {}

    virtual void calculateOptimalRoute(string destination) {
        cout << "Calculating standard route to " << destination << endl;
    }

    virtual double estimateDeliveryTime(double distance) {
        return distance / maxSpeed;
    }

    virtual void command(string cmd, int packageID) {
        if (cmd == "Deliver") {
            cout << "Standard delivery command for package " << packageID << endl;
            totalActiveDeliveries++;
        }
    }

    virtual void command(string cmd, int packageID, string urgencyLevel) {
        if (cmd == "Deliver") {
            cout << "Standard delivery command for package " << packageID << " with urgency " << urgencyLevel << endl;
            totalActiveDeliveries++;
        }
    }

    bool operator==(const Vehical& other) {
        return (maxSpeed == other.maxSpeed &&
                capacity == other.capacity &&
                energyEfficiency == other.energyEfficiency);
    }

    int getID() const { return id; }
    double getSpeed() const { return maxSpeed; }
    double getCapacity() const { return capacity; }
    double getEfficiency() const { return energyEfficiency; }

    static int getTotalActiveDeliveries() {
        return totalActiveDeliveries;
    }
};

int Vehical::totalActiveDeliveries = 0;

void resolveConflict(const Vehical& v1, const Vehical& v2, double distance, double weight, string urgency) {
    double v1Score = (v1.getSpeed() / distance * 0.5) + (v1.getCapacity() / weight * 0.3) + (urgency == "High" ? v1.getEfficiency() * 0.2 : 0);
    double v2Score = (v2.getSpeed() / distance * 0.5) + (v2.getCapacity() / weight * 0.3) + (urgency == "High" ? v2.getEfficiency() * 0.2 : 0);

    cout << "Conflict Resolution Results:\n";
    cout << "Vehicle " << v1.getID() << " score: " << v1Score << endl;
    cout << "Vehicle " << v2.getID() << " score: " << v2Score << endl;

    if (v1Score > v2Score)
        cout << "Selected vehicle: " << v1.getID() << endl;
    else if (v2Score > v1Score)
        cout << "Selected vehicle: " << v2.getID() << endl;
    else
        cout << "Both vehicles are equally suitable. Selecting first vehicle: " << v1.getID() << endl;
}

class RamzanDrone : public Vehical {
    int maxAltitude;

public:
    RamzanDrone(int id, double speed, double cap, double efficiency, int altitude)
        : Vehical(id, speed, cap, efficiency), maxAltitude(altitude) {}

    void calculateOptimalRoute(string destination) override {
        cout << "Calculating aerial route to " << destination << " with max altitude " << maxAltitude << endl;
    }

    double estimateDeliveryTime(double distance) override {
        return distance / (maxSpeed * 0.2);
    }

    void command(string cmd, int packageID) override {
        if (cmd == "Deliver") {
            cout << "Drone " << id << " initiating standard iftar meal delivery for package " << packageID << endl;
            totalActiveDeliveries++;
        }
    }

    void command(string cmd, int packageID, string urgencyLevel) override {
        if (cmd == "Deliver") {
            if (urgencyLevel == "High") {
                cout << "Drone " << id << " activating HIGH SPEED MODE for urgent iftar delivery of package " << packageID << endl;
            } else {
                cout << "Drone " << id << " delivering package " << packageID << " with urgency " << urgencyLevel << endl;
            }
            totalActiveDeliveries++;
        }
    }
};

class RamzanTimeShip : public Vehical {
    int timeTravelCapability;

    void validateHistoricalConsistency(int packageID) {
        cout << "Validating historical records for package " << packageID << "... OK" << endl;
    }

public:
    RamzanTimeShip(int id, double speed, double cap, double efficiency, int travelCap)
        : Vehical(id, speed, cap, efficiency), timeTravelCapability(travelCap) {}

    void calculateOptimalRoute(string destination) override {
        cout << "Calculating time-warp route to " << destination << " with capability " << timeTravelCapability << " years.\n";
    }

    void command(string cmd, int packageID) override {
        if (cmd == "Deliver") {
            cout << "TimeShip " << id << " initiating standard delivery for package " << packageID << endl;
            totalActiveDeliveries++;
        }
    }

    void command(string cmd, int packageID, string urgencyLevel) override {
        if (cmd == "Deliver") {
            if (urgencyLevel == "High") {
                cout << "TimeShip " << id << " checking history for urgent delivery of package " << packageID << endl;
                validateHistoricalConsistency(packageID);
            }
            cout << "TimeShip " << id << " delivering package " << packageID << " with urgency " << urgencyLevel << endl;
            totalActiveDeliveries++;
        }
    }
};

class RamzanHyperPod : public Vehical {
    string tunnelNetwork;

public:
    RamzanHyperPod(int id, double speed, double cap, double efficiency, string network)
        : Vehical(id, speed, cap, efficiency), tunnelNetwork(network) {}

    void calculateOptimalRoute(string destination) override {
        cout << "Calculating underground route via " << tunnelNetwork << " to " << destination << endl;
    }

    double estimateDeliveryTime(double distance) override {
        return distance > 50 ? distance / (maxSpeed * 1.5) : distance / maxSpeed;
    }

    void command(string cmd, int packageID) override {
        if (cmd == "Deliver") {
            cout << "HyperPod " << id << " initiating delivery through " << tunnelNetwork << " for package " << packageID << endl;
            totalActiveDeliveries++;
        }
    }

    void command(string cmd, int packageID, string urgencyLevel) override {
        if (cmd == "Deliver") {
            cout << "HyperPod " << id << " prioritizing delivery of package " << packageID << " with urgency " << urgencyLevel << endl;
            totalActiveDeliveries++;
        }
    }
};

int main() {
    cout << "Student: " << STUDENT_NAME << " | ID: " << STUDENT_ID << "\n\n";

    RamzanDrone drone(1, 100, 10, 0.9, 5000);
    RamzanTimeShip timeShip(2, 80, 15, 0.85, 200);
    RamzanHyperPod hyperPod(3, 120, 25, 0.8, "RedLine");

    drone.calculateOptimalRoute("Gulshan");
    timeShip.calculateOptimalRoute("Nazimabad");
    hyperPod.calculateOptimalRoute("North Karachi");

    cout << "\n--- Deliver Commands ---\n";
    drone.command("Deliver", 101);
    timeShip.command("Deliver", 102);
    hyperPod.command("Deliver", 103);

    drone.command("Deliver", 201, "High");
    timeShip.command("Deliver", 202, "High");
    hyperPod.command("Deliver", 203, "Medium");

    cout << "\n--- Delivery Time Estimates ---\n";
    cout << "Drone: " << drone.estimateDeliveryTime(20) << " mins\n";
    cout << "TimeShip: " << timeShip.estimateDeliveryTime(20) << " mins\n";
    cout << "HyperPod: " << hyperPod.estimateDeliveryTime(60) << " mins\n";

    cout << "\n--- Vehicle Comparison ---\n";
    cout << "Drone == TimeShip: " << (drone == timeShip ? "Yes" : "No") << endl;

    cout << "\n--- Conflict Resolution ---\n";
    resolveConflict(drone, hyperPod, 25, 5, "High");

    cout << "\nTotal active deliveries: " << Vehical::getTotalActiveDeliveries() << endl;

    return 0;
}
