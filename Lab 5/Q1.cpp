#include <iostream>
#include <vector>
using namespace std;

class Blend
{
public:
    void blend()
    {
        cout << "Selecting fruit...." << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "Bleanding......     (" << i + 1 << " second)" << endl;
        }
        cout << "Blending completed." << endl;
    }
};
class Grind
{
public:
    void grind()
    {
        cout << "Grinding started...." << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "(" << i + 1 << " second)" << endl;
        }
        cout << "Grinding completed." << endl;
    }
};

class JuiceMaker
{
    Blend blendObj;
    Grind grindObj;

public:
    void blendJuice()
    {
        blendObj.blend();
    }

    void grindJuice()
    {
        grindObj.grind();
    }
};

int main() {
    JuiceMaker jm;
    cout << "Starting juice making process..." << endl;
    
    jm.blendJuice();
    jm.grindJuice();
    
    cout << "Juice is ready!" << endl;
    return 0;
}