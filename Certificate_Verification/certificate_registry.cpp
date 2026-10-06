/*
 * ============================================================================
 * UNIVERSITY OF EMBU
 * 2026/2027 ACADEMIC YEAR
 * Practical 1 - Assignment 2: School Certificate Verification System
 * System 1: National Examination / Centre Certificate Registry System
 * ============================================================================
 * Scenario:
 * - Stores authentic examination and certificate records in a C++ array.
 * - Used by registry administrators to manage secondary school examination records.
 * - Records stored: Examination/index number, Student name, Examination year,
 *   School/centre, Grade, and Certificate status.
 * - Maximum capacity: 20 records (array-based storage).
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Maximum capacity of the registry array (20 records)
const int MAX_CERTIFICATES = 20;

// Struct to represent a single examination certificate record
struct Certificate {
    string indexNumber;   // Examination/index number (e.g. KCSE001)
    string studentName;   // Candidate full name (e.g. Brian)
    int examYear;         // Examination year (e.g. 2025)
    string schoolCentre;  // Secondary school or examination centre
    string grade;         // Grade achieved (e.g. A-, B+, C)
    string status;        // Certificate validity status (VALID / SUSPENDED / CANCELLED)
};

// Function Prototypes
int findCertificateIndex(const Certificate registry[], int count, const string& indexNumber);
void addCertificate(Certificate registry[], int& count);
void searchCertificate(const Certificate registry[], int count);
void updateCertificate(Certificate registry[], int count);
void displayCertificates(const Certificate registry[], int count);

int main() {
    Certificate registry[MAX_CERTIFICATES];
    int count = 0;

    // Pre-populate sample certificates for demonstration
    registry[0] = {"KCSE001", "Brian", 2025, "Alliance High School", "A-", "VALID"};
    registry[1] = {"KCSE002", "Mary Wanjiku", 2024, "Kenya High School", "B+", "VALID"};
    registry[2] = {"KCSE003", "John Kamau", 2023, "Nairobi School", "D+", "SUSPENDED"};
    count = 3;

    int choice;
    do {
        cout << "\n======================================================\n";
        cout << "                 UNIVERSITY OF EMBU                   \n";
        cout << "   National Examination Certificate Registry System   \n";
        cout << "======================================================\n";
        cout << "1. Add a certificate record\n";
        cout << "2. Search for a certificate (by index number)\n";
        cout << "3. Update a certificate record\n";
        cout << "4. Display all certificate records\n";
        cout << "5. Exit Registry System\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 1 and 5.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addCertificate(registry, count);
                break;
            case 2:
                searchCertificate(registry, count);
                break;
            case 3:
                updateCertificate(registry, count);
                break;
            case 4:
                displayCertificates(registry, count);
                break;
            case 5:
                cout << "Exiting National Examination Registry System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please select between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

// Linear search helper: returns index if found, else -1
int findCertificateIndex(const Certificate registry[], int count, const string& indexNumber) {
    for (int i = 0; i < count; i++) {
        if (registry[i].indexNumber == indexNumber) {
            return i;
        }
    }
    return -1;
}

// 1. Add Certificate Record
void addCertificate(Certificate registry[], int& count) {
    if (count >= MAX_CERTIFICATES) {
        cout << "\n[Registry Error]: Storage full! Maximum capacity of " << MAX_CERTIFICATES << " records reached.\n";
        return;
    }

    string indexNo;
    cout << "\nEnter Examination / Index Number (e.g. KCSE004): ";
    cin >> indexNo;

    // Prevent duplicate index numbers
    if (findCertificateIndex(registry, count, indexNo) != -1) {
        cout << "[Registry Error]: A certificate with Index Number '" << indexNo << "' already exists!\n";
        return;
    }

    registry[count].indexNumber = indexNo;
    cin.ignore(10000, '\n');

    cout << "Enter Student Full Name: ";
    getline(cin, registry[count].studentName);

    while (true) {
        cout << "Enter Examination Year (1950 - 2030): ";
        if (cin >> registry[count].examYear && registry[count].examYear >= 1950 && registry[count].examYear <= 2030) {
            break;
        } else {
            cout << "Invalid year! Please enter a valid 4-digit year.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cin.ignore(10000, '\n');

    cout << "Enter School / Centre Name: ";
    getline(cin, registry[count].schoolCentre);

    cout << "Enter Grade Achieved (e.g. A, B+, C): ";
    cin >> registry[count].grade;

    cout << "Enter Status (VALID / SUSPENDED / CANCELLED): ";
    cin >> registry[count].status;

    count++;
    cout << "\n[Registry Success]: Certificate record added successfully! (Total: " << count << "/" << MAX_CERTIFICATES << ")\n";
}

// 2. Search Certificate Record
void searchCertificate(const Certificate registry[], int count) {
    if (count == 0) {
        cout << "\n[Registry]: No certificate records in the registry.\n";
        return;
    }

    string indexNo;
    cout << "\nEnter Examination / Index Number to search: ";
    cin >> indexNo;

    int idx = findCertificateIndex(registry, count, indexNo);

    if (idx == -1) {
        cout << "[Registry]: No record found for Index Number: " << indexNo << "\n";
        return;
    }

    cout << "\n--- Official Certificate Record ---\n";
    cout << "Index Number  : " << registry[idx].indexNumber << "\n";
    cout << "Student Name  : " << registry[idx].studentName << "\n";
    cout << "Exam Year     : " << registry[idx].examYear << "\n";
    cout << "School/Centre : " << registry[idx].schoolCentre << "\n";
    cout << "Grade         : " << registry[idx].grade << "\n";
    cout << "Status        : " << registry[idx].status << "\n";
}

// 3. Update Certificate Record
void updateCertificate(Certificate registry[], int count) {
    if (count == 0) {
        cout << "\n[Registry]: No records available to update.\n";
        return;
    }

    string indexNo;
    cout << "\nEnter Examination / Index Number to update: ";
    cin >> indexNo;

    int idx = findCertificateIndex(registry, count, indexNo);

    if (idx == -1) {
        cout << "[Registry Error]: Certificate with Index Number '" << indexNo << "' not found.\n";
        return;
    }

    cout << "\nUpdating record for " << registry[idx].studentName << "\n";
    cout << "Current Grade: " << registry[idx].grade << " | Current Status: " << registry[idx].status << "\n";

    cout << "Enter New Grade: ";
    cin >> registry[idx].grade;

    cout << "Enter New Status (VALID / SUSPENDED / CANCELLED): ";
    cin >> registry[idx].status;

    cout << "[Registry Success]: Certificate record updated successfully!\n";
}

// 4. Display All Stored Certificates
void displayCertificates(const Certificate registry[], int count) {
    if (count == 0) {
        cout << "\n[Registry]: Registry is currently empty.\n";
        return;
    }

    cout << "\n=========================================================================================\n";
    cout << left << setw(12) << "Index No"
         << setw(20) << "Student Name"
         << setw(8)  << "Year"
         << setw(26) << "School/Centre"
         << setw(8)  << "Grade"
         << setw(12) << "Status" << "\n";
    cout << "=========================================================================================\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(12) << registry[i].indexNumber
             << setw(20) << registry[i].studentName
             << setw(8)  << registry[i].examYear
             << setw(26) << registry[i].schoolCentre
             << setw(8)  << registry[i].grade
             << setw(12) << registry[i].status << "\n";
    }

    cout << "=========================================================================================\n";
    cout << "Total Records Stored: " << count << " / " << MAX_CERTIFICATES << "\n";
}
