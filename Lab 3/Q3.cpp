#include <iostream>
#include <string>

using namespace std;

class Glass
{
public:
    int LiquidLevel;

    void Drink(int milliliters)
    {
        LiquidLevel -= milliliters;

        if (LiquidLevel < 100)
        {
            Refill();
        }
        cout << "Amount left: " << LiquidLevel << endl;
    }
    void Refill()
    {
        LiquidLevel = 200;
        cout << "Refilled." << endl;
    }
};

int main()
{
    Glass g;

    g.LiquidLevel = 200;

    cout << "Enter -1 to exit." << endl;

    while (1)
    {
        int amount;
        cout << "Enter amount to drink: ";
        cin >> amount;
        if (amount == -1)
        {
            return 1;
        }
        else
        {
            g.Drink(amount);
        }
    }
}