#include <iostream>
#include <cstdlib>
using namespace std;

void resize(int *arr, int *limit, int *n)
{
    if (*(limit) <= *(n))
    {
        int *newarr = new int[*(limit) * 2];
        arr = newarr;
        *(limit) *= 2;
        cout << "Limit excedded to " << *(limit) << endl;
        delete[] arr;
    }
}

int main()
{
    int *num = new int[5];
    int limit = 5;
    int n = 1;

    while (1)
    {
        int choice;
        cout << "Enter number or press 0 to exit: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            for (int i = 0; i < n; i++)
            {
                cout << num[i] << " ";
            }
            delete[] num;
            return 0;

        default:
            resize(num, &limit, &n);
            num[n] = choice;
            n++;
            break;
        }
    }
}