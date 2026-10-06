
## School Certificate Verification System

This directory contains the complete implementation for School Certificate Verification System** b
---

## Scenario & System Architecture

A university receives applications from students who claim to have completed secondary school. Before admitting a student, the university wants to verify whether the presented examination certificate is genuine.

This project implements two communicating systems using **C++ arrays**:

```text
Admission Officer
       │
       ▼ (1. Enters examination/index number)
University Admission System (System 2)
       │
       ▼ (2. Requests verification via requestRegistryVerification())
National Examination/Centre Certificate Registry (System 1)
       │
       ▼ (3. Searches internal certificate array)
       │
       ▼ (4. Returns VerificationResponse packet)
University Admission System (System 2)
       │
       ▼ (5. Evaluates validity & displays admission decision)
```

---

## Files in this Directory

| File | System | Description |
| :--- | :--- | :--- |
| **`certificate_registry.cpp`** | **System 1: National Examination Registry** | Stores and manages authentic certificates in an array of up to 20 records. Allows adding, searching, updating, and displaying records. Enforces unique index numbers. |
| **`admission_system.cpp`** | **System 2: University Admission System** | Used by an admission officer to verify applicant certificates by sending requests to the Registry interface and processing the returned response. |

---

## How to Compile and Run

From this folder (`Assignment2_Certificate_Verification`):

### 1. Run the National Examination Registry System (System 1)
```bash
# Compile
g++ -std=c++11 certificate_registry.cpp -o certificate_registry

# Run
./certificate_registry
```

### 2. Run the University Admission System (System 2)
```bash
# Compile
g++ -std=c++11 admission_system.cpp -o admission_system

# Run
./admission_system
```

---

## Sample Test Verification Cases (for `admission_system.cpp`)

1. **Valid Certificate**:
   * Enter Index: `KCSE001`
   * **Result**: Found for **Brian**, Status: `VALID`. Admission approved.
2. **Suspended Certificate**:
   * Enter Index: `KCSE003`
   * **Result**: Found for **John Kamau**, Status: `SUSPENDED`. Admission flagged on hold.
3. **Unverified / Fraudulent Certificate**:
   * Enter Index: `KCSE999`
   * **Result**: Record NOT found. Warning of possible fraudulent certificate.
