#include <iostream>
#include <limits>
#include <iomanip>

// === Macros for operations ===
#define ADD(a, b) ((a) + (b))
#define SUBTRACT(a, b) ((a) - (b))
#define MULTIPLY(a, b) ((a) * (b))
#define DIVIDE(a, b) ((b) != 0 ? (a) / (b) : 0)

// === Macros for message
#define INVALID_INPUT_MSG "Invalid input. Please inter a valid number.\n"
#define PROMPT_FIRST "Enter first number: "
#define PROMPT_SECOND "Enter second number: "

using namespace std;

/*
 * =============================
 * Calculator with Macros C++ Mini Project
 * =============================
 *
 * A simple console-based calculator that demonstrates:
 * - Using #define macros for basic operations
 * - Input validation
 * - String concatenation and formatting
 * - Modular code structure
 *
 * Features:
 * ✅ Add, subtract, multiply, divide using macros
 * ✅ Safe input handling
 * ✅ Repeat calculation option
 */

// Function declarations
int getValidChoice();
double getValidNumber(const string& prompt);
bool askToContinue();

int main() {
    cout << "=== Calculator with Macros ===\n";

    do {
        double num1 = getValidNumber(PROMPT_FIRST);
        double num2 = getValidNumber(PROMPT_SECOND);

        int choice = getValidChoice();

        double result = 0;
        string opSymbol;

        // Use macros   based on users choice
        switch (choice) {
            case 1:
                result = ADD(num1, num2);
                opSymbol = "+";
                break;
            case 2:
                result = SUBTRACT(num1, num2);
                opSymbol = "-";
                break;
            case 3:
                result = MULTIPLY(num1, num2);
                opSymbol = "*";
                break;
            case 4:
                if (num2 == 0) {
                    cout << "Error! Division by zero.\n";
                    break;
                }
                result = DIVIDE(num1, num2);
                opSymbol = "/";
                break;
            default:
                cout << "Invalid operation selected.\n";
                break;
        }

        // Concatenate strings for output
        cout << fixed << setprecision(2);
        cout << "Result: " << num1 << " " << opSymbol << " " << num2 << " = " << result << endl;
    } while (askToContinue());

    cout << "Exit.\n";
    return 0;
}

// Gets valid numeric input
double getValidNumber(const string& prompt) {
    double value;
    cout << prompt;

    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << INVALID_INPUT_MSG;
        cout << prompt;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear Buffer
    return value;
}

// Gets valid operations choice
int getValidChoice() {
    int choice;

    cout << "Choose operation:\n";
    cout << "1. Addition\n2. Subtraction\n3. Multiply\n4. Divide\nEnter: ";

    while (true) {
        if (cin >> choice && choice >=1 && choice <= 4) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// Ask to countinue
bool askToContinue() {
    char response;
    cout << "Do you want to calculate again? (y/n):";
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return (response == 'Y' || response == 'y');
}