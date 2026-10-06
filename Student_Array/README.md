
 Student Array

This directory contains the complete implementation for ** Student Array** 
---

## Assignment Requirements
* Store a maximum of **20 students** in a fixed-size C++ array.
* Each student contains:
  * Registration number (e.g., `CSM001`)
  * Name (e.g., `Brian`)
  * Marks (e.g., `78`)
* Supported Operations:
  1. Add a student (prevents overflow > 20, ensures unique registration numbers)
  2. Delete a student (shifts subsequent students left to leave no gaps)
  3. Update a student's marks
  4. Search for a student by registration number
  5. Display all stored students in a formatted table

---

## How to Compile and Run

From this folder (`Assignment1_Student_Array`):

```bash
# Compile
g++ -std=c++11 student_array.cpp -o student_array

# Run
./student_array
```
