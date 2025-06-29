#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

/*
 * =============================
 * Contact Manager C++ Mini Project
 * =============================
 *
 * A simple console-based contact manager that demonstrates:
 * - Dynamic arrays and memory management
 * - Pointers and references
 * - String manipulation and search
 * - Input validation
 *
 * Features:
 * ✅ Add contacts with name and phone number
 * ✅ View all saved contacts
 * ✅ Search by name (case-insensitive)
 * ✅ Delete by index
 * ✅ Dynamic array resizing
 */

struct Contact {
    string name;
    string phone;
};

// Function declarations
void addContact(Contact*& contacts, int& count, int& capacity);
void printContacts(const Contact* contacts, const int& count);
void findContact(const Contact* contacts, const int& count);
void deleteContact(Contact*& contacts, int& count);

int main() {
    const int initialCapacity = 2;
    Contact* contacts = new Contact[initialCapacity];
    int count = 0;
    int capacity = initialCapacity;
    char choice;

    do {
        cout << "\n=== Contact Manager ===\n";
        cout << "1. Add contact\n";
        cout << "2. View contacts\n";
        cout << "3. Find contact\n";
        cout << "4. Delete contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        if (input.length() != 1 || input[0] < '1' || input[0] > '5') {
            cout << "Invalid input. Please enter a single digit (1–5).\n";
            continue;
        }

        choice = input[0];

        switch (choice) {
            case '1':
                addContact(contacts, count, capacity);
                break;
            case '2':
                printContacts(contacts, count);
                break;
            case '3':
                findContact(contacts, count);
                break;
            case '4':
                deleteContact(contacts, count);
                break;
            case '5':
                cout << "Exit.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                continue;
        }

    } while (choice != '5');

    delete[] contacts;
    return 0;
}

// Adds a new contact to the list
void addContact(Contact*& contacts, int& count, int& capacity) {
    if (count >= capacity) {
        int newCapacity = capacity * 2;
        Contact* newContacts = new Contact[newCapacity];

        for (int i = 0; i < count; ++i)
            newContacts[i] = contacts[i];

        delete[] contacts;
        contacts = newContacts;
        capacity = newCapacity;
    }

    cout << "Enter name: ";
    getline(cin, contacts[count].name);

    cout << "Enter phone: ";
    getline(cin, contacts[count].phone);

    count++;
    cout << "Contact added!\n";
}

// Prints all contacts
void printContacts(const Contact* contacts, const int& count) {
    if (count == 0) {
        cout << "No contacts found.\n";
        return;
    }

    cout << "\nContacts:\n";
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << contacts[i].name << " | " << contacts[i].phone << endl;
    }
}

// Finds contact by name (case-insensitive)
void findContact(const Contact* contacts, const int& count) {
    if (count == 0) {
        cout << "No contacts to search.\n";
        return;
    }

    string searchName;
    cout << "Enter name to search: ";
    getline(cin, searchName);

    bool found = false;
    string lowerSearch = searchName;
    transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);

    for (int i = 0; i < count; ++i) {
        string currentName = contacts[i].name;
        transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);

        if (currentName.find(lowerSearch) != string::npos) {
            cout << "Found: " << contacts[i].name << " — " << contacts[i].phone << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No contact found with that name.\n";
}

// Deletes contact by index
void deleteContact(Contact*& contacts, int& count) {
    if (count == 0) {
        cout << "No contacts to delete.\n";
        return;
    }

    int index;
    cout << "Enter contact number to delete (1-" << count << "): ";

    while (true) {
        cin >> index;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number: ";
        } else {
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > count) {
        cout << "Invalid index.\n";
        return;
    }

    for (int i = index - 1; i < count - 1; ++i) {
        contacts[i] = contacts[i + 1];
    }

    --count;
    cout << "Contact deleted.\n";
}