#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    string firstName;
    string lastName;
    double salary;

public:
    void setter(string firstName, string lastName, double salary)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        if (salary < 0)
            this->salary = 0;
        else
            this->salary = salary;
    }

    void yearlySalary()
    {
        cout << "Name: " << firstName << " " << lastName << ", Salary: " << salary * 12 << endl;
    }

    void raise(int percentage)
    {
        salary *= (1 + (percentage / 100.0));
    }
};

void intialize(Employee emp[], char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        emp[i].setter(argv[i * 3 + 1], argv[i * 3 + 2], atof(argv[i * 3 + 3]));
    }
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 3 != 0 || argc == 1)
    {
        cerr << "Insufficent arguments." << endl;
        return 1;
    }

    int n = (argc - 1) / 3;
    Employee emp[n];
    intialize(emp, argv, n);

    cout << "Yearly salary:" << endl;
    for (int i = 0; i < n; i++)
    {
        emp[i].yearlySalary();
    }

    cout << "\nYearly salary after raise:" << endl;
    for (int i = 0; i < n; i++)
    {
        emp[i].raise(10);
        emp[i].yearlySalary();
    }
}