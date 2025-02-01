#include <iostream>
#include <cstdlib>
using namespace std;

void argToFloat(char *argv[], float num[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        num[i - 1] = atof(argv[i]);
    }
}

float secondHighest(float num[], int n, int *error)
{
    *error = 0;

    float temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*(num + j) < *(num + j + 1))
            {
                temp = *(num + j);
                *(num + j) = *(num + j + 1);
                *(num + j + 1) = temp;
            }
        }
    }

    int max = num[0];
    for (int i = 0; i < n; i++)
    {
        if (num[i] < max)
        {
            return num[i];
        }
    }

    cerr << "Error: All numbers are the same. No second highest number." << endl;
    *error = 1;
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Too little arguments." << endl;
        return 1;
    }

    int n = argc - 1;
    float num[n];
    int error;

    argToFloat(argv, num, n);

    float number = secondHighest(num, n, &error);

    if (!error)
    {
        cout << "The second higest number is " << number << endl;
    }
}
