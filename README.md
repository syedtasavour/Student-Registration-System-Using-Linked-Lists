
# Student Registration System in C

This is a simple Student Registration System implemented in C, utilizing a linked list data structure. It allows users to register, view, search, update, and delete student records. The system provides a menu-driven interface for easy interaction.

## Features

- **Add Student**: Adds a new student record to the system.
- **View All Students**: Displays a list of all students.
- **Search Student**: Allows users to search for a student by their ID.
- **Update Student**: Enables updating the details of a student.
- **Delete Student**: Deletes a student record by their ID.
- **Count Total Students**: Displays the total number of students in the system.
- **Exit**: Exits the program.

## Data Structure

- The system uses a **singly linked list** to store student records.
- Each student record consists of the following details:
  - Student ID
  - Name
  - Age
  - Class
  - Department
  - Contact Information

## How to Use

1. Clone or download the repository to your local machine.
2. Compile the program using a C compiler.
   ```bash
   gcc student_registration.c -o student_registration
   ```
3. Run the compiled program:
   ```bash
   ./student_registration
   ```
4. Use the interactive menu to add, view, search, update, delete, or count students.

## Example

After running the program, the following options will be available in the menu:

```
1. Add Student
2. View All Students
3. Search Student
4. Update Student
5. Delete Student
6. Count Total Students
7. Exit
```

Select the corresponding number to perform the action.

## Code Overview

### `addStudent`

This function adds a new student record to the linked list. It collects all student details and creates a new node with that information.

### `viewAllStudents`

Displays the details of all registered students by traversing the linked list.

### `searchStudent`

Allows searching for a student by their ID. If the student exists, their details are displayed.

### `updateStudent`

This function enables updating an existing student's details by searching for their ID.

### `deleteStudent`

Deletes a student record from the linked list by searching for their ID and removing the corresponding node.

### `countStudents`

Counts and displays the total number of students in the linked list.

## Requirements

- A C compiler (e.g., GCC)
- Basic knowledge of C programming and linked lists

## License

This project is open-source and available under the MIT License.

## Author

This system was developed by Syed Tasavour as part of an academic project.
