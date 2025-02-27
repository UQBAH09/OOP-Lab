#include <iostream>
#include <vector>
using namespace std;

class Student{
public:
    const int rollNumber;
    Student(int rollNo = 0): rollNumber(rollNo){}
};

int main(){
    int rollNumber;
    cout << "Enter roll number: ";
    cin >> rollNumber;

    Student s(rollNumber);

    cout << "Student Roll Number: " << s.rollNumber << endl;
}