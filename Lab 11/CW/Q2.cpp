#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class DimensionMismatchException : public exception {
public:
    const char* what() const noexcept override {
        return "DimensionMismatchException: Matrix dimensions do not match for the operation.";
    }
};

template<typename T>
class Matrix {
private:
    vector<vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, vector<T>(c)) {}

    void set(size_t i, size_t j, T value) {
        if (i >= rows || j >= cols) {
            throw out_of_range("Index out of bounds");
        }
        data[i][j] = value;
    }

    T at(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw out_of_range("Index out of bounds");
        }
        return data[i][j];
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Matrix Addition
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw DimensionMismatchException();
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];

        return result;
    }

    // Matrix Multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw DimensionMismatchException();
        }

        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = T();
                for (size_t k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }

        return result;
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row)
                cout << elem << " ";
            cout << endl;
        }
    }
};

// Demo usage
int main() {
    try {
        Matrix<int> A(2, 2), B(2, 2);

        A.set(0, 0, 1); A.set(0, 1, 2);
        A.set(1, 0, 3); A.set(1, 1, 4);

        B.set(0, 0, 5); B.set(0, 1, 6);
        B.set(1, 0, 7); B.set(1, 1, 8);

        cout << "Matrix A:\n";
        A.print();

        cout << "\nMatrix B:\n";
        B.print();

        Matrix<int> C = A + B;
        cout << "\nA + B:\n";
        C.print();

        Matrix<int> D = A * B;
        cout << "\nA * B:\n";
        D.print();

        // Uncomment to test dimension mismatch exception
        // Matrix<int> E(3, 3);
        // Matrix<int> F = A + E;

    } catch (const DimensionMismatchException& e) {
        cerr << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
