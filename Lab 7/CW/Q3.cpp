#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BigInteger {
private:
    vector<int> digits;  // Least Significant Digit first
    bool isNegative;

    void trim() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }

    bool absLess(const BigInteger& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }
        return false;
    }

    BigInteger absAdd(const BigInteger& other) const {
        BigInteger result;
        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());

        for (int i = 0; i < maxSize || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }

        result.trim();
        return result;
    }

    BigInteger absSubtract(const BigInteger& other) const {
        BigInteger result;
        int borrow = 0;

        for (int i = 0; i < digits.size(); i++) {
            int sub = digits[i] - (i < other.digits.size() ? other.digits[i] : 0) - borrow;
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(sub);
        }

        result.trim();
        return result;
    }

    bool isZero() const {
        return digits.size() == 1 && digits[0] == 0;
    }

public:
    BigInteger() : isNegative(false) {
        digits.push_back(0);
    }

    BigInteger(string number) {
        isNegative = false;
        digits.clear();

        if (number[0] == '-') {
            isNegative = true;
            number = number.substr(1);
        }

        for (int i = number.length() - 1; i >= 0; --i) {
            if (isdigit(number[i]))
                digits.push_back(number[i] - '0');
        }

        trim();
        if (isZero()) isNegative = false;
    }

    // Output
    friend ostream& operator<<(ostream& out, const BigInteger& n) {
        if (n.isNegative && !n.isZero()) out << '-';
        for (int i = n.digits.size() - 1; i >= 0; i--) {
            out << n.digits[i];
        }
        return out;
    }

    // Input
    friend istream& operator>>(istream& in, BigInteger& n) {
        string s;
        in >> s;
        n = BigInteger(s);
        return in;
    }

    // Addition
    BigInteger operator+(const BigInteger& other) const {
        BigInteger result;

        if (isNegative == other.isNegative) {
            result = absAdd(other);
            result.isNegative = isNegative;
        } else {
            if (absLess(other)) {
                result = other.absSubtract(*this);
                result.isNegative = other.isNegative;
            } else {
                result = absSubtract(other);
                result.isNegative = isNegative;
            }
        }

        if (result.isZero()) result.isNegative = false;
        return result;
    }

    // Subtraction
    BigInteger operator-(const BigInteger& other) const {
        BigInteger temp = other;
        temp.isNegative = !other.isNegative;
        return *this + temp;
    }

    // Multiplication
    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits.assign(digits.size() + other.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); i++) {
            for (size_t j = 0; j < other.digits.size(); j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }

        // Handle carry
        for (size_t i = 0; i < result.digits.size(); ++i) {
            if (result.digits[i] >= 10) {
                if (i + 1 == result.digits.size())
                    result.digits.push_back(0);
                result.digits[i + 1] += result.digits[i] / 10;
                result.digits[i] %= 10;
            }
        }

        result.trim();
        result.isNegative = (isNegative != other.isNegative);
        if (result.isZero()) result.isNegative = false;
        return result;
    }


    // Comparisons
    bool operator==(const BigInteger& other) const {
        return isNegative == other.isNegative && digits == other.digits;
    }

    bool operator!=(const BigInteger& other) const {
        return !(*this == other);
    }

    bool operator<(const BigInteger& other) const {
        if (isNegative != other.isNegative)
            return isNegative;

        if (digits.size() != other.digits.size())
            return isNegative ? digits.size() > other.digits.size()
                              : digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i])
                return isNegative ? digits[i] > other.digits[i]
                                  : digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator>(const BigInteger& other) const {
        return other < *this;
    }
};

// Test main function
int main() {
    BigInteger a, b;
    cout << "Enter first big number: ";
    cin >> a;
    cout << "Enter second big number: ";
    cin >> b;

    cout << "\nYou entered:\na = " << a << "\nb = " << b << endl;

    cout << "\nAddition (a + b): " << (a + b) << endl;
    cout << "Subtraction (a - b): " << (a - b) << endl;
    cout << "Multiplication (a * b): " << (a * b) << endl;

    cout << "a > b? " << (a > b ? "Yes" : "No") << endl;
    cout << "a < b? " << (a < b ? "Yes" : "No") << endl;
    cout << "a == b? " << (a == b ? "Yes" : "No") << endl;
    cout << "a != b? " << (a != b ? "Yes" : "No") << endl;

    return 0;
}
