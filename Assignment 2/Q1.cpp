#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "UQBAH KHAN"
#define STUDENT_ID "24K-0614"

// ============================ Stop Class ============================
class Bus; // Forward declaration

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

    void getStopDetails() const;
};

// ============================ Route Class ============================
class Route {
    int routeID;
    Stop* stops[10];
    int stopCount;

public:
    Route(int id = -1) : routeID(id), stopCount(0) {
        for (int i = 0; i < 10; i++) stops[i] = nullptr;
    }

    ~Route() {
        for (int i = 0; i < stopCount; i++) stops[i] = nullptr;
    }

    int getRouteID() const { return routeID; }

    void addStop(Stop* stop) {
        if (stopCount < 10) {
            stops[stopCount++] = stop;
            cout << "Stop added to route." << endl;
        } else {
            cout << "Route is full." << endl;
        }
    }

    void viewStops() const {
        cout << "Route " << routeID << " Stops:" << endl;
        for (int i = 0; i < stopCount; i++) {
            stops[i]->getStopDetails();
        }
    }

    Stop** getStops() { return stops; }
    int getTotalStops() const { return stopCount; }

    friend bool operator==(const Route& r1, const Route& r2);
};

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

    void assignRoute(Route* r) {
        route = r;
        for (int i = 0; i < route->getTotalStops(); i++) {
            route->getStops()[i]->setAssignedBus(this);
        }
        cout << "Route assigned to Bus " << busID << endl;
    }

    void displayBusInfo() const {
        cout << "Bus ID: " << busID << ", Driver: " << driverName << ", Max Capacity: " << maxCapacity << endl;
        if (route)
            route->viewStops();
        else
            cout << "No route assigned." << endl;
    }
};

// Define method now that Bus is fully declared
void Stop::getStopDetails() const {
    cout << "Stop ID: " << stopID << ", Location: " << location << endl;
    if (assignedBus)
        cout << "Assigned Bus ID: " << assignedBus->getBusID() << endl;
    else
        cout << "No bus assigned." << endl;
}

// ============================ Operator Overload ============================
bool operator==(const Route& r1, const Route& r2) {
    if (r1.stopCount != r2.stopCount) return false;
    for (int i = 0; i < r1.stopCount; i++) {
        if (r1.stops[i]->getStopID() != r2.stops[i]->getStopID())
            return false;
    }
    return true;
}

// ============================ Person Base Class ============================
class Person {
protected:
    int id;
    string name;
    bool transportCardActive;
    Stop* pickupStop;
    Stop* dropoffStop;

public:
    Person(int id, string name)
        : id(id), name(name), transportCardActive(false), pickupStop(nullptr), dropoffStop(nullptr) {}

    virtual ~Person() { pickupStop = dropoffStop = nullptr; }

    virtual void payTransportFee() = 0;
    virtual bool isFeePaid() const = 0;

    void activateCard() {
        if (isFeePaid()) {
            transportCardActive = true;
            cout << name << "'s card activated." << endl;
        } else {
            cout << "Fee not paid." << endl;
        }
    }

    void setPickupStop(Stop* s) { pickupStop = s; }
    void setDropoffStop(Stop* s) { dropoffStop = s; }

    virtual void viewTransportDetails() const {
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Pickup: " << (pickupStop ? pickupStop->getLocation() : "None") << endl;
        cout << "Dropoff: " << (dropoffStop ? dropoffStop->getLocation() : "None") << endl;
    }
};

// ============================ Derived Person Classes ============================
class Student : public Person {
    bool semesterFeePaid;

public:
    Student(int id, string name) : Person(id, name), semesterFeePaid(false) {}

    void paySemesterFee() {
        semesterFeePaid = true;
        cout << name << " paid semester fee." << endl;
    }

    void payTransportFee() override { paySemesterFee(); }
    bool isFeePaid() const override { return semesterFeePaid; }

    void tapCard() {
        if (transportCardActive) cout << name << " tapped in." << endl;
        else cout << name << "'s card not activated." << endl;
    }
};

class Teacher : public Person {
    bool monthlyFeePaid;

public:
    Teacher(int id, string name) : Person(id, name), monthlyFeePaid(false) {}

    void payMonthlyFee() {
        monthlyFeePaid = true;
        cout << name << " paid monthly fee." << endl;
    }

    void payTransportFee() override { payMonthlyFee(); }
    bool isFeePaid() const override { return monthlyFeePaid; }
};

class Staff : public Person {
    bool monthlyFeePaid;

public:
    Staff(int id, string name) : Person(id, name), monthlyFeePaid(false) {}

    void payMonthlyFee() {
        monthlyFeePaid = true;
        cout << name << " paid monthly fee." << endl;
    }

    void payTransportFee() override { payMonthlyFee(); }
    bool isFeePaid() const override { return monthlyFeePaid; }
};

// ============================ Main ============================
int main() {
    cout << "Student: " << STUDENT_NAME << " | ID: " << STUDENT_ID << endl;

    cout << "--- FAST Transport System ---" << endl << endl;

    Stop stop1(101, "Main Gate");
    Stop stop2(102, "Library");
    Stop stop3(103, "Hostel");

    Route route1(1);
    route1.addStop(&stop1);
    route1.addStop(&stop2);
    route1.addStop(&stop3);

    Bus bus1(501, "Ali", 50);
    bus1.assignRoute(&route1);

    Student s1(301, "Saad");
    s1.payTransportFee();
    s1.activateCard();
    s1.setPickupStop(&stop1);
    s1.setDropoffStop(&stop3);
    s1.tapCard();

    Teacher t1(201, "Mr. Bilal");
    t1.payTransportFee();
    t1.activateCard();
    t1.setPickupStop(&stop2);
    t1.setDropoffStop(&stop1);

    Staff st1(401, "Zara");
    st1.payTransportFee();
    st1.activateCard();
    st1.setPickupStop(&stop3);
    st1.setDropoffStop(&stop2);

    cout << endl << "--- Transport Details ---" << endl;
    s1.viewTransportDetails();
    t1.viewTransportDetails();
    st1.viewTransportDetails();

    cout << endl << "--- Bus Info ---" << endl;
    bus1.displayBusInfo();

    return 0;
}
