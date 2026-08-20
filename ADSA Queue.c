#include <stdio.h>
#include <stdlib.h>

struct PrintJob {
    int jobID;
    char jobName[50];
    struct PrintJob *next;
};

struct PrintJob *front = NULL;
struct PrintJob *rear = NULL;

// Display current pending print jobs
void display() {
    struct PrintJob *temp = front;

    if (front == NULL) {
        printf("\nNo pending print jobs.\n");
        return;
    }

    printf("\nPending Print Jobs:\n");
    printf("-----------------------------\n");

    while (temp != NULL) {
        printf("Job ID: %d | Job Name: %s\n",
               temp->jobID, temp->jobName);
        temp = temp->next;
    }
}

// Add a print job to the queue
void enqueue() {
    struct PrintJob *newNode;

    newNode = (struct PrintJob *)malloc(sizeof(struct PrintJob));

    printf("Enter Job ID: ");
    scanf("%d", &newNode->jobID);

    printf("Enter Job Name: ");
    scanf("%s", newNode->jobName);

    newNode->next = NULL;

    // If queue is empty
    if (rear == NULL) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\nPrint job submitted successfully.\n");

    // Display after operation
    display();
}

// Process/remove the first print job
void dequeue() {
    struct PrintJob *temp;

    if (front == NULL) {
        printf("\nNo print jobs to process.\n");
        return;
    }

    temp = front;

    printf("\nProcessing Print Job:\n");
    printf("Job ID: %d | Job Name: %s\n",
           temp->jobID, temp->jobName);

    front = front->next;

    // If queue becomes empty
    if (front == NULL) {
        rear = NULL;
    }

    free(temp);

    // Display after operation
    display();
}

int main() {
    int choice;

    while (1) {

        printf("\n===== Print Job Management System =====\n");
        printf("1. Submit Print Job\n");
        printf("2. Process Print Job\n");
        printf("3. Display Pending Jobs\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("\nProgram terminated.\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}