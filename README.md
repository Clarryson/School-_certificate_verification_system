# Student Management & School Certificate Verification System

A C++ repository featuring two modular practical systems implementing fixed-size array data structures, record management, linear search, and simulated inter-system certificate verification.

---

## Repository Structure

```text
student_CPP/
├── Student_Array/
│   ├── student_array.cpp           # Assignment 1: Student Array record management
│   └── README.md                   # Instructions & documentation for Assignment 1
│
├── Certificate_Verification/
│   ├── certificate_registry.cpp    # Assignment 2 (System 1): National Examination Registry
│   ├── admission_system.cpp        # Assignment 2 (System 2): University Admission System
│   └── README.md                   # Instructions & documentation for Assignment 2
│
├── .gitignore                      # Git ignore rules for build artifacts & executables
└── README.md                       # Main project overview & instructions
```

---

## Projects Overview

### 1. [Student Array System](Student_Array/README.md)
* **Directory**: [`Student_Array/`](Student_Array/)
* **Source**: [`student_array.cpp`](Student_Array/student_array.cpp)
* **Features**:
  * Stores up to 20 students in a fixed-size array.
  * Supported operations: Add student (unique ID validation), Delete student (left array compaction to avoid gaps), Update marks, Linear search by registration number, and Formatted tabular display.

### 2. [School Certificate Verification System](Certificate_Verification/README.md)
* **Directory**: [`Certificate_Verification/`](Certificate_Verification/)
* **Sources**:
  * [`certificate_registry.cpp`](Certificate_Verification/certificate_registry.cpp): System 1 (National Examination Registry) storing official certificate records.
  * [`admission_system.cpp`](Certificate_Verification/admission_system.cpp): System 2 (University Admission Verification System) that queries the registry interface to verify secondary school certificates before clearing applicants for admission.
* **Features**:
  * Simulated client-registry request-response packet structure (`VerificationResponse`).
  * Handles genuine/valid, suspended, and fraudulent/unregistered certificate scenarios.

---

## Prerequisites

* **C++ Compiler**: GCC (`g++`) with C++11 support or later.

Check installation:
```bash
g++ --version
```

---

## Quick Start: Compile and Run

You can compile and run all programs directly from the project root:

### Assignment 1: Student Array
```bash
# Compile
g++ -std=c++11 Student_Array/student_array.cpp -o Student_Array/student_array

# Run
./Student_Array/student_array
```

### Assignment 2: Certificate Registry (System 1)
```bash
# Compile
g++ -std=c++11 Certificate_Verification/certificate_registry.cpp -o Certificate_Verification/certificate_registry

# Run
./Certificate_Verification/certificate_registry
```

### Assignment 2: University Admission System (System 2)
```bash
# Compile
g++ -std=c++11 Certificate_Verification/admission_system.cpp -o Certificate_Verification/admission_system

# Run
./Certificate_Verification/admission_system
```

---

## License & Attribution

Academic coursework implementation for C++ Array Data Structures and Verification Systems.
