#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Maximum number of certificate records allowed in the registry
const int MAX_CERTIFICATES = 20;

// Struct to represent a single Examination Certificate
struct Certificate {
    string indexNumber;   // Unique examination/index number (e.g., KCSE001)
    string studentName;   // Full name of the student
    int examYear;         // Year the exam was taken (e.g., 2025)
    string schoolCentre;  // High school or examination centre name
    string grade;         // Grade achieved (e.g., A, B+, C)
    string status;        // Certificate status: "VALID", "SUSPENDED", "CANCELLED"
};

// Struct used as a response packet from Registry to Admission System
// This represents the message sent between the two systems
struct VerificationResponse {
    bool found;               // true if record exists, false otherwise
    Certificate certData;     // The certificate details if found
};

// =============================================================
// FUNCTION PROTOTYPES
// =============================================================

// Registry Helper Function
int findCertificateIndex(const Certificate registry[], int count, const string& indexNumber);

// System 1: Registry Functions
void addCertificate(Certificate registry[], int& count);
void searchCertificate(const Certificate registry[], int count);
void displayCertificates(const Certificate registry[], int count);
void updateCertificate(Certificate registry[], int count);
void registryMenu(Certificate registry[], int& count);

// Communication Interface (Simulated Service Request/Response)
VerificationResponse registryProcessRequest(const Certificate registry[], int count, const string& indexNumber);

// System 2: University Admission System Functions
void verifyApplicantCertificate(const Certificate registry[], int count);
void admissionMenu(const Certificate registry[], int count);

// Main Program
int main() {
    // Array to store certificate records (System 1 database)
    Certificate registry[MAX_CERTIFICATES];
    int certificateCount = 0;

    // Optional: Pre-populate 3 sample certificates so the program can be tested immediately
    registry[0] = {"KCSE001", "Brian Otieno", 2025, "Alliance High School", "A-", "VALID"};
    registry[1] = {"KCSE002", "Mary Wanjiku", 2024, "Kenya High School", "B+", "VALID"};
    registry[2] = {"KCSE003", "John Kamau", 2023, "Nairobi School", "D+", "SUSPENDED"};
    certificateCount = 3;

    int topChoice;

    do {
        cout << "\n======================================================\n";
        cout << "     SCHOOL CERTIFICATE VERIFICATION SYSTEM           \n";
        cout << "======================================================\n";
        cout << "Select which system you want to access:\n";
        cout << "1. National Examination Registry System (Admin)\n";
        cout << "2. University Admission System (Admission Officer)\n";
        cout << "3. Exit Program\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice (1-3): ";

        if (!(cin >> topChoice)) {
            cout << "Invalid input! Please enter 1, 2, or 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (topChoice) {
            case 1:
                registryMenu(registry, certificateCount);
                break;
            case 2:
                admissionMenu(registry, certificateCount);
                break;
            case 3:
                cout << "\nShutting down both systems. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please choose between 1 and 3.\n";
        }

    } while (topChoice != 3);

    return 0;
}

// =============================================================
// SYSTEM 1: REGISTRY HELPER & CORE FUNCTIONS
// =============================================================

// Linear search helper: returns index (0 to count-1) if found, else -1
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
    cout << "\nEnter Examination / Index Number: ";
    cin >> indexNo;

    // Check for duplicate index number
    if (findCertificateIndex(registry, count, indexNo) != -1) {
        cout << "[Registry Error]: A certificate with Index Number '" << indexNo << "' already exists!\n";
        return;
    }

    registry[count].indexNumber = indexNo;

    // Clear input buffer before reading multi-word strings
    cin.ignore(10000, '\n');

    cout << "Enter Student Full Name: ";
    getline(cin, registry[count].studentName);

    // Validate examination year
    while (true) {
        cout << "Enter Examination Year (e.g. 2020 - 2026): ";
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
        cout << "\n[Registry]: No certificate records exist in the registry.\n";
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

    cout << "\n--- Registry Certificate Record ---\n";
    cout << "Index Number : " << registry[idx].indexNumber << "\n";
    cout << "Student Name : " << registry[idx].studentName << "\n";
    cout << "Exam Year    : " << registry[idx].examYear << "\n";
    cout << "School/Centre: " << registry[idx].schoolCentre << "\n";
    cout << "Grade        : " << registry[idx].grade << "\n";
    cout << "Status       : " << registry[idx].status << "\n";
}

// 3. Display All Certificates
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

// 4. Update Certificate Record
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

    cout << "\nUpdating record for " << registry[idx].studentName << " (Current Grade: "
         << registry[idx].grade << ", Status: " << registry[idx].status << ")\n";

    cout << "Enter New Grade: ";
    cin >> registry[idx].grade;

    cout << "Enter New Status (VALID / SUSPENDED / CANCELLED): ";
    cin >> registry[idx].status;

    cout << "[Registry Success]: Record updated successfully!\n";
}

// Registry Sub-Menu Loop
void registryMenu(Certificate registry[], int& count) {
    int choice;
    do {
        cout << "\n------------------------------------------------------\n";
        cout << "   NATIONAL EXAMINATION CERTIFICATE REGISTRY SYSTEM   \n";
        cout << "------------------------------------------------------\n";
        cout << "1. Add Certificate Record\n";
        cout << "2. Search Certificate Record\n";
        cout << "3. Update Certificate Record\n";
        cout << "4. Display All Stored Certificates\n";
        cout << "5. Return to Main Menu\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
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
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Select an option from 1 to 5.\n";
        }
    } while (choice != 5);
}

// =========================================================================
// COMMUNICATION INTERFACE: SIMULATED REQUEST & RESPONSE BETWEEN THE SYSTEMS
// =========================================================================
// The Admission System calls this function to ask the Registry for verification.
// The Registry searches its array and bundles the response into a VerificationResponse struct.
VerificationResponse registryProcessRequest(const Certificate registry[], int count, const string& indexNumber) {
    VerificationResponse response;

    // Simulate Registry processing the request
    int idx = findCertificateIndex(registry, count, indexNumber);

    if (idx != -1) {
        // Record exists in registry
        response.found = true;
        response.certData = registry[idx]; // Copy certificate details to the response packet
    } else {
        // Record does not exist in registry
        response.found = false;
    }

    return response;
}

// =============================================================
// SYSTEM 2: UNIVERSITY ADMISSION SYSTEM
// =============================================================

// Admission Officer verifies applicant certificate
void verifyApplicantCertificate(const Certificate registry[], int count) {
    string searchIndex;

    cout << "\n======================================================\n";
    cout << "       APPLICANT CERTIFICATE VERIFICATION             \n";
    cout << "======================================================\n";
    cout << "Admission System: Enter applicant's examination number: ";
    cin >> searchIndex;

    // --- STEP 1: SEND REQUEST ---
    cout << "\n[Admission System] -> Sending verification request for index: " << searchIndex << "...\n";

    // --- STEP 2: REGISTRY PROCESSES AND REPLIES ---
    cout << "[Registry System]  -> Request received. Searching national certificate records...\n";
    VerificationResponse response = registryProcessRequest(registry, count, searchIndex);

    // --- STEP 3: ADMISSION SYSTEM PROCESSES RESPONSE ---
    cout << "[Admission System] -> Response packet received from Registry.\n";
    cout << "------------------------------------------------------\n";

    if (response.found) {
        cout << "Registry Response Status: RECORD FOUND\n\n";
        cout << "---- CERTIFICATE DETAILS ----\n";
        cout << "Candidate Name : " << response.certData.studentName << "\n";
        cout << "School / Centre: " << response.certData.schoolCentre << "\n";
        cout << "Exam Year      : " << response.certData.examYear << "\n";
        cout << "Grade Awarded  : " << response.certData.grade << "\n";
        cout << "Official Status: " << response.certData.status << "\n";
        cout << "------------------------------------------------------\n";

        // Decision logic based on certificate status
        if (response.certData.status == "VALID") {
            cout << "ADMISSION DECISION:\n";
            cout << "SUCCESS: Certificate is genuine and verified.\n";
            cout << "Applicant is cleared to proceed with university admission processing.\n";
        } else {
            cout << "ADMISSION DECISION:\n";
            cout << "ALERT: Certificate record exists, but status is '" << response.certData.status << "'.\n";
            cout << "Admission officer review required before processing can continue.\n";
        }
    } else {
        cout << "Registry Response Status: RECORD NOT FOUND\n\n";
        cout << "ADMISSION DECISION:\n";
        cout << "FAILURE: Certificate could not be verified!\n";
        cout << "No matching examination record was found in the National Registry.\n";
        cout << "Suspected fraudulent claim or invalid index number.\n";
    }
}

// Admission Sub-Menu Loop
void admissionMenu(const Certificate registry[], int count) {
    int choice;
    do {
        cout << "\n------------------------------------------------------\n";
        cout << "             UNIVERSITY ADMISSION SYSTEM              \n";
        cout << "------------------------------------------------------\n";
        cout << "1. Verify Applicant Certificate\n";
        cout << "2. Return to Main Menu\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice (1-2): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                verifyApplicantCertificate(registry, count);
                break;
            case 2:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Select 1 or 2.\n";
        }
    } while (choice != 2);
}
