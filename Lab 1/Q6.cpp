#include <iostream>
#include <cstdlib>
using namespace std;

void getInfo(char* argv[], string* name, float marks[]){
    *(name) = argv[1];
    for (int i = 0; i < 5; i++)
    {
        marks[i] = atof(argv[i+2]);
    }
}

float avg(float marks[]){
    float sum=0;
    for (int i = 0; i < 5; i++)
    {
        sum += marks[i];
    }
    return sum/5;
}

int main(int argc, char* argv[]){
    if(argc != 7){
        cout << "Insufficent arguments." << endl;
        return 1;
    }

    string name;
    float marks[5];

    getInfo(argv, &name, marks);

    cout << "Student Name: " << name << endl;
    cout << "Test Scores: ";
    for (int i = 0; i < 5; i++)
    {
        printf("%.2f ", marks[i]);
    }
    printf("\nAverage test scores: %.2f", avg(marks));
}