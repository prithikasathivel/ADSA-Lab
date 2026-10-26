
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int productID;
    int priority;
    struct Node *left, *right;
};

struct Node *createNode(int id)
{
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->productID = id;
    newNode->priority = rand() % 100;
    newNode->left = newNode->right = NULL;

    printf("Product ID: %d, Priority: %d\n",
           id, newNode->priority);

    return newNode;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

struct Node *insert(struct Node *root, int id)
{
    if (root == NULL)
        return createNode(id);

    if (id < root->productID)
    {
        root->left = insert(root->left, id);

        if (root->left->priority < root->priority)
            root = rightRotate(root);
    }
    else if (id > root->productID)
    {
        root->right = insert(root->right, id);

        if (root->right->priority < root->priority)
            root = leftRotate(root);
    }
    else
    {
        printf("Duplicate Product ID!\n");
    }

    return root;
}

struct Node *search(struct Node *root, int id)
{
    if (root == NULL || root->productID == id)
        return root;

    if (id < root->productID)
        return search(root->left, id);

    return search(root->right, id);
}

struct Node *deleteNode(struct Node *root, int id)
{
    if (root == NULL)
        return NULL;

    if (id < root->productID)
        root->left = deleteNode(root->left, id);

    else if (id > root->productID)
        root->right = deleteNode(root->right, id);

    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            root = leftRotate(root);
            root->left = deleteNode(root->left, id);
        }
        else if (root->right == NULL)
        {
            root = rightRotate(root);
            root->right = deleteNode(root->right, id);
        }
        else if (root->left->priority < root->right->priority)
        {
            root = rightRotate(root);
            root->right = deleteNode(root->right, id);
        }
        else
        {
            root = leftRotate(root);
            root->left = deleteNode(root->left, id);
        }
    }

    return root;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("Product ID: %d, Priority: %d\n",
               root->productID, root->priority);
        inorder(root->right);
    }
}

int main()
{
    struct Node *root = NULL;
    struct Node *result;
    int choice, id;

    srand((unsigned int)time(NULL));

    do
    {
        printf("\n--- Treap Inventory Menu ---\n");
        printf("1. Insert Product\n");
        printf("2. Search Product\n");
        printf("3. Delete Product\n");
        printf("4. Display Products\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter Product ID: ");
                scanf("%d", &id);
                root = insert(root, id);
                break;

            case 2:
                printf("Enter Product ID to search: ");
                scanf("%d", &id);
                result = search(root, id);

                if (result != NULL)
                    printf("Product found! Priority = %d\n",
                           result->priority);
                else
                    printf("Product not found!\n");
                break;

            case 3:
                printf("Enter Product ID to delete: ");
                scanf("%d", &id);

                if (search(root, id) != NULL)
                {
                    root = deleteNode(root, id);
                    printf("Product deleted successfully.\n");
                }
                else
                    printf("Product not found!\n");
                break;

            case 4:
                printf("\nProducts in sorted order:\n");
                inorder(root);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
