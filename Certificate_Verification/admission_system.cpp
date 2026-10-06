/*
 * ============================================================================
 * UNIVERSITY 
 * 2026/2027 ACADEMIC YEAR
 * School Certificate Verification System
 * System 2: University Admission System (Used by Admission Officer)
 * ============================================================================
 * Scenario:
 * - A university receives applications from students who claim to have completed
 *   secondary school.
 * - Before admitting a student, the university verifies whether the presented
 *   examination certificate is genuine.
 * - This Admission System sends a verification request to the National Examination
 *   Registry System and processes the response.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Maximum capacity of the registry array
const int MAX_CERTIFICATES = 20;

// Struct to represent a single certificate record
struct Certificate {
    string indexNumber;   // Examination/index number
    string studentName;   // Candidate full name
    int examYear;         // Examination year
    string schoolCentre;  // Name of secondary school or centre
    string grade;         // Grade achieved (e.g. A-, B+, C)
    string status;        // Certificate validity status (VALID / SUSPENDED / CANCELLED)
};

// Response packet sent back from the National Examination Registry
struct VerificationResponse {
    bool found;           // true if matching certificate exists in registry
    Certificate certData; // Authentic certificate details returned by registry
};

// =========================================================================
// SIMULATED REGISTRY SERVICE ENDPOINT
// This function models the communication interface to the Registry.
// The Admission System requests certificate verification and receives
// a VerificationResponse packet without directly manipulating the registry array.
// =========================================================================
VerificationResponse requestRegistryVerification(const Certificate registry[], int count, const string& indexNumber) {
    VerificationResponse response;
    response.found = false;

    // The Registry searches its internal array of certificates
    for (int i = 0; i < count; i++) {
        if (registry[i].indexNumber == indexNumber) {
            response.found = true;
            response.certData = registry[i];
            break;
        }
    }

    return response;
}

// =============================================================
// UNIVERSITY ADMISSION SYSTEM FUNCTIONS
// =============================================================

// Verification flow for the admission officer
void verifyApplicantCertificate(const Certificate registry[], int registryCount) {
    string indexNumber;

    cout << "\n======================================================\n";
    cout << "          APPLICANT CERTIFICATE VERIFICATION          \n";
    cout << "======================================================\n";
    cout << "Admission Officer: Enter applicant's index number: ";
    cin >> indexNumber;

    // --- STEP 1: ADMISSION SYSTEM SENDS REQUEST ---
    cout << "\n[Admission System] -> Sending verification request for Index: " << indexNumber << "...\n";

    // --- STEP 2: REGISTRY SEARCHES AND SENDS RESPONSE ---
    cout << "[Registry System]  -> Request received. Searching national examination records...\n";
    VerificationResponse response = requestRegistryVerification(registry, registryCount, indexNumber);

    // --- STEP 3: ADMISSION SYSTEM RECEIVES AND EVALUATES RESPONSE ---
    cout << "[Admission System] -> Response packet received from Registry.\n";
    cout << "------------------------------------------------------\n";

    if (response.found) {
        cout << "Registry Verification Status: RECORD FOUND\n\n";
        cout << "---- OFFICIAL EXAMINATION CERTIFICATE DETAILS ----\n";
        cout << "Candidate Name : " << response.certData.studentName << "\n";
        cout << "School / Centre: " << response.certData.schoolCentre << "\n";
        cout << "Exam Year      : " << response.certData.examYear << "\n";
        cout << "Grade Awarded  : " << response.certData.grade << "\n";
        cout << "Official Status: " << response.certData.status << "\n";
        cout << "------------------------------------------------------\n";

        // Decision logic
        if (response.certData.status == "VALID") {
            cout << "ADMISSION DECISION:\n";
            cout << ">> [VERIFIED]: Certificate is GENUINE and VALID.\n";
            cout << ">> Applicant is cleared to proceed with university admission.\n";
        } else {
            cout << "ADMISSION DECISION:\n";
            cout << ">> [WARNING]: Record found, but official status is '" 
                 << response.certData.status << "'.\n";
            cout << ">> [ON HOLD]: Admission is placed on hold pending institutional review.\n";
        }
    } else {
        cout << "Registry Verification Status: RECORD NOT FOUND\n\n";
        cout << "ADMISSION DECISION:\n";
        cout << ">> [REJECTED]: Certificate could NOT be verified.\n";
        cout << ">> No matching examination record found in National Registry.\n";
        cout << ">> Warning: Possible fraudulent certificate or invalid index number.\n";
    }
}

int main() {
    // Array holding authentic records at the National Examination Registry
    Certificate registryDatabase[MAX_CERTIFICATES];
    int registryCount = 3;

    // Pre-loaded authentic records
    registryDatabase[0] = {"KCSE001", "Brian", 2025, "Alliance High School", "A-", "VALID"};
    registryDatabase[1] = {"KCSE002", "Mary Wanjiku", 2024, "Kenya High School", "B+", "VALID"};
    registryDatabase[2] = {"KCSE003", "John Kamau", 2023, "Nairobi School", "D+", "SUSPENDED"};

    int choice;
    do {
        cout << "\n======================================================\n";
        cout << "                 UNIVERSITY OF EMBU                   \n";
        cout << "             University Admission System              \n";
        cout << "======================================================\n";
        cout << "1. Verify an applicant's certificate\n";
        cout << "2. Exit\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice (1-2): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                verifyApplicantCertificate(registryDatabase, registryCount);
                break;
            case 2:
                cout << "Exiting University Admission System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Enter 1 or 2.\n";
        }
    } while (choice != 2);

    return 0;
}
