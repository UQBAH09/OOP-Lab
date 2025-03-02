#include <iostream>
#include <string>

using namespace std;

class User {
    string name;
    int age;
    string licenseType;
    string contactNum;
    int userID;

public:
    User(string name = "", int age = 0, string licenseType = "Learner", string num = "", int ID = 0)
        : name(name), age(age), licenseType(licenseType), contactNum(num), userID(ID) {}

    void updateName(const string &n) { name = n; }
    void updateAge(int a) { age = a; }
    void updateType(const string &t) { licenseType = t; }
    void updateContactNum(const string &c) { contactNum = c; }

    string getName() const { return name; }
    string getType() const { return licenseType; }
};

class Vehicle {
    string model;
    float price;
    string eligibility;

public:
    Vehicle(string model = "", float price = 0.00, string eligibility = "Learner")
        : model(model), price(price), eligibility(eligibility) {}

    string getModel() const { return model; }
    string getEligibility() const { return eligibility; }

    void displayVehicle() const {
        cout << "Model: " << model << "\nPrice: $" << price << "/day\nEligibility: " << eligibility << "\n";
    }
};

class Rental {
    Vehicle **vehicles;
    int numOfVehicles;

public:
    Rental() {
        vehicles = nullptr;
        numOfVehicles = 0;
    }

    void addVehicle(Vehicle *vehicle) {
        // Create a new array with increased size
        Vehicle **temp = new Vehicle *[numOfVehicles + 1];

        // Copy existing vehicles into new array
        for (int i = 0; i < numOfVehicles; i++) {
            temp[i] = vehicles[i];
        }

        // Add new vehicle at the end
        temp[numOfVehicles] = vehicle;
        numOfVehicles++;

        // Delete old array and replace with the new one
        delete[] vehicles;
        vehicles = temp;

        cout << "Vehicle added successfully: " << vehicle->getModel() << endl;
    }

    int checkForVehicle(const string &model) const {
        for (int i = 0; i < numOfVehicles; i++) {
            if (vehicles[i]->getModel() == model) {
                return i;
            }
        }
        return -1;
    }

    void displayVehicles() const {
        cout << "\nAvailable Vehicles:\n";
        for (int i = 0; i < numOfVehicles; i++) {
            cout << "Vehicle " << i + 1 << ":\n";
            vehicles[i]->displayVehicle();
            cout << "-------------------\n";
        }
    }

    void rent(User &u, const string &model) {
        int vehicleIndex = checkForVehicle(model);
        if (vehicleIndex == -1) {
            cout << "No vehicle found with this model.\n";
            return;
        }

        if (vehicles[vehicleIndex]->getEligibility() != u.getType()) {
            cout << "You are not eligible to rent this vehicle due to license restrictions.\n";
            return;
        }

        cout << "Vehicle rented successfully!\n";
        vehicles[vehicleIndex]->displayVehicle();

        numOfVehicles --;
    }

    ~Rental() {
        for (int i = 0; i < numOfVehicles; i++) {
            delete vehicles[i];
        }
        delete[] vehicles;
    }
};

int main() {
    Rental rentalSystem;

    // Adding Vehicles to System
    rentalSystem.addVehicle(new Vehicle("Honda Civic", 50, "Full"));
    rentalSystem.addVehicle(new Vehicle("Toyota Corolla", 40, "Intermediate"));
    rentalSystem.addVehicle(new Vehicle("Scooter", 20, "Learner"));

    // Registering a User
    User user1("Ali Khan", 22, "Intermediate", "123-456-7890", 101);

    // Displaying Available Vehicles
    rentalSystem.displayVehicles();

    // Renting a Vehicle
    rentalSystem.rent(user1, "Toyota Corolla");

    return 0;
}
