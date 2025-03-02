#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Catalog
{
    vector<string> ISBN;
    vector<string> locations;

public:
    void addISBN(string s, string l)
    {
        ISBN.push_back(s);
        locations.push_back(l);
        cout << "\nISBN Added: " << s << " at location " << l;
    }

    string getLocation(string isbn)
    {
        for (size_t i = 0; i < ISBN.size(); ++i)
        {
            if (isbn == ISBN[i])
            {
                return locations[i];
            }
        }
        return "ISBN not found";
    }
};

class Book
{
    string title;
    string author;
    string isbn;

public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i) {}

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    string getISBN() const
    {
        return isbn;
    }
};

class Library
{
    Catalog catalog;
    vector<Book> books;

public:
    void addBook(const Book &book, string location)
    {
        catalog.addISBN(book.getISBN(), location);
        books.push_back(book);
    }

    void searchBookByISBN(string isbn)
    {
        string location = catalog.getLocation(isbn);
        if (location != "ISBN not found")
        {
            cout << "Book found at location: " << location << endl;
        }
        else
        {
            cout << "Book with ISBN " << isbn << " not found in the catalog." << endl;
        }
    }

    void printLibraryBooks()
    {
        for (const auto &book : books)
        {
            cout << "Book: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << endl;
        }
    }
};

int main()
{
    Library myLibrary;

    // Adding books with updated values
    Book book1("The Alchemist", "Paulo Coelho", "9780062315007");
    Book book2("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "9780439708180");
    Book book3("The Hobbit", "J.R.R. Tolkien", "9780618260300");

    myLibrary.addBook(book1, "Shelf A5");
    myLibrary.addBook(book2, "Shelf B3");
    myLibrary.addBook(book3, "Shelf C7");

    // Display all books
    cout << "\nBooks available in the library:\n";
    myLibrary.printLibraryBooks();

    // Static book search
    cout << "\nSearching for a book with ISBN 9780439708180...\n";
    myLibrary.searchBookByISBN("9780439708180");

    cout << "\nSearching for a book with ISBN 9999999999999...\n";
    myLibrary.searchBookByISBN("9999999999999");

    return 0;
}
