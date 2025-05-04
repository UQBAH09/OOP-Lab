#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    int years;

    string to_string() const {
        stringstream ss;
        ss << id << "," << name << "," << designation << "," << years;
        return ss.str();
    }

    static Employee from_string(const string& line) {
        Employee emp;
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); emp.id = stoi(temp);
        getline(ss, emp.name, ',');
        getline(ss, emp.designation, ',');
        getline(ss, temp, ','); emp.years = stoi(temp);
        return emp;
    }
};

// Write dummy data
void write_dummy_data(const string& filename) {
    vector<Employee> data = {
        {1, "Alice", "Manager", 3},
        {2, "Bob", "Developer", 1},
        {3, "Carol", "Manager", 1},
        {4, "David", "Manager", 4}
    };

    ofstream file(filename);
    for (const auto& e : data) {
        file << e.to_string() << endl;
    }
    file.close();
}

// Read all data
vector<Employee> read_all(const string& filename) {
    vector<Employee> records;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            records.push_back(Employee::from_string(line));
    }
    return records;
}

// Filter managers with >=2 years
vector<Employee> filter_managers(const vector<Employee>& records) {
    vector<Employee> result;
    for (const auto& e : records) {
        if (e.designation == "Manager" && e.years >= 2)
            result.push_back(e);
    }
    return result;
}

// Overwrite file with selected records
void write_filtered(const string& filename, const vector<Employee>& data) {
    ofstream file(filename);
    for (const auto& e : data) {
        file << e.to_string() << endl;
    }
    file.close();
}

// Add incremented version of the records
void append_incremented(const string& filename, vector<Employee> data) {
    ofstream file(filename, ios::app);
    for (auto& e : data) {
        e.id += 100;        // Increment ID
        e.years += 1;       // Increment Years
        file << e.to_string() << endl;
    }
    file.close();
}

int main() {
    string filename = "employees.txt";

    write_dummy_data(filename);
    cout << "Initial dummy data written." << endl;

    vector<Employee> all = read_all(filename);
    vector<Employee> filtered = filter_managers(all);

    write_filtered(filename, filtered);
    cout << "Filtered managers with >=2 years written to file." << endl;

    append_incremented(filename, filtered);
    cout << "Incremented version of filtered data appended." << endl;

    return 0;
}
