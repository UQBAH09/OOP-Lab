#include <iostream>
using namespace std;

class Books {
    string genre;
public:
    Books(string genre) : genre(genre) {}
    string getGenre() const { return genre; }
};

class Mystery : public Books {
    string title;
    string author;
public:
    Mystery(string title, string author) 
        : Books("Mystery"), title(title), author(author) {}

    void display() {
        cout << "Genre: " << getGenre() << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
    }
};

class Thriller : public Books {
    string title;
    string author;
public:
    Thriller(string title, string author) 
        : Books("Thriller"), title(title), author(author) {}

    void display() {
        cout << "Genre: " << getGenre() << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
    }
};

int main() {
    Thriller t("The Silent Patient", "Alex Michaelides");
    Mystery m("Gone Girl", "Gillian Flynn");

    cout << "Book 1:" << endl;
    t.display();
    cout << "\nBook 2:" << endl;
    m.display();

    return 0;
}
