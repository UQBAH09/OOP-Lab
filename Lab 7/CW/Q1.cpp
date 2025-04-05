#include <iostream>
#include <numeric>

using namespace std;

class Fractions
{
    int numerator;
    int denominator;

    void reduce()
    {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }
    }

public:
    Fractions(int num = 0, int den = 1)
    {
        if (den == 0)
        {
            cout << "Denominator cannot be zero. Setting to 1 by default.\n";
            den = 1;
        }
        numerator = num;
        denominator = den;
        reduce();
    }

    // Arithmetic operators
    Fractions operator+(const Fractions &f)
    {
        return Fractions(numerator * f.denominator + f.numerator * denominator, denominator * f.denominator);
    }

    Fractions operator-(const Fractions &f)
    {
        return Fractions(numerator * f.denominator - f.numerator * denominator, denominator * f.denominator);
    }

    Fractions operator*(const Fractions &f)
    {
        return Fractions(numerator * f.numerator, denominator * f.denominator);
    }

    Fractions operator/(const Fractions &f)
    {
        if (f.numerator == 0)
        {
            cout << "Cannot divide by zero fraction. Returning original fraction.\n";
            return *this;
        }
        return Fractions(numerator * f.denominator, denominator * f.numerator);
    }

    // Relational operators
    bool operator==(const Fractions &other) const
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fractions &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Fractions &other) const
    {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    bool operator>(const Fractions &other) const
    {
        return other < *this;
    }

    bool operator<=(const Fractions &other) const
    {
        return !(*this > other);
    }

    bool operator>=(const Fractions &other) const
    {
        return !(*this < other);
    }

    // I/O stream operators
    friend ostream &operator<<(ostream &out, const Fractions &f);
    friend istream &operator>>(istream &in, Fractions &f);
};

// Output stream
ostream &operator<<(ostream &out, const Fractions &f)
{
    if (f.denominator == 1)
        out << f.numerator << endl;
    else
        out << f.numerator << "/" << f.denominator << endl;
    return out;
}

// Input stream
istream &operator>>(istream &in, Fractions &f)
{
    cout << "Enter numerator and denominator: ";
    in >> f.numerator >> f.denominator;

    if (f.denominator == 0)
    {
        cout << "Denominator cannot be zero. Setting to 1 by default.\n";
        f.denominator = 1;
    }

    f.reduce();
    return in;
}

// Main function to demonstrate all functionalities
int main()
{
    Fractions f1(1, 2), f2(2, 3);

    cout << "Initial Fractions:\n";
    cout << "f1 => " << f1;
    cout << "f2 => " << f2;

    Fractions sum = f1 + f2;
    Fractions diff = f1 - f2;
    Fractions prod = f1 * f2;
    Fractions quot = f1 / f2;

    cout << "\nOperations:\n";
    cout << "f1 + f2 = " << sum;
    cout << "f1 - f2 = " << diff;
    cout << "f1 * f2 = " << prod;
    cout << "f1 / f2 = " << quot;

    cout << "\nComparison Operators:\n";
    cout << "f1 == f2? " << (f1 == f2 ? "True" : "False") << endl;
    cout << "f1 != f2? " << (f1 != f2 ? "True" : "False") << endl;
    cout << "f1 < f2? " << (f1 < f2 ? "True" : "False") << endl;
    cout << "f1 > f2? " << (f1 > f2 ? "True" : "False") << endl;
    cout << "f1 <= f2? " << (f1 <= f2 ? "True" : "False") << endl;
    cout << "f1 >= f2? " << (f1 >= f2 ? "True" : "False") << endl;

    Fractions f3;
    cout << "\nNow enter a new fraction f3:\n";
    cin >> f3;
    cout << "You entered f3 => " << f3;

    return 0;
}
