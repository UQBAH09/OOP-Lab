#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to encrypt the input string
string encrypt(const string& text) {
    string encrypted = text;
    for (size_t i = 0; i < text.size(); ++i) {
        encrypted[i] = text[i] + (i + 1);
    }
    return encrypted;
}

// Function to decrypt the encrypted string
string decrypt(const string& encrypted) {
    string decrypted = encrypted;
    for (size_t i = 0; i < encrypted.size(); ++i) {
        decrypted[i] = encrypted[i] - (i + 1);
    }
    return decrypted;
}

int main() {
    string input;
    cout << "Enter String: ";
    getline(cin, input);

    string encryptedText = encrypt(input);

    // Write encrypted text to file
    ofstream outFile("encrypted.txt");
    outFile << encryptedText;
    outFile.close();

    cout << "Normal Text: " << input << endl;
    cout << "Encrypted text inserted in file." << endl;

    // Read encrypted text from file
    ifstream inFile("encrypted.txt");
    string readEncrypted((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    string decryptedText = decrypt(readEncrypted);

    cout << "Decrypted text Read then decoded from file:" << endl;
    cout << decryptedText << endl;

    return 0;
}
