#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

int main() {
    size_t capacity;
    cout << "Enter preferred hash table capacity (integer): ";
    cin >> capacity;
    // Echo the input
    cout << capacity << endl;

    PassServer ps(capacity);
    char choice;
    string filename;

    do {
        Menu();
        cin >> choice;
        choice = tolower(choice);
        // Echo the choice
        cout << "choice: " << choice << endl;

        if (choice == 'l') {
            cout << "Enter password file name to load from: ";
            cin >> filename;
            if (!ps.load(filename.c_str()))
                cout << "*****Error: Cannot open file " << filename << endl;
        }
        else if (choice == 'a') {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            pair<string, string> kv(username, password);
            cout << endl;
            if (ps.addUser(kv))
                cout << "User " << username << " added." << endl;
            else
                cout << "*****Error: User already exists. Could not add user." << endl;
        }
        else if (choice == 'r') {
            string username;
            cout << "Enter username: ";
            cin >> username;
            if (ps.removeUser(username))
                cout << "User " << username << " deleted." << endl;
            else
                cout << endl << "*****Error: User not found.  Could not delete user" << endl;
        }
        else if (choice == 'c') {
            string username, oldpassword, newpassword;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> oldpassword;
            cout << endl << "Enter new password: ";
            cin >> newpassword;
            cout << endl;
            pair<string, string> kv(username, oldpassword);
            if (ps.changePassword(kv, newpassword))
                cout << "Password changed for user " << username << endl;
            else
                cout << "*****Error: Could not change user password" << endl;
        }
        else if (choice == 'f') {
            string username;
            cout << "Enter username: ";
            cin >> username;
            cout << endl;
            if (ps.find(username))
                cout << "User '" << username << "' found. " << endl;
            else
                cout << "User '" << username << "' not found. " << endl;
        }
        else if (choice == 'd') {
            ps.dump();
        }
        else if (choice == 's') {
            cout << "Size of hashtable: " << ps.size() << endl;
        }
        else if (choice == 'w') {
            cout << "Enter password file name to write to: ";
            cin >> filename;
            if (!ps.write_to_file(filename.c_str()))
                cout << "*****Error: Cannot write to file " << filename << endl;
        }
        else if (choice == 'x') {
            // do nothing
        }
        else {
            cout << "*****Invalid choice. Please try again." << endl;
        }

    } while (choice != 'x');

    return 0;
}
