#include <iostream>
#include <cstdlib>
using namespace std;

void argToInt(char *argv[], int num[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		num[i - 1] = atoi(argv[i]);
	}
}

int sum(int num[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += *(num + i);
	}
	return sum;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Too little arguments." << endl;
		return 1;
	}

	int n = argc;
	int num[n];

	argToInt(argv, num, n);
	cout << "The sum is " << sum(num, n) << endl;
}
