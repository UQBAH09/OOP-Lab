#include <iostream>
#include <string>

using namespace std;

class User
{
public:
    int age;
    string name;
};

int main()
{
    User user;
    user.age = 24;
    user.name = "Teo";

    cout << "My name is " << user.name << " and " << user.age << " years old." << endl;
}