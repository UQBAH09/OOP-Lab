#include <iostream>
#include <cstdlib>
using namespace std;

struct Employee
{
    int id;
    string name;
    int salary;
};

struct Organisation
{
    string name;
    string number;
    Employee emp;
};

void intailize(char *argv[], Organisation *org)
{
    (*org).name = argv[1];
    (*org).number = argv[2];

    (*org).emp.id = atoi(argv[3]);
    (*org).emp.name = argv[4];
    (*org).emp.salary = atoi(argv[5]);
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        cout << "Too little arguments." << endl;
        return 1;
    }

    Organisation org;

    intailize(argv, &org);

    cout << "The size of structure organisation: " << sizeof(org) << endl;
    cout << "Organisation Name: " << org.name << endl;
    cout << "Organisation Number: " << org.number << endl;
    cout << "Employee id: " << org.emp.id << endl;
    cout << "Employee name: " << org.emp.name << endl;
    cout << "Employee Salary: " << org.emp.salary << endl;
}