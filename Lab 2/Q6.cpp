#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct Subject
{
    string name;
};

struct Student
{
    int id;
    Subject subjects[5];
};

void displayStudents(vector<Student> &students)
{
    for (auto &student : students)
    {
        cout << "  Student ID: " << student.id << endl;
        cout << "  Subjects: ";
        for (auto &subject : student.subjects)
        {
            cout << subject.name << " ";
        }
        cout << "\n\n";
    }
}

void intialize(vector<Student> &students, char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Student s;
        s.id = atoi(argv[i * 6 + 1]);
        for (int j = 0; j < 5; j++)
        {
            s.subjects[j].name = argv[i * 6 + 2 + j];
        }
        students.push_back(s);
    }
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 6 != 0 || argc == 1)
    {
        cerr << "Insufficent arguments." << endl;
        return 1;
    }
    vector<Student> students;

    int n = (argc - 1) / 6;
    intialize(students, argv, n);

    cout << "Student Details:" << endl;
    cout << "-------------------" << endl;
    displayStudents(students);
}