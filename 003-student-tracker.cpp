#include <iostream>

/*
 * =============================
 * Student Tracker C++ Mini Project
 * =============================
 *
 * A simple console-based student management system written in C++.
 * Demonstrates the use of dynamic arrays to manage a list of students
 * and their average scores.
 *
 * Features:
 * ✅ Add students with name and average score
 * ✅ Remove students by index
 * ✅ Display current list of students
 * ✅ Dynamic array resizing when full
 * ✅ Input validation for numeric choices
 *
 * Memory Management:
 * Uses raw pointers and manual memory handling to demonstrate how
 * dynamic arrays work in C++.
 */

using namespace std;

struct Student {
    string name;
    double avgScore;
};

void addStudent(Student*& arr, int& size, int& capacity);
void removeStudent(Student*& arr, int& size);
void showStudent(const Student* const arr, const int size);

int main () {
    Student* student = nullptr;
    int size = 0;
    int capacity = 0;

    while (true) {
        cout<<"==== Menu ====\n";
        cout<<"1. Add Student\n";
        cout<<"2. Remove Students\n";
        cout<<"3. Show list\n";
        cout<<"4. Exit\n";

        int choice;
        while (true) {
            cout<<"Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();           // сброс ошибки
                cin.ignore(10000, '\n'); // очистка буфера
                cout << "Invalid input. Numbers only.\n";
            } else {
                break;
            }
        }
        if (choice == 1)
            addStudent(student, size, capacity);
        else if (choice == 2)
            removeStudent(student, size);
        else if (choice == 3)
            showStudent(student, size);
        else if (choice == 4)
            break;
        else
            cout<<"Invalid choice\n";
    }

    delete[] student;
    return 0;
}

void addStudent(Student*& arr, int& size, int& capacity) {
    if (size >= capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        Student* temp = new Student[capacity];
        for (int i = 0; i < size; i++)
            temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }

    cin.ignore();
    cout<<"Enter name: ";
    getline(cin, arr[size].name);

    cout<<"Enter average score: ";
    cin>>arr[size].avgScore;

    cout<<"Student added!\n";

    ++size;
}

void removeStudent(Student*& arr, int& size) {
    if (size == 0) {
        cout<<"\nNo Student found\n";
    }

    cout<<"Enter index to remove(1 - " << size << "): ";
    int index;

    while (true) {
        cin >> index;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number: ";
        } else {
            break;
        }
    }

    if (index < 1 || index > size) {
        cout<<"Invalid index\n";
        return;
    }

    index--;

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    cout<<"Student removed!\n";

    --size;
}

void showStudent(const Student* const arr, const int size) {
    if (size == 0) {
        cout<<"\nNo Student found\n";
    }

    cout<<"\nStudent List:\n";
    for (int i = 0; i < size; i++)
        cout<<i+1<<". "<<arr[i].name<<" | Ave Score: "<<arr[i].avgScore<<endl;

    cout<<endl;
}