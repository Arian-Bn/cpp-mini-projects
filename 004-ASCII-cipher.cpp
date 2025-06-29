#include <iostream>
#include <limits>
using namespace std;

/*
 * =============================
 * ASCII Cipher C++ Mini Project
 * =============================
 *
 * A simple console app that encrypts/decrypts text using ASCII shift cipher.
 * Demonstrates:
 * - ASCII manipulation
 * - Type casting (static_cast)
 * - Input validation
 * - Modular code structure with functions
 */

// Function declarations
string getInputText();
string encrypt(const string& text, int SHIFT);
string decrypt(const string& text, int SHIFT);
void showResult(const string& origin, const string& result, bool is_encrypt);

int main () {
    const int SHIFT = 3;
    int choice;

    cout << "=== ASCII-Cipher ===\n";
    cout << "1. Encrypt\n2. Decrypt\nChoice: ";

    // Validate input
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter 1 or 2: ";
    }

    string original = getInputText();

    string result;
    if (choice == 1)
        result = encrypt(original, SHIFT);
    else
        result = decrypt(original, SHIFT);

    showResult(original, result, choice == 1);

    return 0;
}

// Gets input from user
string getInputText() {
    string input;
    cout << "Please enter text: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    return input;
}

// Encrypts text with ASCII shift and wraps in printable range (32–126)
string encrypt(const string& text, int SHIFT) {
    string result = text;
    for (size_t i = 0; i < text.length(); ++i) {
        int shifted = static_cast<int>(text[i]) + SHIFT;
        if (shifted > 126) shifted = 32 + (shifted - 127) % (126 - 32 + 1);
        result[i] = static_cast<char>(shifted);
    }
    return result;
}

// Decrypts text with ASCII unshift and wraps in printable range (32–126)
string decrypt(const string& text, int SHIFT) {
    string result = text;
    for (size_t i = 0; i < text.length(); ++i) {
        int shifted = static_cast<int>(text[i]) - SHIFT;
        if (shifted < 32) shifted = 126 - (32 - shifted - 1);
        result[i] = static_cast<char>(shifted);
    }
    return result;
}

// Displays the result
void showResult(const string& original, const string& result, bool is_encrypt) {
    cout << "\nOriginal: " << original << endl;
    cout << (is_encrypt ? "Encrypted: " : "Decrypted: ") << result << endl;
}
