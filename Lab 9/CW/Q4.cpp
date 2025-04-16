#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Flight {
private:
    string flightNumber;
    string departure;
    string arrival;
    int capacity;
    int bookedSeats;
    vector<string> passengerIDs;

    bool isBooked(const string& passengerID) const {
        for (const string& id : passengerIDs) {
            if (id == passengerID)
                return true;
        }
        return false;
    }

public:
    Flight(string number, string dep, string arr, int cap)
        : flightNumber(number), departure(dep), arrival(arr), capacity(cap), bookedSeats(0) {}

    bool bookSeat(const string& passengerID) {
        if (bookedSeats >= capacity) {
            cout << "Booking failed for " << passengerID << ". No available seats.\n";
            return false;
        }
        if (isBooked(passengerID)) {
            cout << "Booking failed. " << passengerID << " already has a seat.\n";
            return false;
        }
        passengerIDs.push_back(passengerID);
        bookedSeats++;
        cout << "Seat booked for " << passengerID << " on flight " << flightNumber << endl;
        return true;
    }

    bool cancelSeat(const string& passengerID) {
        for (size_t i = 0; i < passengerIDs.size(); ++i) {
            if (passengerIDs[i] == passengerID) {
                passengerIDs.erase(passengerIDs.begin() + i);
                bookedSeats--;
                cout << "Seat canceled for " << passengerID << " on flight " << flightNumber << endl;
                return true;
            }
        }
        cout << "Cancellation failed. " << passengerID << " has no seat booked.\n";
        return false;
    }

    bool upgradeSeat(const string& passengerID) {
        if (!isBooked(passengerID)) {
            cout << "Upgrade failed. " << passengerID << " has no seat booked.\n";
            return false;
        }
        cout << "Seat upgraded for " << passengerID << " on flight " << flightNumber << endl;
        return true;
    }

    void showStatus() const {
        cout << "Flight " << flightNumber << " [" << departure << " -> " << arrival << "]"
             << " | Booked Seats: " << bookedSeats << "/" << capacity << endl;
    }
};

class Passenger {
private:
    string id;
    string name;

public:
    Passenger(string pid, string pname) : id(pid), name(pname) {}

    void requestBooking(Flight& flight) {
        flight.bookSeat(id);
    }

    void requestCancellation(Flight& flight) {
        flight.cancelSeat(id);
    }

    void requestUpgrade(Flight& flight) {
        flight.upgradeSeat(id);
    }
};

int main() {
    Flight flight1("PK101", "Lahore", "Karachi", 2);
    Flight flight2("PK202", "Islamabad", "Dubai", 1);

    Passenger p1("P001", "Ali");
    Passenger p2("P002", "Sara");
    Passenger p3("P003", "John");

    p1.requestBooking(flight1);
    p2.requestBooking(flight1);
    p3.requestBooking(flight1);  // Should fail

    p2.requestCancellation(flight1);
    p3.requestBooking(flight1);  // Should now succeed

    p1.requestUpgrade(flight1);

    flight1.showStatus();
    flight2.showStatus();

    return 0;
}
