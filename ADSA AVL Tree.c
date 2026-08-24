#include <stdio.h>
#include <stdlib.h>

struct Node {
    int patientID;
    int height;
    struct Node *left;
    struct Node *right;
};

// Get height of a node
int height(struct Node *node) {
    if (node == NULL)
        return 0;

    return node->height;
}

// Find maximum of two values
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* createNode(int patientID) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->patientID = patientID;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Get balance factor
int getBalance(struct Node *node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

// Right Rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left Rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert patient ID
struct Node* insert(struct Node *node, int patientID) {

    // Normal BST insertion
    if (node == NULL)
        return createNode(patientID);

    if (patientID < node->patientID)
        node->left = insert(node->left, patientID);

    else if (patientID > node->patientID)
        node->right = insert(node->right, patientID);

    else {
        printf("Patient ID already exists.\n");
        return node;
    }

    // Update height
    node->height = 1 + max(height(node->left),
                            height(node->right));

    // Find balance factor
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && patientID < node->left->patientID)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && patientID > node->right->patientID)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && patientID > node->left->patientID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && patientID < node->right->patientID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Inorder traversal
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->patientID);
        inorder(root->right);
    }
}

// Preorder traversal to show tree structure
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->patientID);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {

    struct Node *root = NULL;
    int n, patientID, i;

    printf("Enter number of patient IDs: ");
    scanf("%d", &n);

    printf("\nEnter patient IDs:\n");

    for (i = 0; i < n; i++) {

        printf("Patient ID %d: ", i + 1);
        scanf("%d", &patientID);

        root = insert(root, patientID);

        printf("After insertion: ");
        preorder(root);
        printf("\n");
    }

    printf("\nPatient IDs in sorted order: ");
    inorder(root);

    printf("\n");

    return 0;
}