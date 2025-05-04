#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

struct User {
    int id;
    string name;

    string to_string() const {
        return std::to_string(id) + "," + name;
    }

    static User from_string(const string& line) {
        User u;
        stringstream ss(line);
        string temp;
        getline(ss, temp, ',');
        u.id = stoi(temp);
        getline(ss, u.name);
        return u;
    }
};

struct Product {
    int id;
    string name;
    int user_id;

    string to_string() const {
        return std::to_string(id) + "," + name + "," + std::to_string(user_id);
    }

    static Product from_string(const string& line) {
        Product p;
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');
        getline(ss, temp); p.user_id = stoi(temp);
        return p;
    }
};

void write_dummy_data() {
    // Users
    ofstream ufile("users.txt");
    vector<User> users = {
        {1, "Linus"},
        {2, "Ada"},
        {3, "Grace"}
    };
    for (const auto& u : users) ufile << u.to_string() << endl;
    ufile.close();

    // Products
    ofstream pfile("products.txt");
    vector<Product> products = {
        {101, "Laptop", 1},
        {102, "Smartphone", 2},
        {103, "Keyboard", 1},
        {104, "Router", 3}
    };
    for (const auto& p : products) pfile << p.to_string() << endl;
    pfile.close();
}

vector<User> read_users() {
    vector<User> users;
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        users.push_back(User::from_string(line));
    }
    return users;
}

vector<Product> read_products() {
    vector<Product> products;
    ifstream file("products.txt");
    string line;
    while (getline(file, line)) {
        products.push_back(Product::from_string(line));
    }
    return products;
}

void find_products_for_user(const string& username) {
    auto users = read_users();
    auto products = read_products();

    unordered_map<string, int> name_to_id;
    for (const auto& user : users) {
        name_to_id[user.name] = user.id;
    }

    if (name_to_id.find(username) == name_to_id.end()) {
        cout << "User not found.\n";
        return;
    }

    int target_id = name_to_id[username];
    cout << "Products associated with user \"" << username << "\":" << endl;
    for (const auto& product : products) {
        if (product.user_id == target_id) {
            cout << "- " << product.name << endl;
        }
    }
}

int main() {
    write_dummy_data(); // write sample data
    find_products_for_user("Linus");
    return 0;
}
