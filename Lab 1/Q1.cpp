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

float secondHighest(float num[], int n)
{
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
	return num[1];
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

	argToFloat(argv, num, n);
	cout << "The second higest number is " << secondHighest(num, n) << endl;
}