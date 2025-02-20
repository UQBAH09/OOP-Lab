#include <iostream>
#include <vector>
using namespace std;

class Book {
private:
    string title, author, publisher;
    double price;
    int stock;

public:
    Book(string t, string a, string p, double pr, int s)
        : title(t), author(a), publisher(p), price(pr), stock(s) {}

    bool searchBook(string t, string a) const {
        return (title == t && author == a);
    }

    void displayDetails() const {
        cout << "\n--- Book Details ---\n";
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Price: $" << price << endl;
        cout << "Stock Available: " << stock << " copies\n";
    }

    void sellBook(int copies) {
        if (copies > stock) {
            cout << "Required copies not in stock.\n";
        } else {
            double totalCost = copies * price;
            stock -= copies;
            cout << "Total Cost: $" << totalCost << endl;
            cout << "Purchase successful! Remaining stock: " << stock << " copies\n";
        }
    }
};

void initializeInventory(vector<Book>& inventory) {
    inventory.push_back(Book("The Alchemist", "Paulo Coelho", "HarperCollins", 10.99, 5));
    inventory.push_back(Book("1984", "George Orwell", "Secker & Warburg", 8.99, 10));
    inventory.push_back(Book("To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 12.50, 7));
}

int main() {
    vector<Book> inventory;
    initializeInventory(inventory);

    string searchTitle, searchAuthor;
    cout << "Enter book title: ";
    getline(cin, searchTitle);
    cout << "Enter author name: ";
    getline(cin, searchAuthor);

    bool found = false;
    for (Book& book : inventory) {
        if (book.searchBook(searchTitle, searchAuthor)) {
            found = true;
            book.displayDetails();
            
            int copies;
            cout << "Enter number of copies required: ";
            cin >> copies;
            book.sellBook(copies);
            break;
        }
    }

    if (!found) {
        cout << "Book not available in inventory.\n";
    }

    return 0;
}