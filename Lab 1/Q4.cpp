#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Insufficent argumnets" << endl;
        return 1;
    }

    float kg = atof(argv[1]);
    float pounds = kg * 2.2;

    printf("Weight in kg: %.2f\n", kg);
    printf("Weight in pound: %.2f\n", pounds);
}