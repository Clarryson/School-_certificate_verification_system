# Student Array System

This directory contains the complete C++ implementation for the **Student Array System**.

---

## Overview & Requirements

* **Storage**: Fixed-size C++ array storing a maximum of **20 students** (`MAX_STUDENTS = 20`).
* **Student Record Structure**:
  * **Registration Number**: string (e.g., `CSM001`) - unique identifier
  * **Name**: string (e.g., `Brian`)
  * **Marks**: double (0.00 – 100.00, e.g., `78.00`)

* **Supported Operations**:
  1. **Add a student**: Appends a new record if capacity allows; verifies uniqueness of registration number; validates marks in the range 0–100.
  2. **Delete a student**: Locates the student by registration number, removes the record, and shifts subsequent elements left to eliminate gaps.
  3. **Update a student's marks**: Searches for a student by registration number and updates their score with input validation.
  4. **Search for a student**: Linear search by registration number, displaying matching student details.
  5. **Display all students**: Renders all currently stored students in a formatted tabular layout.
  6. **Exit**: Gracefully exits the application.

---

## How to Compile and Run

### Option 1: From this directory (`Student_Array`)

```bash
cd Student_Array

# Compile
g++ -std=c++11 student_array.cpp -o student_array

# Run
./student_array
```

### Option 2: From the project root

```bash
# Compile
g++ -std=c++11 Student_Array/student_array.cpp -o Student_Array/student_array

# Run
./Student_Array/student_array
```

---

## Sample Program Flow

```text
======================================================
                 UNIVERSITY
           Assignment 1: Student Array
======================================================
1. Add a student
2. Delete a student
3. Update a student's marks
4. Search for a student
5. Display all students
6. Exit
------------------------------------------------------
Enter your choice (1-6): 5

============================================================
Index   Reg Number        Name                       Marks
============================================================
1       CSM001            Brian                      78.00
2       CSM002            Mary Wanjiku               85.50
============================================================
Total Students: 2 / 20
```
