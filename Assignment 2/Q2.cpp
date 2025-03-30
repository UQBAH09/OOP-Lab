#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "UQBAH KHAN"
#define STUDENT_ID "24K-0614"

// ======== BASE CLASS: GHOST ==========
class Ghosts {
protected:
    string name;
    int scareLevel;

public:
    Ghosts(string name, int scareLevel) : name(name), scareLevel(scareLevel) {}

    virtual void haunting() = 0;

    int getScareLevel() const { return scareLevel; }

    virtual void display(ostream &out) {
        out << "Ghost played by: " << name << ", Scare Level: " << scareLevel;
    }

    friend ostream &operator<<(ostream &out, Ghosts &g) {
        g.display(out);
        return out;
    }

    Ghosts* operator+(Ghosts& other);

    friend void Visit(class Visitors visitors[], int count, class HauntedHouse& h);
};

// ======== DERIVED CLASSES ==========
class Poltergeists : virtual public Ghosts {
public:
    Poltergeists(string name, int scareLevel) : Ghosts(name, scareLevel) {}

    void haunting() override {
        cout << name << " moves objects mysteriously!" << endl;
    }

    void display(ostream &out) override {
        out << "Poltergeist played by: " << name << ", Scare Level: " << scareLevel;
    }
};

class Banshees : virtual public Ghosts {
public:
    Banshees(string name, int scareLevel) : Ghosts(name, scareLevel) {}

    void haunting() override {
        cout << name << " screams loudly: Booooooo!!!!!" << endl;
    }

    void display(ostream &out) override {
        out << "Banshee played by: " << name << ", Scare Level: " << scareLevel;
    }
};

class ShadowGhosts : virtual public Ghosts {
public:
    ShadowGhosts(string name, int scareLevel) : Ghosts(name, scareLevel) {}

    void haunting() override {
        cout << name << " whispers creepily from the shadows..." << endl;
    }

    void display(ostream &out) override {
        out << "ShadowGhost played by: " << name << ", Scare Level: " << scareLevel;
    }
};

// ======== HYBRID GHOST ==========
class ShadowPoltergeist : public Poltergeists, public ShadowGhosts {
public:
    ShadowPoltergeist(string name, int scareLevel): Ghosts(name, scareLevel), Poltergeists(name, scareLevel), ShadowGhosts(name, scareLevel) {}

    void haunting() override {
        cout << name << " whispers creepily AND moves objects mysteriously!" << endl;
    }

    void display(ostream &out) override {
        out << "ShadowPoltergeist played by: " << name << ", Scare Level: " << scareLevel;
    }
};

Ghosts* Ghosts::operator+(Ghosts& other) {
    string newName = name + " & " + other.name;
    int newScare = scareLevel + other.scareLevel;
    return new Poltergeists(newName, newScare);
}

// ======== VISITOR CLASS ==========
class Visitors {
private:
    string name;
    int bravery;

public:
    Visitors(string name, int bravery) : name(name), bravery(bravery) {}

    string getName() { return name; }

    string getBraveryType() const {
        if (bravery >= 1 && bravery <= 4) return "Cowardly";
        else if (bravery >= 5 && bravery <= 7) return "Average";
        else return "Fearless";
    }

    void reactToGhost(int scareLevel) const {
        string braveryType = getBraveryType();

        if ((braveryType == "Cowardly" && scareLevel < 4) || (braveryType == "Average" && scareLevel < 7) || (braveryType == "Fearless" && scareLevel < 10)) {
            cout << name << " laughs and taunts the ghost!" << endl;
        }
        else if ((braveryType == "Cowardly" && scareLevel > 4) || (braveryType == "Average" && scareLevel > 7) || (braveryType == "Fearless" && scareLevel > 10)) {
            cout << name << " screams and runs away!" << endl;
        }
        else {
            cout << name << " gets a shaky voice..." << endl;
        }
    }

    void display() const {
        cout << "Visitor: " << name << ", Bravery: " << bravery << " (" << getBraveryType() << ")" << endl;
    }
};

// ======== HAUNTED HOUSE ==========
class HauntedHouse {
private:
    string name;
    Ghosts* ghosts[10]; // Max 10 ghosts
    int ghostCount;

public:
    HauntedHouse(string name) : name(name), ghostCount(0) {}

    void addGhost(Ghosts* g) {
        if (ghostCount < 10) {
            ghosts[ghostCount++] = g;
        } else {
            cout << "Haunted house is full!" << endl;
        }
    }

    string getName() const { return name; }

    void display() {
        cout << "\nHaunted House: " << name << endl;
        for (int i = 0; i < ghostCount; i++) {
            cout << *ghosts[i] << endl;
        }
    }

    int getGhostCount() const { return ghostCount; }

    Ghosts* getGhost(int i) const { return ghosts[i]; }

    friend void Visit(Visitors visitors[], int count, HauntedHouse& h);
};

// ======== GLOBAL FRIEND FUNCTION Visit ==========
void Visit(Visitors visitors[], int count, HauntedHouse& h) {
    cout << "\nHaunting visitors at " << h.getName() << "...\n";
    for (int i = 0; i < count; i++) {
        cout << "\n" << visitors[i].getBraveryType() << " visitor \"" << visitors[i].getName() << "\" is being haunted...\n";
        for (int j = 0; j < h.getGhostCount(); j++) {
            h.getGhost(j)->haunting();
            visitors[i].reactToGhost(h.getGhost(j)->getScareLevel());
        }
    }
}

// ======== MAIN ==========
int main() {
    cout << "Student: " << STUDENT_NAME << " | ID: " << STUDENT_ID << endl;

    Visitors visitors[] = {
        Visitors("Ali", 3),
        Visitors("Sara", 6),
        Visitors("John", 9)
    };
    int visitorCount = sizeof(visitors) / sizeof(visitors[0]);

    // Haunted House 1
    HauntedHouse h1("Fear Mansion");
    h1.addGhost(new Poltergeists("Eddie", 6));
    h1.addGhost(new Banshees("Lilly", 9));
    h1.addGhost(new ShadowGhosts("Zara", 4));
    h1.addGhost(new ShadowPoltergeist("Luna", 8));
    h1.display();
    Visit(visitors, visitorCount, h1);

    // Haunted House 2
    HauntedHouse h2("Phantom Hall");
    h2.addGhost(new Banshees("Echo", 7));
    h2.addGhost(new ShadowGhosts("Mist", 5));
    h2.addGhost(new Poltergeists("Flicker", 3));
    h2.display();
    Visit(visitors, visitorCount, h2);

    // Haunted House 3
    HauntedHouse h3("Terror Tower");
    Ghosts* g1 = new ShadowGhosts("Shade", 4);
    Ghosts* g2 = new Banshees("Screech", 6);
    Ghosts* combined = *g1 + *g2;
    h3.addGhost(combined);
    h3.display();
    Visit(visitors, visitorCount, h3);

    delete g1;
    delete g2;
    delete combined;

    return 0;
}