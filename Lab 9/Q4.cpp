#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class Student {
protected:
    string name;
    int id;

public:
    void setStudentInfo(string n, int i) {
        name = n;
        id = i;
    }

    void displayStudentInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

    virtual double getTuition(const string& status, int creditHours) = 0; // Pure virtual

    virtual ~Student() {}
};

// Derived Class
class GraduateStudent : public Student {
private:
    string researchTopic;

public:
    void setResearchTopic(const string& topic) {
        researchTopic = topic;
    }

    string getResearchTopic() const {
        return researchTopic;
    }

    double getTuition(const string& status, int creditHours) override {
        double rate = 0;
        if (status == "undergraduate") {
            rate = 200;
        } else if (status == "graduate") {
            rate = 300;
        } else if (status == "doctoral") {
            rate = 400;
        } else {
            cout << "Invalid status provided.\n";
            return 0;
        }

        return creditHours * rate;
    }
};

// Demonstration
int main() {
    GraduateStudent grad;
    grad.setStudentInfo("Ali", 12345);
    grad.setResearchTopic("Artificial Intelligence");

    const string status = "graduate";
    const int credits = 9;

    cout << "\n--- Student Info ---" << endl;
    grad.displayStudentInfo();
    cout << "Research Topic: " << grad.getResearchTopic() << endl;
    cout << "Status: " << status << ", Credit Hours: " << credits << endl;

    const double tuition = grad.getTuition(status, credits);
    cout << "Calculated Tuition: $" << tuition << endl;

    return 0;
}
