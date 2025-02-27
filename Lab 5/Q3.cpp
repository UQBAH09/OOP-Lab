#include <iostream>
#include <vector>
using namespace std;

class MenuItem
{
public:
    string name;
    int price;
    string type;
};

class CoffeeShop
{
public:
    const string name;
    vector<MenuItem> Menu;
    vector<string> orders;

    CoffeeShop(const string &shopName, const vector<MenuItem> &menuItems)
        : name(shopName), Menu(menuItems) {}

    void addOrder(const string item)
    {
        for (MenuItem m : Menu)
        {
            if (m.name == item)
            {
                orders.push_back(item);
                return;
            }
        }
        cout << "This item is currently unavailable!" << endl;
    }

    void fulfillOrder()
    {
        if (orders.empty())
        {
            cout << "All orders have been fulfilled" << endl;
            return;
        }
        cout << "The " << orders.front() << " is ready!" << endl;
        orders.erase(orders.begin());
    }

    void listOrders()
    {
        cout << "List of orders:" << endl;
        for (string order : orders)
        {
            cout << "  " << order << endl;
        }
    }

    void dueAmount()
    {
        int sum = 0;
        for (string order : orders)
        {
            for (int i = 0; i < Menu.size(); i++)
            {
                if (order == Menu[i].name)
                {
                    sum += Menu[i].price;
                }
            }
        }
        cout << "Total amount due: " << sum << " pkr" << endl;
    }

    void cheapestItem()
    {
        if (Menu.empty())
        {
            cout << "Menu is empty." << endl;
            return;
        }
        int cheapest = Menu[0].price;
        int cheapestItemIndex = 0;
        for (int i = 0; i < Menu.size(); i++)
        {
            if (cheapest > Menu[i].price)
            {
                cheapest = Menu[i].price;
                cheapestItemIndex = i;
            }
        }
        cout << "The cheapest item on the venue is " << Menu[cheapestItemIndex].name
             << ", priced " << cheapest << " pkr." << endl;
    }

    void drinksOnly()
    {
        cout << "Drinkable items:" << endl;
        for (int i = 0; i < Menu.size(); i++)
        {
            if (Menu[i].type == "drink")
            {
                cout << "  " << Menu[i].name << endl;
            }
        }
    }

    void foodOnly()
    {
        cout << "Eatable items:" << endl;
        for (int i = 0; i < Menu.size(); i++)
        {
            if (Menu[i].type == "food")
            {
                cout << "  " << Menu[i].name << endl;
            }
        }
    }
};

int main()
{
    // Create a list of menu items.
    vector<MenuItem> items;

    MenuItem item1;
    item1.name = "Coffee";
    item1.price = 100;
    item1.type = "drink";
    items.push_back(item1);

    MenuItem item2;
    item2.name = "Tea";
    item2.price = 80;
    item2.type = "drink";
    items.push_back(item2);

    MenuItem item3;
    item3.name = "Sandwich";
    item3.price = 150;
    item3.type = "food";
    items.push_back(item3);

    MenuItem item4;
    item4.name = "Cake";
    item4.price = 120;
    item4.type = "food";
    items.push_back(item4);

    // Create a CoffeeShop object with the name "Cafe Delight" and the above menu.
    CoffeeShop shop("Cafe Delight", items);

    // Display shop name
    cout << "Welcome to " << shop.name << "!" << endl;

    // Test addOrder: adding valid orders and an invalid order.
    shop.addOrder("Coffee");
    shop.addOrder("Cake");
    shop.addOrder("Burger"); // This should print an error message.

    // List current orders.
    shop.listOrders();

    // Fulfill an order.
    shop.fulfillOrder();

    // List orders after fulfilling one.
    shop.listOrders();

    // Show the total amount due for the current orders.
    shop.dueAmount();

    // Display the cheapest item on the menu.
    shop.cheapestItem();

    // Display only drinks from the menu.
    shop.drinksOnly();

    // Display only food items from the menu.
    shop.foodOnly();

    return 0;
}
