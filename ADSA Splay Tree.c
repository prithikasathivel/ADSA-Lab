#include <stdio.h>
#include <stdlib.h>

struct Node {
    int contactID;
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(int contactID) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->contactID = contactID;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Right Rotation
struct Node* rightRotate(struct Node *x) {
    struct Node *y = x->left;

    x->left = y->right;
    y->right = x;

    return y;
}

// Left Rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;

    x->right = y->left;
    y->left = x;

    return y;
}

// Splay operation
struct Node* splay(struct Node *root, int contactID) {

    if (root == NULL || root->contactID == contactID)
        return root;

    // Contact is in left subtree
    if (contactID < root->contactID) {

        if (root->left == NULL)
            return root;

        // Zig-Zig case
        if (contactID < root->left->contactID) {
            root->left->left =
                splay(root->left->left, contactID);

            root = rightRotate(root);
        }

        // Zig-Zag case
        else if (contactID > root->left->contactID) {
            root->left->right =
                splay(root->left->right, contactID);

            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Final rotation
        if (root->left == NULL)
            return root;
        else
            return rightRotate(root);
    }

    // Contact is in right subtree
    else {

        if (root->right == NULL)
            return root;

        // Zag-Zag case
        if (contactID > root->right->contactID) {
            root->right->right =
                splay(root->right->right, contactID);

            root = leftRotate(root);
        }

        // Zag-Zig case
        else if (contactID < root->right->contactID) {
            root->right->left =
                splay(root->right->left, contactID);

            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }

        // Final rotation
        if (root->right == NULL)
            return root;
        else
            return leftRotate(root);
    }
}

// Insert a contact
struct Node* insert(struct Node *root, int contactID) {

    if (root == NULL)
        return createNode(contactID);

    // Splay the tree using the contact ID
    root = splay(root, contactID);

    // If contact already exists
    if (root->contactID == contactID) {
        printf("Contact ID already exists.\n");
        return root;
    }

    struct Node *newNode = createNode(contactID);

    if (contactID < root->contactID) {

        newNode->right = root;
        newNode->left = root->left;

        root->left = NULL;
    }
    else {

        newNode->left = root;
        newNode->right = root->right;

        root->right = NULL;
    }

    return newNode;
}

// Search for a contact
struct Node* search(struct Node *root, int contactID) {

    if (root == NULL)
        return NULL;

    root = splay(root, contactID);

    if (root->contactID == contactID) {
        printf("Contact ID %d found.\n", contactID);
    }
    else {
        printf("Contact ID %d not found.\n", contactID);
    }

    return root;
}

// Display contacts using inorder traversal
void inorder(struct Node *root) {

    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->contactID);
        inorder(root->right);
    }
}

// Display tree structure using preorder
void preorder(struct Node *root) {

    if (root != NULL) {
        printf("%d ", root->contactID);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {

    struct Node *root = NULL;
    int choice;
    int contactID;

    while (1) {

        printf("\n===== Contact Management System =====\n");
        printf("1. Insert Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contacts\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter Contact ID: ");
                scanf("%d", &contactID);

                root = insert(root, contactID);

                printf("Tree after insertion (Preorder): ");
                preorder(root);
                printf("\n");

                break;

            case 2:
                printf("Enter Contact ID to search: ");
                scanf("%d", &contactID);

                root = search(root, contactID);

                printf("Tree after search (Preorder): ");
                preorder(root);
                printf("\n");

                break;

            case 3:
                printf("\nContacts in sorted order: ");
                inorder(root);
                printf("\n");

                printf("Current tree structure (Preorder): ");
                preorder(root);
                printf("\n");

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