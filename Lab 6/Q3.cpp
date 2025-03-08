#include <iostream>
#include <string>
using namespace std;

class Student {
protected:
    string name;
    int rollNumber;
public:
    Student(string n, int r) : name(n), rollNumber(r) {}

    void displayStudentInfo() {
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
    }
};

class Marks : public Student {
protected:
    int numSubjects;
    int* marks;

public:
    Marks(string n, int r, int num) : Student(n, r), numSubjects(num) {
        marks = new int[numSubjects];
    }

    void setMarks(const int m[]) {
        for (int i = 0; i < numSubjects; i++) {
            marks[i] = m[i];
        }
    }

    void displayMarks() {
        cout << "Marks obtained:" << endl;
        for (int i = 0; i < numSubjects; i++) {
            cout << "Subject " << i + 1 << ": " << marks[i] << endl;
        }
    }

    ~Marks() {
        delete[] marks;
    }
};

class Result : public Marks {
private:
    int totalMarks;
    float averageMarks;

public:
    Result(string n, int r, int num) : Marks(n, r, num) {
        totalMarks = 0;
        averageMarks = 0.0;
    }

    void calculateResult() {
        totalMarks = 0;
        for (int i = 0; i < numSubjects; i++) {
            totalMarks += marks[i];
        }
        averageMarks = static_cast<float>(totalMarks) / numSubjects;
    }

    void displayResult() {
        cout << "Total Marks: " << totalMarks << endl;
        cout << "Average Marks: " << averageMarks << endl;
    }
};

// Main function (entry point)
int main() {
    // Constant values for student details and marks
    string name = "John Doe";
    int roll = 101;
    int numSubjects = 3;
    int marksArray[] = {85, 90, 78}; // Predefined marks

    // Creating object
    Result student(name, roll, numSubjects);
    student.setMarks(marksArray);
    student.calculateResult();

    // Display details
    cout << "\n---- Student Details ----\n";
    student.displayStudentInfo();
    cout << "\n---- Marks ----\n";
    student.displayMarks();
    cout << "\n---- Result ----\n";
    student.displayResult();

    return 0;
}
