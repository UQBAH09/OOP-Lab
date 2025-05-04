#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class StackUnderflowException : public exception {
public:
    const char* what() const noexcept override {
        return "StackUnderflowException: Attempted to access element from an empty stack.";
    }
};

template<typename T>
class Stack {
private:
    vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (elements.empty()) {
            throw StackUnderflowException();
        }
        elements.pop_back();
    }

    T top() const {
        if (elements.empty()) {
            throw StackUnderflowException();
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

// Demo usage
int main() {
    Stack<int> s;

    try {
        s.push(10);
        s.push(20);
        s.push(30);

        cout << "Top of stack: " << s.top() << endl;

        s.pop();
        cout << "Top after pop: " << s.top() << endl;

        s.pop();
        s.pop();

        // This will trigger exception
        s.pop();
    } catch (const StackUnderflowException& e) {
        cerr << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
