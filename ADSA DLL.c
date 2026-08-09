#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Photo {
    int photoID;
    char photoName[50];
    struct Photo *prev;
    struct Photo *next;
};

struct Photo *head = NULL;

// Insert photo at a specified position
void insertPhoto(int position) {
    struct Photo *newNode, *temp;
    int i;

    newNode = (struct Photo *)malloc(sizeof(struct Photo));

    printf("Enter Photo ID: ");
    scanf("%d", &newNode->photoID);

    printf("Enter Photo Name: ");
    scanf("%s", newNode->photoName);

    newNode->prev = NULL;
    newNode->next = NULL;

    // Insert at beginning
    if (position == 1) {
        newNode->next = head;

        if (head != NULL)
            head->prev = newNode;

        head = newNode;

        printf("Photo inserted successfully.\n");
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
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;

    printf("Photo inserted successfully.\n");
}

// Delete photo by Photo ID
void deletePhoto(int photoID) {
    struct Photo *temp = head;

    if (head == NULL) {
        printf("Photo list is empty.\n");
        return;
    }

    // Search for photo
    while (temp != NULL && temp->photoID != photoID) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Photo not found.\n");
        return;
    }

    // If deleting first node
    if (temp == head) {
        head = temp->next;

        if (head != NULL)
            head->prev = NULL;
    }
    else {
        temp->prev->next = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;
    }

    free(temp);

    printf("Photo deleted successfully.\n");
}

// Display photos in forward direction
void displayForward() {
    struct Photo *temp = head;

    if (head == NULL) {
        printf("Photo list is empty.\n");
        return;
    }

    printf("\nPhotos - Forward Direction\n");
    printf("--------------------------------\n");

    while (temp != NULL) {
        printf("Photo ID: %d | Name: %s\n",
               temp->photoID,
               temp->photoName);

        temp = temp->next;
    }
}

// Display photos in backward direction
void displayBackward() {
    struct Photo *temp = head;

    if (head == NULL) {
        printf("Photo list is empty.\n");
        return;
    }

    // Move to the last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("\nPhotos - Backward Direction\n");
    printf("--------------------------------\n");

    while (temp != NULL) {
        printf("Photo ID: %d | Name: %s\n",
               temp->photoID,
               temp->photoName);

        temp = temp->prev;
    }
}

int main() {
    int choice, position, photoID;

    while (1) {

        printf("\n===== Photo Management System =====\n");
        printf("1. Insert Photo\n");
        printf("2. Delete Photo\n");
        printf("3. Display Forward\n");
        printf("4. Display Backward\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter position: ");
                scanf("%d", &position);
                insertPhoto(position);
                break;

            case 2:
                printf("Enter Photo ID to delete: ");
                scanf("%d", &photoID);
                deletePhoto(photoID);
                break;

            case 3:
                displayForward();
                break;

            case 4:
                displayBackward();
                break;

            case 5:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}