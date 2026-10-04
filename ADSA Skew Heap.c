#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int patientID;
    int priority;
    struct Node *left;
    struct Node *right;
};

/* Create a new patient node */
struct Node* createNode(int patientID, int priority)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->patientID = patientID;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Merge two Skew Heaps */
struct Node* merge(struct Node *h1, struct Node *h2)
{
    struct Node *temp;

    if(h1 == NULL)
        return h2;

    if(h2 == NULL)
        return h1;

    /* Smaller priority gets higher priority */
    if(h2->priority < h1->priority)
    {
        temp = h1;
        h1 = h2;
        h2 = temp;
    }

    /* Merge with right subtree */
    h1->right = merge(h1->right, h2);

    /* Swap left and right children */
    temp = h1->left;
    h1->left = h1->right;
    h1->right = temp;

    return h1;
}

/* Insert a patient */
struct Node* insert(struct Node *root, int patientID, int priority)
{
    struct Node *newNode;

    newNode = createNode(patientID, priority);

    return merge(root, newNode);
}

/* Delete highest priority patient */
struct Node* deleteMin(struct Node *root)
{
    struct Node *leftHeap;
    struct Node *rightHeap;
    struct Node *temp;

    if(root == NULL)
    {
        printf("No patients in the emergency queue.\n");
        return NULL;
    }

    printf("\nTreating Patient ID: %d\n", root->patientID);
    printf("Priority: %d\n", root->priority);

    leftHeap = root->left;
    rightHeap = root->right;

    free(root);

    /* Merge remaining two heaps */
    temp = merge(leftHeap, rightHeap);

    return temp;
}

/* Display the heap */
void display(struct Node *root)
{
    if(root == NULL)
        return;

    printf("Patient ID: %d | Priority: %d\n",
           root->patientID, root->priority);

    display(root->left);
    display(root->right);
}

/* Main function */
int main()
{
    struct Node *root = NULL;

    int choice;
    int patientID;
    int priority;

    while(1)
    {
        printf("\n===== HOSPITAL EMERGENCY PRIORITY QUEUE =====\n");
        printf("1. Add Patient\n");
        printf("2. Treat Highest Priority Patient\n");
        printf("3. Display Patients\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%d", &patientID);

                printf("Enter Priority Number: ");
                scanf("%d", &priority);

                root = insert(root, patientID, priority);

                printf("Patient added successfully.\n");
                break;

            case 2:
                root = deleteMin(root);
                break;

            case 3:
                if(root == NULL)
                    printf("Emergency queue is empty.\n");
                else
                {
                    printf("\nPatients in Skew Heap:\n");
                    printf("-----------------------------\n");
                    display(root);
                }
                break;

            case 4:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}