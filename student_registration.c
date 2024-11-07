#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definitions
struct Student {
    int studentId;
    char name[50];
    int age;
    char class[20];
    char department[50];
    char contact[50];
    struct Student* next;
};

// Function declarations
struct Student* addStudent(struct Student* head);
void viewAllStudents(struct Student* head);
void searchStudent(struct Student* head);
void updateStudent(struct Student* head);
void deleteStudent(struct Student** head);
void countStudents(struct Student* head);
int isIdUnique(struct Student* head, int id);
void clearInputBuffer();

int main() {
    struct Student* head = NULL;
    int choice;

    do {
        printf("\n=== Student Registration System ===\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Count Total Students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                viewAllStudents(head);
                break;
            case 3:
                searchStudent(head);
                break;
            case 4:
                updateStudent(head);
                break;
            case 5:
                deleteStudent(&head);
                break;
            case 6:
                countStudents(head);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    // Free memory before exiting
    struct Student* current = head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

// Utility function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to add a new student
struct Student* addStudent(struct Student* head) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    printf("\nEnter Student Details:\n");
    printf("Student ID: ");
    scanf("%d", &newStudent->studentId);
    clearInputBuffer();

    if (!isIdUnique(head, newStudent->studentId)) {
        printf("Error: Student ID already exists!\n");
        free(newStudent);
        return head;
    }

    printf("Name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = 0;

    printf("Age: ");
    scanf("%d", &newStudent->age);
    clearInputBuffer();

    printf("Class: ");
    fgets(newStudent->class, sizeof(newStudent->class), stdin);
    newStudent->class[strcspn(newStudent->class, "\n")] = 0;

    printf("Department: ");
    fgets(newStudent->department, sizeof(newStudent->department), stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = 0;

    printf("Contact: ");
    fgets(newStudent->contact, sizeof(newStudent->contact), stdin);
    newStudent->contact[strcspn(newStudent->contact, "\n")] = 0;

    newStudent->next = head;
    printf("Student added successfully!\n");
    return newStudent;
}

// Function to check if student ID is unique
int isIdUnique(struct Student* head, int id) {
    struct Student* current = head;
    while (current != NULL) {
        if (current->studentId == id) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

// Function to view all students
void viewAllStudents(struct Student* head) {
    if (head == NULL) {
        printf("No students registered yet!\n");
        return;
    }

    printf("\n=== Student Records ===\n");
    struct Student* current = head;
    while (current != NULL) {
        printf("\nStudent ID: %d\n", current->studentId);
        printf("Name: %s\n", current->name);
        printf("Age: %d\n", current->age);
        printf("Class: %s\n", current->class);
        printf("Department: %s\n", current->department);
        printf("Contact: %s\n", current->contact);
        printf("------------------------\n");
        current = current->next;
    }
}

// Function to search for a student
void searchStudent(struct Student* head) {
    if (head == NULL) {
        printf("No students registered yet!\n");
        return;
    }

    int searchId;
    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);

    struct Student* current = head;
    while (current != NULL) {
        if (current->studentId == searchId) {
            printf("\nStudent found!\n");
            printf("Student ID: %d\n", current->studentId);
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Class: %s\n", current->class);
            printf("Department: %s\n", current->department);
            printf("Contact: %s\n", current->contact);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found!\n", searchId);
}

// Function to update student information
void updateStudent(struct Student* head) {
    if (head == NULL) {
        printf("No students registered yet!\n");
        return;
    }

    int updateId;
    printf("Enter Student ID to update: ");
    scanf("%d", &updateId);
    clearInputBuffer();

    struct Student* current = head;
    while (current != NULL) {
        if (current->studentId == updateId) {
            printf("\nEnter new details:\n");
            
            printf("Name: ");
            fgets(current->name, sizeof(current->name), stdin);
            current->name[strcspn(current->name, "\n")] = 0;

            printf("Age: ");
            scanf("%d", &current->age);
            clearInputBuffer();

            printf("Class: ");
            fgets(current->class, sizeof(current->class), stdin);
            current->class[strcspn(current->class, "\n")] = 0;

            printf("Department: ");
            fgets(current->department, sizeof(current->department), stdin);
            current->department[strcspn(current->department, "\n")] = 0;

            printf("Contact: ");
            fgets(current->contact, sizeof(current->contact), stdin);
            current->contact[strcspn(current->contact, "\n")] = 0;

            printf("Student information updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found!\n", updateId);
}

// Function to delete a student
void deleteStudent(struct Student** head) {
    if (*head == NULL) {
        printf("No students registered yet!\n");
        return;
    }

    int deleteId;
    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteId);

    struct Student* current = *head;
    struct Student* prev = NULL;

    // If head node itself holds the student to be deleted
    if (current != NULL && current->studentId == deleteId) {
        *head = current->next;
        free(current);
        printf("Student deleted successfully!\n");
        return;
    }

    // Search for the student to be deleted
    while (current != NULL && current->studentId != deleteId) {
        prev = current;
        current = current->next;
    }

    // If student was not present in the list
    if (current == NULL) {
        printf("Student with ID %d not found!\n", deleteId);
        return;
    }

    // Unlink the node from linked list
    prev->next = current->next;
    free(current);
    printf("Student deleted successfully!\n");
}

// Function to count total students
void countStudents(struct Student* head) {
    int count = 0;
    struct Student* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    printf("Total number of students: %d\n", count);
} 