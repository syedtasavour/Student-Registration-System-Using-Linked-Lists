#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_CLASS_LENGTH 20
#define MAX_DEPARTMENT_LENGTH 50
#define MAX_CONTACT_LENGTH 50

typedef struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char class[MAX_CLASS_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH];
    char contact[MAX_CONTACT_LENGTH];
    struct Student* next;
} Student;

// Function prototypes
Student* addStudent(Student* head, int id, const char* name, int age, const char* class, const char* department, const char* contact);
void viewAllStudents(Student* head);
Student* searchStudent(Student* head, int id);
void updateStudent(Student* head, int id);
Student* deleteStudent(Student* head, int id);
int countStudents(Student* head);
bool isValidEmail(const char* email);
bool isValidPhone(const char* phone);
void clearInputBuffer();
bool isValidName(const char* name);
bool isValidAge(int age);
bool isValidClass(const char* class);
bool isValidDepartment(const char* department);

int main() {
    Student* head = NULL;
    int choice, id, age;
    char name[MAX_NAME_LENGTH], class[MAX_CLASS_LENGTH], department[MAX_DEPARTMENT_LENGTH], contact[MAX_CONTACT_LENGTH];

    while (1) {
        printf("\nStudent Registration System\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Count Total Students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid ID. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }

                printf("Enter Name: ");
                clearInputBuffer();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                if (!isValidName(name)) {
                    printf("Invalid name. Please use only letters, spaces, and hyphens.\n");
                    break;
                }

                printf("Enter Age: ");
                if (scanf("%d", &age) != 1 || !isValidAge(age)) {
                    printf("Invalid age. Please enter a number between 15 and 100.\n");
                    clearInputBuffer();
                    break;
                }

                printf("Enter Class: ");
                clearInputBuffer();
                fgets(class, sizeof(class), stdin);
                class[strcspn(class, "\n")] = 0;
                if (!isValidClass(class)) {
                    printf("Invalid class. Please use only letters, numbers, and spaces.\n");
                    break;
                }

                printf("Enter Department: ");
                fgets(department, sizeof(department), stdin);
                department[strcspn(department, "\n")] = 0;
                if (!isValidDepartment(department)) {
                    printf("Invalid department. Please use only letters, spaces, and hyphens.\n");
                    break;
                }

                printf("Enter Contact (email or phone): ");
                fgets(contact, sizeof(contact), stdin);
                contact[strcspn(contact, "\n")] = 0;
                
                if (isValidEmail(contact) || isValidPhone(contact)) {
                    head = addStudent(head, id, name, age, class, department, contact);
                } else {
                    printf("Invalid contact information. Please enter a valid email or phone number.\n");
                }
                break;
            case 2:
                viewAllStudents(head);
                break;
            case 3:
                printf("Enter Student ID to search: ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid ID. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }
                Student* found = searchStudent(head, id);
                if (found) {
                    printf("Student found:\n");
                    printf("ID: %d, Name: %s, Age: %d, Class: %s, Department: %s, Contact: %s\n",
                           found->id, found->name, found->age, found->class, found->department, found->contact);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 4:
                printf("Enter Student ID to update: ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid ID. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }
                updateStudent(head, id);
                break;
            case 5:
                printf("Enter Student ID to delete: ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid ID. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }
                head = deleteStudent(head, id);
                break;
            case 6:
                printf("Total number of students: %d\n", countStudents(head));
                break;
            case 7:
                // Free allocated memory before exiting
                while (head != NULL) {
                    Student* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

Student* addStudent(Student* head, int id, const char* name, int age, const char* class, const char* department, const char* contact) {
    if (searchStudent(head, id) != NULL) {
        printf("A student with ID %d already exists. Cannot add duplicate.\n", id);
        return head;
    }

    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed. Cannot add student.\n");
        return head;
    }

    newStudent->id = id;
    strncpy(newStudent->name, name, MAX_NAME_LENGTH - 1);
    newStudent->name[MAX_NAME_LENGTH - 1] = '\0';
    newStudent->age = age;
    strncpy(newStudent->class, class, MAX_CLASS_LENGTH - 1);
    newStudent->class[MAX_CLASS_LENGTH - 1] = '\0';
    strncpy(newStudent->department, department, MAX_DEPARTMENT_LENGTH - 1);
    newStudent->department[MAX_DEPARTMENT_LENGTH - 1] = '\0';
    strncpy(newStudent->contact, contact, MAX_CONTACT_LENGTH - 1);
    newStudent->contact[MAX_CONTACT_LENGTH - 1] = '\0';
    newStudent->next = head;
    printf("Student added successfully.\n");
    return newStudent;
}

void viewAllStudents(Student* head) {
    if (head == NULL) {
        printf("No students in the system.\n");
        return;
    }

    printf("All Students:\n");
    while (head != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Class: %s, Department: %s, Contact: %s\n",
               head->id, head->name, head->age, head->class, head->department, head->contact);
        head = head->next;
    }
}

Student* searchStudent(Student* head, int id) {
    while (head != NULL) {
        if (head->id == id) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void updateStudent(Student* head, int id) {
    Student* student = searchStudent(head, id);
    if (student == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("Updating student with ID %d\n", id);
    char input[MAX_NAME_LENGTH];

    printf("Enter new Name (or press enter to keep current): ");
    clearInputBuffer();
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (input[0] != '\0') {
            if (isValidName(input)) {
                strncpy(student->name, input, MAX_NAME_LENGTH - 1);
                student->name[MAX_NAME_LENGTH - 1] = '\0';
            } else {
                printf("Invalid name. Name not updated.\n");
            }
        }
    }

    printf("Enter new Age (or press enter to keep current): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (input[0] != '\0') {
            int newAge = atoi(input);
            if (isValidAge(newAge)) {
                student->age = newAge;
            } else {
                printf("Invalid age. Age not updated.\n");
            }
        }
    }

    printf("Enter new Class (or press enter to keep current): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (input[0] != '\0') {
            if (isValidClass(input)) {
                strncpy(student->class, input, MAX_CLASS_LENGTH - 1);
                student->class[MAX_CLASS_LENGTH - 1] = '\0';
            } else {
                printf("Invalid class. Class not updated.\n");
            }
        }
    }

    printf("Enter new Department (or press enter to keep current): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (input[0] != '\0') {
            if (isValidDepartment(input)) {
                strncpy(student->department, input, MAX_DEPARTMENT_LENGTH - 1);
                student->department[MAX_DEPARTMENT_LENGTH - 1] = '\0';
            } else {
                printf("Invalid department. Department not updated.\n");
            }
        }
    }

    printf("Enter new Contact (or press enter to keep current): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (input[0] != '\0') {
            if (isValidEmail(input) || isValidPhone(input)) {
                strncpy(student->contact, input, MAX_CONTACT_LENGTH - 1);
                student->contact[MAX_CONTACT_LENGTH - 1] = '\0';
            } else {
                printf("Invalid contact information. Contact not updated.\n");
            }
        }
    }

    printf("Student information updated successfully.\n");
}

Student* deleteStudent(Student* head, int id) {
    Student* current = head;
    Student* prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with ID %d not found.\n", id);
        return head;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Student with ID %d deleted successfully.\n", id);
    return head;
}

int countStudents(Student* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

bool isValidEmail(const char* email) {
    const char* atSign = strchr(email, '@');
    return atSign != NULL && strchr(atSign, '.') != NULL;
}

bool isValidPhone(const char* phone) {
    int len = strlen(phone);
    if (len != 10) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool isValidName(const char* name) {
    int len = strlen(name);
    if (len == 0 || len > MAX_NAME_LENGTH - 1) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-') return false;
    }
    return true;
}

bool isValidAge(int age) {
    return age >= 15 && age <= 100;
}

bool isValidClass(const char* class) {
    int len = strlen(class);
    if (len == 0 || len > MAX_CLASS_LENGTH - 1) return false;
    for (int i = 0; i < len; i++) {
        if (!isalnum(class[i]) && class[i] != ' ') return false;
    }
    return true;
}

bool isValidDepartment(const char* department) {
    int len = strlen(department);
    if (len == 0 || len > MAX_DEPARTMENT_LENGTH - 1) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha(department[i]) && department[i] != ' ' && department[i] != '-') return false;
    }
    return true;
}
