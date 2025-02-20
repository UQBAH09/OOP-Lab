#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct MenuItem {
    string name;
    string type;
    double price;

    MenuItem(string n, string t, double p) : name(n), type(t), price(p) {}
};

class CoffeeShop {
private:
    string name;
    vector<MenuItem> menu;
    vector<string> orders;

public:
    CoffeeShop(string shopName, vector<MenuItem> menuItems) : name(shopName), menu(menuItems) {}

    string addOrder(string itemName) {
        for (const MenuItem& item : menu) {
            if (item.name == itemName) {
                orders.push_back(itemName);
                return "Order added: " + itemName;
            }
        }
        return "This item is currently unavailable";
    }

    string fulfillOrder() {
        if (!orders.empty()) {
            string order = orders.front();
            orders.erase(orders.begin());
            return "The " + order + " is ready";
        }
        return "All orders have been fulfilled";
    }

    vector<string> listOrders() {
        return orders;
    }

    double dueAmount() {
        double total = 0.0;
        for (const string& order : orders) {
            for (const MenuItem& item : menu) {
                if (item.name == order) {
                    total += item.price;
                }
            }
        }
        return total;
    }

    string cheapestItem() {
        if (menu.empty()) return "No items available";

        double minPrice = numeric_limits<double>::max();
        string cheapest = "";
        
        for (const MenuItem& item : menu) {
            if (item.price < minPrice) {
                minPrice = item.price;
                cheapest = item.name;
            }
        }
        return cheapest;
    }

    vector<string> drinksOnly() {
        vector<string> drinks;
        for (const MenuItem& item : menu) {
            if (item.type == "drink") {
                drinks.push_back(item.name);
            }
        }
        return drinks;
    }

    vector<string> foodOnly() {
        vector<string> foods;
        for (const MenuItem& item : menu) {
            if (item.type == "food") {
                foods.push_back(item.name);
            }
        }
        return foods;
    }
};

int main() {
    vector<MenuItem> menu = {
        {"Espresso", "drink", 3.50},
        {"Cappuccino", "drink", 4.00},
        {"Latte", "drink", 4.50},
        {"Croissant", "food", 2.75},
        {"Muffin", "food", 3.00},
        {"Bagel", "food", 2.50}
    };

    CoffeeShop shop("BOB Cafe", menu);

    cout << shop.addOrder("Espresso") << endl;
    cout << shop.addOrder("Bagel") << endl;
    cout << shop.addOrder("Mocha") << endl;

    cout << "\nOrders list: ";
    for (const string& order : shop.listOrders()) {
        cout << order << " ";
    }
    cout << endl;

    cout << "Total due amount: $" << shop.dueAmount() << endl;

    cout << shop.fulfillOrder() << endl;
    cout << shop.fulfillOrder() << endl;
    cout << shop.fulfillOrder() << endl;

    cout << "Cheapest item: " << shop.cheapestItem() << endl;

    cout << "\nDrinks available: ";
    for (const string& drink : shop.drinksOnly()) {
        cout << drink << " ";
    }

    cout << "\nFoods available: ";
    for (const string& food : shop.foodOnly()) {
        cout << food << " ";
    }

    return 0;
}
