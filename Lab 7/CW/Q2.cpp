#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Polynomial; // Forward declaration

class PolynomialUtils {
public:
    int evaluate(const Polynomial& p, int x);
    Polynomial derivative(const Polynomial& p);
};

class Polynomial {
    vector<int> coefficients;

public:
    // Default constructor
    Polynomial() {}

    // Constructor from vector
    Polynomial(const vector<int>& coeffs) {
        coefficients = coeffs;
    }

    // Addition
    Polynomial operator+(const Polynomial& p) {
        int maxSize = max(coefficients.size(), p.coefficients.size());
        vector<int> result(maxSize, 0);

        for (int i = 0; i < maxSize; i++) {
            if (i < coefficients.size()) result[i] += coefficients[i];
            if (i < p.coefficients.size()) result[i] += p.coefficients[i];
        }

        return Polynomial(result);
    }

    // Subtraction
    Polynomial operator-(const Polynomial& p) {
        int maxSize = max(coefficients.size(), p.coefficients.size());
        vector<int> result(maxSize, 0);

        for (int i = 0; i < maxSize; i++) {
            if (i < coefficients.size()) result[i] += coefficients[i];
            if (i < p.coefficients.size()) result[i] -= p.coefficients[i];
        }

        return Polynomial(result);
    }

    // Multiplication
    Polynomial operator*(const Polynomial& p) {
        vector<int> result(coefficients.size() + p.coefficients.size() - 1, 0);

        for (size_t i = 0; i < coefficients.size(); ++i) {
            for (size_t j = 0; j < p.coefficients.size(); ++j) {
                result[i + j] += coefficients[i] * p.coefficients[j];
            }
        }

        return Polynomial(result);
    }

    // Print polynomial
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        if (p.coefficients.empty()) {
            out << "0";
            return out;
        }

        bool firstTerm = true;

        for (int i = p.coefficients.size() - 1; i >= 0; i--) {
            int coeff = p.coefficients[i];
            if (coeff == 0) continue;

            // Sign
            if (firstTerm) {
                if (coeff < 0) out << "-";
                firstTerm = false;
            } else {
                out << (coeff < 0 ? " - " : " + ");
            }

            int absCoeff = abs(coeff);

            // Coefficient and variable
            if (i == 0) {
                out << absCoeff;
            } else {
                if (absCoeff != 1) out << absCoeff;
                out << "x";
                if (i > 1) out << "^" << i;
            }
        }

        return out;
    }

    // Grant friend access
    friend class PolynomialUtils;
};

// Evaluate polynomial at a point x
int PolynomialUtils::evaluate(const Polynomial& p, int x) {
    int result = 0;
    for (int i = 0; i < p.coefficients.size(); i++) {
        result += p.coefficients[i] * pow(x, i);
    }
    return result;
}

// Derivative of a polynomial
Polynomial PolynomialUtils::derivative(const Polynomial& p) {
    if (p.coefficients.size() <= 1)
        return Polynomial({0});

    vector<int> deriv(p.coefficients.size() - 1);
    for (size_t i = 1; i < p.coefficients.size(); ++i) {
        deriv[i - 1] = p.coefficients[i] * i;
    }

    return Polynomial(deriv);
}

// Main function to demonstrate functionality
int main() {
    vector<int> a = {3, 5, 2};     // 2x^2 + 5x + 3
    vector<int> b = {1, -2, 4};    // 4x^2 - 2x + 1

    Polynomial p1(a), p2(b);
    PolynomialUtils utils;

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    cout << "\nAddition:        " << (p1 + p2) << endl;
    cout << "Subtraction:     " << (p1 - p2) << endl;
    cout << "Multiplication:  " << (p1 * p2) << endl;

    int x = 2;
    cout << "\nEvaluate p1 at x = " << x << ": " << utils.evaluate(p1, x) << endl;
    cout << "Derivative of p1:  " << utils.derivative(p1) << endl;

    return 0;
}
