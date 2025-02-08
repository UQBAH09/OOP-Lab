#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
    int month;
    int date;
    int year;

public:
    void getDate(int d, int m, int y)
    {
        date = d;
        month = m;
        year = y;
    }
    void displayDate()
    {
        printf("%d/%d/%d", date, month, year);
    }
};

int main()
{
    Date date;

    date.getDate(5, 3, 2024);
    date.displayDate();
}