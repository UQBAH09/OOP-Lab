#include <iostream>
#include <string>

using namespace std;

class Media {
protected:
    string title;
    string publicationDate;
    int uniqueID;
    string publisher;

public:
    Media(string t, string date, int id, string pub)
        : title(t), publicationDate(date), uniqueID(id), publisher(pub) {}

    virtual void displayInfo() const {
        cout << "\n--- Media Info ---\n";
        cout << "Title: " << title << "\nPublication Date: " << publicationDate
             << "\nID: " << uniqueID << "\nPublisher: " << publisher << endl;
    }

    virtual void checkOut() {
        cout << title << " has been checked out.\n";
    }

    virtual void returnItem() {
        cout << title << " has been returned.\n";
    }

    string getTitle() const { return title; }
    string getPublicationDate() const { return publicationDate; }
    int getID() const { return uniqueID; }

    virtual ~Media() {}
};

class Book : public Media {
    string author;
    string ISBN;
    int numberOfPages;

public:
    Book(string t, string date, int id, string pub,
         string auth, string isbn, int pages)
        : Media(t, date, id, pub), author(auth), ISBN(isbn), numberOfPages(pages) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "--- Book Details ---\n" << "Author: " << author << "\nISBN: " << ISBN << "\nPages: " << numberOfPages << endl;
    }
};

class DVD : public Media {
    string director;
    int duration;
    float rating;

public:
    DVD(string t, string date, int id, string pub,
        string dir, int dur, float rate)
        : Media(t, date, id, pub), director(dir), duration(dur), rating(rate) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "--- DVD Details ---\n" << "Director: " << director << "\nDuration: " << duration << " mins" << "\nRating: " << rating << "/10" << endl;
    }
};

class CD : public Media {
    string artist;
    int numberOfTracks;
    string genre;

public:
    CD(string t, string date, int id, string pub,
       string artist, int tracks, string genre)
        : Media(t, date, id, pub), artist(artist), numberOfTracks(tracks), genre(genre) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "--- CD Details ---\n" << "Artist: " << artist << "\nTracks: " << numberOfTracks << "\nGenre: " << genre << endl;
    }
};

class Magazine : public Media {
public:
    Magazine(string t, string date, int id, string pub)
        : Media(t, date, id, pub) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "--- Magazine ---\n(No extra metadata)\n";
    }
};

void searchMedia(const Media& media, const string& title) {
    if (media.getTitle() == title)
        cout << "\n[Search] Found by Title: " << title << endl;
}

void searchMedia(const Media& media, int id) {
    if (media.getID() == id)
        cout << "\n[Search] Found by ID: " << id << endl;
}

void searchMedia(const Media& media, const string& title, const string& pubDate) {
    if (media.getTitle() == title && media.getPublicationDate() == pubDate)
        cout << "\n[Search] Found by Title + Date: " << title << ", " << pubDate << endl;
}

// ------------------ Main Function ------------------

int main() {
    Book b("The C++ Way", "2021", 101, "TechBooks", "Bjarne Stroustrup", "978-123456", 350);
    DVD d("Inception", "2010", 102, "Warner Bros", "Christopher Nolan", 148, 8.8);
    CD c("Divide", "2017", 103, "Sony Music", "Ed Sheeran", 16, "Pop");
    Magazine m("Tech Monthly", "April 2024", 104, "Future Media");

    // Display info
    b.displayInfo();
    d.displayInfo();
    c.displayInfo();
    m.displayInfo();

    // Actions
    b.checkOut();
    d.returnItem();

    // Function Overloading Demo
    searchMedia(b, "The C++ Way");
    searchMedia(c, 103);
    searchMedia(m, "Tech Monthly", "April 2024");

    return 0;
}
