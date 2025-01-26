#include <iostream>
#include <cstdlib>
using namespace std;

void getInput(char *argv[], int *id, string *name, int *units)
{
	*(id) = atoi(argv[1]);
	*(name) = argv[2];
	*(units) = atoi(argv[3]);
}

void calPrice(int id, string name, int units)
{
	float price, surcharge, punit, total;
	if (units < 199)
	{
		punit = 16.2;
		price = units * 16.2;
	}
	else if (units < 300)
	{
		punit = 20.1;
		price = units * 20.1;
	}
	else if (units < 500)
	{
		punit = 27.1;
		price = units * 27.1;
	}
	else
	{
		punit = 35.9;
		price = units * 35.9;
	}

	if (price > 18000)
		surcharge = 0.15 * price;
	else
		surcharge = 0;

	total = surcharge + price;

	cout << "Customer ID: " << id << endl;
	cout << "Customer Name: " << name << endl;
	cout << "Units Consumed: " << units << endl;
	cout << "Amount Charges @Rs. " << punit << " per unit: " << price << endl;
	cout << "Surcharge Amount: " << surcharge << endl;
	cout << "Net Amount Paid by the Customer: " << total << endl;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Insufficent arguments." << endl;
		return 1;
	}

	int id, units;
	string name;

	getInput(argv, &id, &name, &units);
	calPrice(id, name, units);
}