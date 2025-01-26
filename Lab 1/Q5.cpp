#include <iostream>
#include <iomanip>
#include<cstdlib>
using namespace std;

void getInfo(char* argv[], string* name, float* adultPrice, float* childPrice, float* grossPer, int* adultTickets, int* childTickets){
    *(name) = argv[1];
    *(adultPrice) = atof(argv[2]);
    *(childPrice) = atof(argv[3]);
    *(adultTickets) = atoi(argv[4]);
    *(childTickets) = atoi(argv[5]);
    *(grossPer) = atof(argv[6]);
}

void calPrice(string name, float adultPrice, float childPrice, float grossPer, int adultTickets, int childTickets) {
    int totalTickets = adultTickets + childTickets;
    float grossAmount = (adultTickets * adultPrice) + (childTickets * childPrice);
    float amountDonated = (grossPer / 100) * grossAmount;
    float netSale = grossAmount - amountDonated;

    cout << setprecision(2) << fixed;

    cout << left << setw(40) << "Movie Name:" << right << setw(30) << name << endl;
    cout << left << setw(40) << "Number of Tickets Sold:" << right << setw(30) << totalTickets << endl;
    cout << left << setw(40) << "Gross Amount:" << right << setw(30) << "$ " << grossAmount << endl;
    cout << left << setw(40) << "Percentage of Gross Amount Donated:" << right << setw(29) << grossPer << "%" << endl;
    cout << left << setw(40) << "Amount Donated:" << right << setw(30) << "$ " << amountDonated << endl;
    cout << left << setw(40) << "Net Sale:" << right << setw(30) << "$ " << netSale << endl;
}


int main(int argc, char* argv[]){
    if (argc != 7){
        cout << "Insufficent arguments." << endl;
        return 1;
    }

    string name;
    float adultPrice, childPrice, grossPer;
    int adultTickets, childTickets;

    getInfo(argv, &name, &adultPrice, &childPrice, &grossPer, &adultTickets, &childTickets);
    calPrice(name, adultPrice, childPrice, grossPer, adultTickets, childTickets);
}