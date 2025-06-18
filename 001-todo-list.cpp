#include <iostream>
#include <limits>

/*
 * =============================
 * To-Do List C++ Mini Project
 * =============================
 *
 * A simple console-based To-Do List application written in C++.
 * Demonstrates the use of dynamic arrays for managing tasks and their completion status.
 *
 * Features:
 * - Add new tasks
 * - Mark tasks as completed
 * - Delete tasks by index
 * - Dynamic array resizing (doubles capacity when full)
 * - Colored terminal output for task status
 *
 * Memory Management:
 * Uses raw pointers and manual memory handling to demonstrate dynamic arrays in C++.
 *
 * Terminal Colors:
 * Uses ANSI escape codes to display checkmarks in green when a task is marked as done.
 *
*/

// Increases array capacity by 2 times when overflow occurs
void expandArrays(std::string*& tasks, bool*& completed, int& capacity);

int main () {
    const int initialCapacity = 4; // Initial size of arrays
    std::string* tasks = new std::string[initialCapacity]; // Task array
    bool* completed = new bool[initialCapacity]; // Task statuses
    int count = 0; // Current number of tasks
    int capacity = initialCapacity; // Current capacity

    char choice;
    do {
        std::cout << "==== To-Do List ====\n";
        std::cout << "1. Add task\n";
        std::cout << "2. Show all tasks\n";
        std::cout << "3. Mark as done\n";
        std::cout << "4. Deleting a task\n";
        std::cout << "5. Exit\n\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                if (count == capacity) {
                    expandArrays(tasks, completed, capacity); // Expand arrays if necessary
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
                std::cout << "Enter the task: ";
                std::getline(std::cin, tasks[count]);
                completed[count] = false;
                count++;

                std::cout << '\n';
                break;
            case '2':
                std::cout << "\n=== Task list ===\n";

                if (count == 0) {
                    std::cout << "The task list is empty.";
                } else {
                    for (int i = 0; i < count; i++) {
                        std::cout << i + 1 << ". [" << (completed [i]? "\033[32mx\033[0m" : " ") << "] " << tasks[i] << "\n\n";
                    }
                }
                break;
            case '3':
                int index;
                std::cout << "Enter the task number to mark: ";
                std::cin >> index;

                if (index > 0 && index <= count) {
                    completed[index - 1] = true;
                    std::cout << index << "\nThe task is marked as completed.\n";
                } else {
                    std::cout << "Invalid task number\n\n";
                }

                std::cout << '\n';
                break;
            case '4':
                int nindex;
                std::cout << "Enter the task number to delete: ";
                std::cin >> nindex;

                if (nindex > 0 && nindex <= count) {
                    for (int i = nindex - 1; i < count - 1; ++i) {
                        tasks[i] = tasks[i + 1];
                        completed[i] = completed[i + 1];
                    }
                    count--;
                    std::cout << "The task has been deleted.\n\n";
                } else {
                    std::cout << "Invalid task number\n\n";
                }
                break;
            case '5':
                std::cout << "Exit the program.";
                break;
            default:
                std::cout << "Incorrect choice. Try again.\n\n\n";
        }
    } while (choice != '5');


    delete [] tasks;        // Free the task array
    delete [] completed;    // Free the status array

    return 0;
}

// Increases the capacity of arrays by 2 times
void expandArrays(std::string*& tasks, bool*& completed, int& capacity) {
    int newCapacity = capacity * 2;
    std::string* newTasks = new std::string[newCapacity];
    bool* newCompleted = new bool[newCapacity];

    // Copy old data
    for (int i = 0; i < capacity; i++) {
        newTasks[i] = tasks[i];
        newCompleted[i] = completed[i];
    }

    delete [] tasks; //Freeing up the old task array
    delete [] completed; // Freeing old statuses

    tasks = newTasks;           // Switch to a new array
    completed = newCompleted;
    capacity = newCapacity;     // Обновляем вместимость
}