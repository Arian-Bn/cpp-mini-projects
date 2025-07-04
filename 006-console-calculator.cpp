#include <iostream>
#include <limits>   // For numeric limits (used in input validation)
#include <string>   // For string manipulation

/*
 * =============================
 * Console Calculator Mini Project
 * =============================
 *
 * A simple console-based calculator that demonstrates:
 * - Use of function pointers to dynamically select operations
 * - Input validation and error handling
 * - User interaction through menus
 * - Clean code structure and separation of concerns
 *
 * Features:
 * Accepts two floating-point numbers from user input
 * Allows user to choose an operation: Add, Subtract, Multiply, Divide
 * Uses function pointers to execute the selected operation
 * Handles division by zero safely
 * Supports repeating calculations or exiting the program
 */

using namespace std;

// === Function Prototypes for Operations ===
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

// === Helper Function to Get Valid Float Input ===
bool getFloatInput(float& value, const string& prompt);

int main() {
    float num1, num2;
    char choice;
    bool calculateAgain = true;

    // Function pointer declaration
    // Points to a function that takes two floats and returns a float
    float (*operationPtr)(float, float) = nullptr;

    while (calculateAgain) {
        cout << "=== Calculator ===" << endl;

        // Get valid first number
        while (!getFloatInput(num1, "Enter first number: ")) {}

        // Get valid second number
        while (!getFloatInput(num2, "Enter second number: ")) {}

        // Display operation menu
        cout << "Choose operation:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Subtract" << endl;
        cout << "3. Multiply" << endl;
        cout << "4. Divide" << endl;
        cout << "Enter choice (1-4): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear newline from buffer

        // Assign correct function to the function pointer
        switch (choice) {
            case '1':
                operationPtr = add;
                break;
            case '2':
                operationPtr = subtract;
                break;
            case '3':
                operationPtr = multiply;
                break;
            case '4':
                operationPtr = divide;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                continue;  // Skip calculation and restart loop
        }

        // Call the selected operation via function pointer
        float result = operationPtr(num1, num2);

        // Display formatted result
        cout << "Result: " << num1 << " ";
        switch (choice) {
            case '1': cout << "+"; break;
            case '2': cout << "-"; break;
            case '3': cout << "*"; break;
            case '4': cout << "/"; break;
        }
        cout << " " << num2 << " = " << result << endl;

        // Ask if user wants to repeat
        char repeat;
        cout << "Do you want to calculate again? (y/n): ";
        cin >> repeat;
        calculateAgain = (repeat == 'y' || repeat == 'Y');
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear newline
    }

    cout << "Thank you for using the calculator!" << endl;
    return 0;
}

// === Operation Definitions ===

/**
 * Adds two numbers.
 */
float add(float a, float b) {
    return a + b;
}

/**
 * Subtracts the second number from the first.
 */
float subtract(float a, float b) {
    return a - b;
}

/**
 * Multiplies two numbers.
 */
float multiply(float a, float b) {
    return a * b;
}

/**
 * Divides the first number by the second.
 * Prevents division by zero.
 */
float divide(float a, float b) {
    if (b == 0) {
        cout << "Error: Division by zero is not allowed." << endl;
        return 0;
    }
    return a / b;
}

// === Utility Functions ===

/**
 * Gets a valid float input from the user.
 * @param value Reference to store the input value
 * @param prompt Message to display before input
 * @return True if input is valid, false otherwise
 */
bool getFloatInput(float& value, const string& prompt) {
    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return false;
    }

    return true;
}
