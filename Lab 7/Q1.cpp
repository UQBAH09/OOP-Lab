#include <iostream>
#include <vector>

using namespace std;

class Num{
    int num;
public:
    Num(int n): num(n){}

    Num operator-- (){
        num *= 4;
        return *this;
    }

    Num operator-- (int){
        num /= 4;
        return *this;
    }

    int getNum(){return num;}
};

int main(){
    Num n(8);
    
    --n;
    cout << "Prefix: " << n.getNum() << endl;
    n--;
    cout << "Postfix: " << n.getNum() << endl;
}