#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Maximum capacity of the array
const int MAX_STUDENTS = 20;

// Struct to represent a single student
struct Student {
    string regNumber;
    string name;
    double marks;
};

// Function prototypes
int findStudentIndex(const Student students[], int count, const string& regNumber);
void addStudent(Student students[], int& count);
void deleteStudent(Student students[], int& count);
void updateMarks(Student students[], int count);
void searchStudent(const Student students[], int count);
void displayStudents(const Student students[], int count);

int main() {
    Student students[MAX_STUDENTS]; // Fixed-size array to store up to 20 students
    int count = 0;                  // Tracks the current number of students in the array
    int choice;

    do {
        // Display the menu
        cout << "\n========================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM        \n";
        cout << "========================================\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Update Student Marks\n";
        cout << "4. Search for a Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice (1-6): ";
        
        if (!(cin >> choice)) {
            // Handle non-numeric input
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
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please select an option between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}

// Helper function: Finds the index of a student by registration number
// Returns index if found (0 to count-1), or -1 if not found
int findStudentIndex(const Student students[], int count, const string& regNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].regNumber == regNumber) {
            return i; // Found at index i
        }
    }
    return -1; // Not found
}

// 1. Function to add a student
void addStudent(Student students[], int& count) {
    // Check if the array is already full
    if (count >= MAX_STUDENTS) {
        cout << "\nError: Cannot add student. Maximum capacity of " << MAX_STUDENTS << " reached.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number: ";
    cin >> regNo;

    // Check if registration number is unique
    if (findStudentIndex(students, count, regNo) != -1) {
        cout << "Error: A student with Registration Number '" << regNo << "' already exists!\n";
        return;
    }

    students[count].regNumber = regNo;

    // Clear input buffer before reading string with spaces
    cin.ignore(10000, '\n');

    cout << "Enter Student Name: ";
    getline(cin, students[count].name);

    // Validate marks input (ensure it's between 0 and 100)
    double marks;
    while (true) {
        cout << "Enter Marks (0 - 100): ";
        if (cin >> marks && marks >= 0.0 && marks <= 100.0) {
            students[count].marks = marks;
            break;
        } else {
            cout << "Invalid marks! Please enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // Increment count after successfully adding the student
    count++;
    cout << "Student added successfully! (Total students: " << count << "/" << MAX_STUDENTS << ")\n";
}

// 2. Function to delete a student
void deleteStudent(Student students[], int& count) {
    // Check if the array is empty
    if (count == 0) {
        cout << "\nNo students available to delete.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to delete: ";
    cin >> regNo;

    // Find the student's index
    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "Error: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    // Shift all subsequent students one position to the left to remove gap
    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    // Decrease the student count
    count--;
    cout << "Student with Registration Number '" << regNo << "' deleted successfully.\n";
}

// 3. Function to update student marks
void updateMarks(Student students[], int count) {
    // Check if the array is empty
    if (count == 0) {
        cout << "\nNo students available to update.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to update marks: ";
    cin >> regNo;

    // Find the student's index
    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "Error: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    cout << "Current Marks for " << students[index].name << ": " << students[index].marks << "\n";

    // Validate and update new marks
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

    cout << "Marks updated successfully!\n";
}

// 4. Function to search for a student
void searchStudent(const Student students[], int count) {
    // Check if the array is empty
    if (count == 0) {
        cout << "\nNo students in the system to search.\n";
        return;
    }

    string regNo;
    cout << "\nEnter Registration Number to search: ";
    cin >> regNo;

    // Find the student's index
    int index = findStudentIndex(students, count, regNo);

    if (index == -1) {
        cout << "Error: Student with Registration Number '" << regNo << "' not found.\n";
        return;
    }

    // Display student details
    cout << "\n--- Student Details Found ---\n";
    cout << "Registration Number: " << students[index].regNumber << "\n";
    cout << "Name               : " << students[index].name << "\n";
    cout << "Marks              : " << fixed << setprecision(2) << students[index].marks << "\n";
}

// 5. Function to display all students
void displayStudents(const Student students[], int count) {
    // Check if the array is empty
    if (count == 0) {
        cout << "\nNo student records to display.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << left << setw(8) << "Index"
         << setw(18) << "Reg Number"
         << setw(24) << "Name"
         << right << setw(8) << "Marks" << "\n";
    cout << "============================================================\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(8) << (i + 1)
             << setw(18) << students[i].regNumber
             << setw(24) << students[i].name
             << right << setw(8) << fixed << setprecision(2) << students[i].marks << "\n";
    }

    cout << "============================================================\n";
    cout << "Total Students: " << count << "/" << MAX_STUDENTS << "\n";
}
