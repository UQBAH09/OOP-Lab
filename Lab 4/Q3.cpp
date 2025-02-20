#include <iostream>
using namespace std;

class Invoice {
public:
    string partNum;
    string description;
    int quantity;
    double price;

    Invoice(string num, string dis, int quan, double pri)
        : partNum(num), description(dis) {
        quantity = (quan > 0) ? quan : 0;
        price = (pri > 0) ? pri : 0.0;
    }

    double getInvoiceAmount() const {
        return quantity * price;
    }
};

int main() {
    string partNum, description;
    int quantity;
    double price;

    // Get user input
    cout << "Enter part number: ";
    cin >> partNum;
    cin.ignore(); // Ignore newline for getline()

    cout << "Enter part description: ";
    getline(cin, description);

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Enter price per item: ";
    cin >> price;

    // Create Invoice object
    Invoice invoice(partNum, description, quantity, price);

    // Display invoice details
    cout << "\n--- Invoice Details ---\n";
    cout << "Part Number: " << invoice.partNum << endl;
    cout << "Description: " << invoice.description << endl;
    cout << "Quantity: " << invoice.quantity << endl;
    cout << "Price per item: $" << invoice.price << endl;
    cout << "Total Invoice Amount: $" << invoice.getInvoiceAmount() << endl;

    return 0;
}
