#include <iostream>
#include <any>
#include <unordered_map>
#include <typeindex>
#include <exception>

using namespace std;

class BadTypeException : public exception {
public:
    const char* what() const noexcept override {
        return "BadTypeException: Attempted to retrieve object with wrong type.";
    }
};

class TypeSafeContainer {
private:
    unordered_map<string, any> data;

public:
    template<typename T>
    void store(const string& key, T value) {
        data[key] = value;
    }

    template<typename T>
    T get(const string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw out_of_range("Key not found");
        }

        try {
            return any_cast<T>(it->second);
        } catch (const bad_any_cast&) {
            throw BadTypeException();
        }
    }
};

// Demo usage
int main() {
    TypeSafeContainer container;

    container.store<int>("intVal", 42);
    container.store<string>("strVal", "Hello");

    try {
        int val = container.get<int>("intVal");
        cout << "intVal: " << val << endl;

        string str = container.get<string>("strVal");
        cout << "strVal: " << str << endl;

        // Triggering BadTypeException
        double wrong = container.get<double>("intVal");
    } catch (const BadTypeException& e) {
        cerr << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Other exception: " << e.what() << endl;
    }

    return 0;
}
