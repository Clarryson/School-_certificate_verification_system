/*
 * ============================================================================
 * 
 * 2026/2027 ACADEMIC YEAR
 *  Student Array
 * ============================================================================
 * Requirements from Assignment Document:
 * - Create an array capable of storing a maximum of 20 students.
 * - Each student must contain:
 *     1. Registration number (e.g., CSM001)
 *     2. Name (e.g., Brian)
 *     3. Marks (e.g., 78)
 * - The program must allow the user to:
 *     1. Add a student
 *     2. Delete a student (shifts remaining students to eliminate gaps)
 *     3. Update a student's marks
 *     4. Search for a student (by registration number)
 *     5. Display all students
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Maximum capacity of the array (strictly 20)
const int MAX_STUDENTS = 20;

// Struct to represent a single student record
struct Student {
    string regNumber; // e.g., CSM001
    string name;      // e.g., Brian
    double marks;     // e.g., 78
};

// Function prototypes
int findStudentIndex(const Student students[], int count, const string& regNumber);
void addStudent(Student students[], int& count);
void deleteStudent(Student students[], int& count);
void updateMarks(Student students[], int count);
void searchStudent(const Student students[], int count);
void displayStudents(const Student students[], int count);

int main() {
    Student students[MAX_STUDENTS]; // Fixed-size array for up to 20 students
    int count = 0;                  // Tracks the current number of students in the array
    int choice;

    do {
        // Interactive menu matching University of Embu specifications
        cout << "\n======================================================\n";
        cout << "                 UNIVERSITY OF EMBU                   \n";
        cout << "           Assignment 1: Student Array                \n";
        cout << "======================================================\n";
        cout << "1. Add a student\n";
        cout << "2. Delete a student\n";
        cout << "3. Update a student's marks\n";
        cout << "4. Search for a student\n";
        cout << "5. Display all students\n";
        cout << "6. Exit\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter your choice (1-6): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                deleteStudent(students, count);
                break;
            case 3:
                updateMarks(students, count);
                break;
            case 4:
                searchStudent(students, count);
                break;
            case 5:
                displayStudents(students, count);
                break;
            case 6:
                cout << "Exiting Assignment 1 (Student Array). Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please select an option between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}

// Linear search helper: finds student by registration number
// Returns index (0 to count-1) if found, or -1 if not found
int findStudentIndex(const Student students[], int count, const string& regNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].regNumber == regNumber) {
            return i;
        }
    }
    return -1;
}

// 1. Add a student
void addStudent(Student students[], int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "\n[Error]: Cannot add student. Maximum capacity of " << MAX_STUDENTS << " reached.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number (e.g. CSM001): ";
    cin >> regNo;

    // Ensure registration number is unique
    if (findStudentIndex(students, count, regNo) != -1) {
        cout << "[Error]: A student with Registration Number '" << regNo << "' already exists!\n";
        return;
    }

    students[count].regNumber = regNo;

    cin.ignore(10000, '\n'); // Clear buffer for multi-word name
    cout << "Enter Student Name (e.g. Brian): ";
    getline(cin, students[count].name);

    // Validate marks
    double marks;
    while (true) {
        cout << "Enter Marks (0 - 100, e.g. 78): ";
        if (cin >> marks && marks >= 0.0 && marks <= 100.0) {
            students[count].marks = marks;
            break;
        } else {
            cout << "Invalid marks! Please enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    count++;
    cout << "[Success]: Student added successfully! (Stored: " << count << "/" << MAX_STUDENTS << ")\n";
}

// 2. Delete a student (shifts remaining students to eliminate empty gaps)
void deleteStudent(Student students[], int& count) {
    if (count == 0) {
        cout << "\n[Notice]: No students available to delete.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to delete: ";
    cin >> regNo;

    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "[Error]: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    // Shift all subsequent students one position to the left
    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;
    cout << "[Success]: Student '" << regNo << "' deleted successfully.\n";
}

// 3. Update a student's marks
void updateMarks(Student students[], int count) {
    if (count == 0) {
        cout << "\n[Notice]: No students available to update.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to update marks: ";
    cin >> regNo;

    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "[Error]: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    cout << "Current Marks for " << students[index].name << ": " << students[index].marks << "\n";

    double newMarks;
    while (true) {
        cout << "Enter New Marks (0 - 100): ";
        if (cin >> newMarks && newMarks >= 0.0 && newMarks <= 100.0) {
            students[index].marks = newMarks;
            break;
        } else {
            cout << "Invalid marks! Please enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cout << "[Success]: Marks updated successfully!\n";
}

// 4. Search for a student
void searchStudent(const Student students[], int count) {
    if (count == 0) {
        cout << "\n[Notice]: No students stored to search.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to search: ";
    cin >> regNo;

    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "[Error]: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    cout << "\n--- Student Record Found ---\n";
    cout << "Registration Number : " << students[index].regNumber << "\n";
    cout << "Name                : " << students[index].name << "\n";
    cout << "Marks               : " << fixed << setprecision(2) << students[index].marks << "\n";
}

// 5. Display all students
void displayStudents(const Student students[], int count) {
    if (count == 0) {
        cout << "\n[Notice]: No student records to display.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << left << setw(8)  << "Index"
         << setw(18) << "Reg Number"
         << setw(24) << "Name"
         << right << setw(8)  << "Marks" << "\n";
    cout << "============================================================\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(8)  << (i + 1)
             << setw(18) << students[i].regNumber
             << setw(24) << students[i].name
             << right << setw(8)  << fixed << setprecision(2) << students[i].marks << "\n";
    }

    cout << "============================================================\n";
    cout << "Total Students: " << count << " / " << MAX_STUDENTS << "\n";
}
