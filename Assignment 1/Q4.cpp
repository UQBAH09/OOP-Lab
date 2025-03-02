#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward Declarations
class Stop;
class Route;

// ============================ Bus Class ============================
class Bus {
    int busID;
    string driverName;
    int maxCapacity;
    Route* route;

public:
    Bus(int id, string driver, int capacity) : busID(id), driverName(driver), maxCapacity(capacity), route(nullptr) {}

    ~Bus() { route = nullptr; }

    int getBusID() const { return busID; }
    string getDriverName() const { return driverName; }

    void assignRoute(Route* r);

    void displayBusInfo() const;
};

// ============================ Stop Class ============================
class Stop {
    int stopID;
    string location;
    Bus* assignedBus;

public:
    Stop(int id = -1, string loc = "") : stopID(id), location(loc), assignedBus(nullptr) {}

    ~Stop() { assignedBus = nullptr; }

    int getStopID() const { return stopID; }
    string getLocation() const { return location; }
    void setAssignedBus(Bus* bus) { assignedBus = bus; }

    void getStopDetails() const {
        cout << "Stop ID: " << stopID << ", Location: " << location << endl;
        if (assignedBus)
            cout << "Assigned Bus ID: " << assignedBus->getBusID() << endl;
        else
            cout << "No bus assigned.\n";
    }
};

// ============================ Route Class ============================
class Route {
    int routeID;
    vector<Stop*> stops; // Using vector for dynamic management

public:
    Route(int id = -1) : routeID(id) {}

    ~Route() {
        stops.clear(); // Avoid dangling pointers
    }

    int getRouteID() const { return routeID; }

    void addStop(Stop* stop) {
        if (stops.size() < 10) {
            stops.push_back(stop);
            cout << "Stop added to route.\n";
        } else {
            cout << "Route is full.\n";
        }
    }

    void removeStop(int stopID) {
        for (auto it = stops.begin(); it != stops.end(); ++it) {
            if ((*it)->getStopID() == stopID) {
                stops.erase(it);
                cout << "Stop removed successfully.\n";
                return;
            }
        }
        cout << "Stop not found.\n";
    }

    void viewStops() const {
        cout << "Route " << routeID << " Stops:\n";
        for (auto stop : stops)
            stop->getStopDetails();
    }

    vector<Stop*>& getStops() { return stops; }
    int getTotalStops() const { return stops.size(); }
};

// ============================ Bus Methods ============================
void Bus::assignRoute(Route* r) {
    route = r;
    for (auto stop : route->getStops()) {
        stop->setAssignedBus(this);
    }
    cout << "Route assigned to Bus " << busID << endl;
}

void Bus::displayBusInfo() const {
    cout << "Bus ID: " << busID << ", Driver: " << driverName << ", Max Capacity: " << maxCapacity << endl;
    if (route)
        route->viewStops();
    else
        cout << "No route assigned.\n";
}

// ============================ Student Class ============================
class Student {
private:
    int studentID;
    string name;
    bool semesterFeePaid;
    bool transportCardActive;
    Stop* pickupStop;
    Stop* dropoffStop;

public:
    Student(int id, string name)
        : studentID(id), name(name), semesterFeePaid(false), transportCardActive(false), pickupStop(nullptr), dropoffStop(nullptr) {}

    ~Student() { pickupStop = dropoffStop = nullptr; }

    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    void setPickupStop(Stop* stop) { pickupStop = stop; }
    void setDropoffStop(Stop* stop) { dropoffStop = stop; }

    void registerForTransport() { cout << name << " has registered for transport.\n"; }
    void paySemesterFee() { semesterFeePaid = true; cout << name << " has paid the semester fee.\n"; }

    void activateCard() {
        if (semesterFeePaid) {
            transportCardActive = true;
            cout << "Transport card activated for " << name << ".\n";
        } else {
            cout << "Pay semester fee first.\n";
        }
    }

    void tapCard() {
        if (transportCardActive) {
            cout << name << " tapped the card. Attendance marked.\n";
        } else {
            cout << "Card not activated.\n";
        }
    }

    void viewTransportDetails() const {
        cout << "Student ID: " << studentID << ", Name: " << name << endl;
        cout << "Pickup Stop: " << (pickupStop ? pickupStop->getLocation() : "Not Assigned") << endl;
        cout << "Dropoff Stop: " << (dropoffStop ? dropoffStop->getLocation() : "Not Assigned") << endl;
    }
};

// ============================ Main Function ============================
int main() {
    // Create Stops
    Stop stop1(101, "Main Gate");
    Stop stop2(102, "Library");
    Stop stop3(103, "Hostel");

    // Create Route
    Route route1(1);
    route1.addStop(&stop1);
    route1.addStop(&stop2);
    route1.addStop(&stop3);

    // Create Bus and assign Route
    Bus bus1(501, "Ali", 50);
    bus1.assignRoute(&route1);

    // Create Student and register for transport
    Student student1(301, "Saad");
    student1.registerForTransport();
    student1.paySemesterFee();
    student1.activateCard();
    student1.setPickupStop(&stop1);
    student1.setDropoffStop(&stop3);
    student1.tapCard();

    // Display transport details
    student1.viewTransportDetails();
    bus1.displayBusInfo();

    return 0;
}
