#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

map<string, string> passwords;
const string key = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const string value = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM5678901234";

void encryptDecrypt(string& str) {
    for (char& c : str) {
        size_t pos = key.find(c);
        if (pos != string::npos) {
            c = value[pos];
        }
    }
}

void loadPasswords() {
    ifstream file("passwords.txt");
    string website, password;
    while (file >> website >> password) {
        encryptDecrypt(password);
        passwords[website] = password;
    }
    file.close();
}

void savePasswords() {
    ofstream file("passwords.txt");
    for (auto& pair : passwords) {
        string password = pair.second;
        encryptDecrypt(password);
        file << pair.first << " " << password << endl;
    }
    file.close();
}

void addPassword() {
    string website, password;
    cout << "Enter website: ";
    cin >> website;
    cout << "Enter password: ";
    cin >> password;
    passwords[website] = password;
    savePasswords();
    cout << "Password saved!" << endl;
}

void getPassword() {
    string website;
    cout << "Enter website: ";
    cin >> website;
    if (passwords.find(website) != passwords.end()) {
        cout << "Password for " << website << ": " << passwords[website] << endl;
    } else {
        cout << "No password found for " << website << endl;
    }
}

int main() {
    loadPasswords();
    int choice;
    while (true) {
        cout << "\nPassword Manager Menu" << endl;
        cout << "1. Add Password" << endl;
        cout << "2. Get Password" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addPassword();
            break;
        case 2:
            getPassword();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}
