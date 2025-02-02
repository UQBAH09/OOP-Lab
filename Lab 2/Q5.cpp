#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

struct Employee
{
    int id;
    string name;
};

void printData(Employee emp[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "ID: " << emp[i].id << ", Name: " << emp[i].name << endl;
    }
}

void sortByID(Employee emp[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (emp[j + 1].id < emp[j].id)
            {
                swap(emp[j], emp[j + 1]);
            }
        }
    }
}

void sortByName(Employee emp[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (emp[j + 1].name[0] < emp[j].name[0])
            {
                swap(emp[j], emp[j + 1]);
            }
        }
    }
}

void intialize(Employee emp[], char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        emp[i].id = atoi(argv[i * 2 + 1]);
        emp[i].name = argv[i * 2 + 2];
    }
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 2 != 0 || argc == 1)
    {
        cerr << "Insufficent arguments" << endl;
        return 1;
    }

    int n = (argc - 1) / 2;

    // Pull data from arguments into structures
    Employee original[n];
    intialize(original, argv, n);

    // Copy data into structures and sort them
    Employee sortedById[n];
    copy(original, original + n, sortedById);
    sortByID(sortedById, n);

    Employee sortedByName[n];
    copy(original, original + n, sortedByName);
    sortByName(sortedByName, n);

    // print the sorted structures
    cout << "Sort by ID:" << endl;
    printData(sortedById, n);

    cout << "\nSort by Name:" << endl;
    printData(sortedByName, n);
}