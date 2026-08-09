#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    char department[50];
    struct Student *next;
};

struct Student *head = NULL;

// Add a new student at a specified position
void insertAtPosition(int position) {
    struct Student *newNode, *temp;
    int i;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    printf("Enter Roll Number: ");
    scanf("%d", &newNode->rollNo);

    printf("Enter Name: ");
    scanf("%s", newNode->name);

    printf("Enter Department: ");
    scanf("%s", newNode->department);

    newNode->next = NULL;

    // Insert at beginning
    if (position == 1) {
        newNode->next = head;
        head = newNode;
        return;
    }

    temp = head;

    // Move to the node before the required position
    for (i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    printf("Student record added successfully.\n");
}

// Delete student by roll number
void deleteByRollNo(int rollNo) {
    struct Student *temp = head;
    struct Student *prev = NULL;

    // If list is empty
    if (head == NULL) {
        printf("Student list is empty.\n");
        return;
    }

    // If first node contains the roll number
    if (head->rollNo == rollNo) {
        head = head->next;
        free(temp);
        printf("Student record deleted successfully.\n");
        return;
    }

    // Search for the roll number
    while (temp != NULL && temp->rollNo != rollNo) {
        prev = temp;
        temp = temp->next;
    }

    // Roll number not found
    if (temp == NULL) {
        printf("Student with Roll Number %d not found.\n", rollNo);
        return;
    }

    // Delete the node
    prev->next = temp->next;
    free(temp);

    printf("Student record deleted successfully.\n");
}

// Display all student records
void display() {
    struct Student *temp = head;

    if (head == NULL) {
        printf("Student list is empty.\n");
        return;
    }

    printf("\nStudent Records\n");
    printf("---------------------------------------------\n");
    printf("Roll No\tName\tDepartment\n");
    printf("---------------------------------------------\n");

    while (temp != NULL) {
        printf("%d\t%s\t%s\n",
               temp->rollNo,
               temp->name,
               temp->department);

        temp = temp->next;
    }
}

int main() {
    int choice, position, rollNo;

    while (1) {
        printf("\n===== Student Record Management =====\n");
        printf("1. Add Student\n");
        printf("2. Delete Student by Roll Number\n");
        printf("3. Display Students\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(position);
                break;

            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNo);
                deleteByRollNo(rollNo);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}