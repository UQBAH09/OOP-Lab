#include <iostream>
#include <cstdlib>
using namespace std;

void intalize(int num[], char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        num[i] = atoi(*(argv + i + 1));
    }
}

void *alter(void *num, int n)
{
    int *arr = (int *)num;

    for (int i = 0; i < n; i++)
    {
        arr[i] += 2;
    }
    return num;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Too little arguments." << endl;
        return 1;
    }

    int n = argc - 1;
    int *num = new int[n];

    intalize(num, argv, n);
    alter(num, n);

    for (int i = 0; i < n; i++)
    {
        cout << num[i] << " ";
    }
}