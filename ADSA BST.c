#include <stdio.h>
#include <stdlib.h>

struct Node {
    int rollNo;
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(int rollNo) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->rollNo = rollNo;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a roll number into BST
struct Node* insert(struct Node *root, int rollNo) {

    if (root == NULL) {
        return createNode(rollNo);
    }

    if (rollNo < root->rollNo) {
        root->left = insert(root->left, rollNo);
    }
    else if (rollNo > root->rollNo) {
        root->right = insert(root->right, rollNo);
    }
    else {
        printf("Roll Number already exists.\n");
    }

    return root;
}

// Search for a roll number
struct Node* search(struct Node *root, int rollNo) {

    if (root == NULL || root->rollNo == rollNo) {
        return root;
    }

    if (rollNo < root->rollNo) {
        return search(root->left, rollNo);
    }

    return search(root->right, rollNo);
}

// Find the minimum value node
struct Node* findMin(struct Node *root) {

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

// Delete a roll number
struct Node* deleteNode(struct Node *root, int rollNo) {

    if (root == NULL) {
        printf("Roll Number not found.\n");
        return root;
    }

    if (rollNo < root->rollNo) {
        root->left = deleteNode(root->left, rollNo);
    }
    else if (rollNo > root->rollNo) {
        root->right = deleteNode(root->right, rollNo);
    }
    else {

        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: Only right child
        else if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        // Case 3: Only left child
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 4: Two children
        else {
            struct Node *temp = findMin(root->right);

            root->rollNo = temp->rollNo;

            root->right = deleteNode(root->right, temp->rollNo);
        }
    }

    return root;
}

// Inorder traversal - displays sorted roll numbers
void inorder(struct Node *root) {

    if (root != NULL) {
        inorder(root->left);

        printf("%d ", root->rollNo);

        inorder(root->right);
    }
}

int main() {

    struct Node *root = NULL;
    struct Node *result;

    int choice;
    int rollNo;

    while (1) {

        printf("\n===== Student Roll Number Management =====\n");
        printf("1. Insert Roll Number\n");
        printf("2. Search Roll Number\n");
        printf("3. Delete Roll Number\n");
        printf("4. Display Sorted Roll Numbers\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &rollNo);

                root = insert(root, rollNo);

                printf("Roll Number inserted successfully.\n");
                break;

            case 2:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNo);

                result = search(root, rollNo);

                if (result != NULL)
                    printf("Roll Number %d found.\n", rollNo);
                else
                    printf("Roll Number %d not found.\n", rollNo);

                break;

            case 3:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNo);

                root = deleteNode(root, rollNo);

                break;

            case 4:
                if (root == NULL) {
                    printf("No roll numbers available.\n");
                }
                else {
                    printf("Roll Numbers in Sorted Order:\n");
                    inorder(root);
                    printf("\n");
                }

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