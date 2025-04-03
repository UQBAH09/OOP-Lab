#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string address;
    string phoneNumber;
    string email;

public:
    Person(string name, int id, string addr, string phone, string mail)
        : name(name), id(id), address(addr), phoneNumber(phone), email(mail) {}

    virtual void displayInfo() const {
        cout << "\n--- Personal Info ---\n";
        cout << "Name: " << name << "\nID: " << id << "\nAddress: " << address
             << "\nPhone: " << phoneNumber << "\nEmail: " << email << endl;
    }

    virtual void updateInfo(string addr, string phone, string mail) {
        address = addr;
        phoneNumber = phone;
        email = mail;
    }

    string getName() const {
        return name;
    }

    virtual ~Person() {}
};

class Student : public Person {
    vector<string> coursesEnrolled;
    float GPA;
    int enrollmentYear;

public:
    Student(string name, int id, string addr, string phone, string mail,
            vector<string> courses, float gpa, int year)
        : Person(name, id, addr, phone, mail),
          coursesEnrolled(courses), GPA(gpa), enrollmentYear(year) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "--- Academic Info ---\n";
        cout << "Enrollment Year: " << enrollmentYear << "\nGPA: " << GPA << "\nCourses Enrolled: ";
        for (const auto& course : coursesEnrolled)
            cout << course << " ";
        cout << endl;
    }
};

class Professor : public Person {
    string department;
    vector<string> coursesTaught;
    double salary;

public:
    Professor(string name, int id, string addr, string phone, string mail,
              string dept, vector<string> courses, double sal)
        : Person(name, id, addr, phone, mail),
          department(dept), coursesTaught(courses), salary(sal) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "--- Faculty Info ---\n";
        cout << "Department: " << department << "\nCourses Taught: ";
        for (const auto& course : coursesTaught)
            cout << course << " ";
        cout << "\nSalary: $" << salary << endl;
    }
};

class Staff : public Person {
    string department;
    string position;
    double salary;

public:
    Staff(string name, int id, string addr, string phone, string mail,
          string dept, string pos, double sal)
        : Person(name, id, addr, phone, mail),
          department(dept), position(pos), salary(sal) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "--- Administrative Info ---\n";
        cout << "Department: " << department << "\nPosition: " << position
             << "\nSalary: $" << salary << endl;
    }
};

class Course {
    string courseId;
    string courseName;
    int credits;
    string instructor;
    string schedule;

public:
    Course(string id, string name, int cred, string instr, string sched)
        : courseId(id), courseName(name), credits(cred), instructor(instr), schedule(sched) {}

    void registerStudent(const Student& student) const {
        cout << "\nRegistering student " << student.getName() << " to course: " << courseName << endl;
    }

    void calculateGrades() const {
        cout << "Calculating grades for course: " << courseName << endl;
    }

    void displayCourseInfo() const {
        cout << "\n--- Course Info ---\n";
        cout << "Course ID: " << courseId << "\nCourse Name: " << courseName
             << "\nCredits: " << credits << "\nInstructor: " << instructor
             << "\nSchedule: " << schedule << endl;
    }
};

// ------------------ Main Function ------------------

int main() {
    // Creating a student
    vector<string> stuCourses = {"CS101", "MA101"};
    Student student("Alice Smith", 1001, "123 College Ave", "555-1234", "alice@univ.edu", stuCourses, 3.8, 2022);

    // Creating a professor
    vector<string> profCourses = {"CS101", "CS201"};
    Professor prof("Dr. John Doe", 2001, "45 Faculty Rd", "555-5678", "john.doe@univ.edu", "Computer Science", profCourses, 85000);

    // Creating a staff member
    Staff staff("Karen White", 3001, "78 Admin St", "555-9012", "karen@univ.edu", "HR", "Manager", 60000);

    // Creating a course
    Course course("CS101", "Introduction to Programming", 3, "Dr. John Doe", "MWF 10-11 AM");

    // Display all info
    student.displayInfo();
    prof.displayInfo();
    staff.displayInfo();
    course.displayCourseInfo();

    // Register student to course and calculate grades
    course.registerStudent(student);
    course.calculateGrades();

    return 0;
}
