#include <iostream>
#include <exception>

using namespace std;

class ArrayIndexOutOfBounds : public exception {
public:
    const char* what() const noexcept override {
        return "ArrayIndexOutOfBounds: Invalid index accessed.";
    }
};

template<typename T>
class SafeArray {
private:
    T* arr;
    size_t size;

public:
    SafeArray(size_t s) : size(s) {
        arr = new T[size];
    }

    ~SafeArray() {
        delete[] arr;
    }

    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(size)) {
            throw ArrayIndexOutOfBounds();
        }
        return arr[index];
    }

    size_t getSize() const {
        return size;
    }
};

// Demo usage
int main() {
    try {
        SafeArray<int> arr(5);

        // Fill array
        for (int i = 0; i < arr.getSize(); ++i) {
            arr[i] = i * 10;
        }

        // Print array
        for (int i = 0; i < arr.getSize(); ++i) {
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }

        cout << arr[10] << endl;

    } catch (const ArrayIndexOutOfBounds& e) {
        cerr << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
