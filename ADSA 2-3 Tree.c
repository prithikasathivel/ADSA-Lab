#include <stdio.h>
#include <stdlib.h>

#define MAX 2

struct Node {
    int key[MAX];
    struct Node *child[MAX + 1];
    int n;
    int leaf;
};

struct Node *root = NULL;

/* Create a new node */
struct Node* createNode(int key, int leaf)
{
    struct Node *newNode;
    int i;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key[0] = key;
    newNode->n = 1;
    newNode->leaf = leaf;

    for(i = 0; i < 3; i++)
        newNode->child[i] = NULL;

    return newNode;
}

/* Search */
int search(struct Node *node, int key)
{
    int i = 0;

    if(node == NULL)
        return 0;

    while(i < node->n && key > node->key[i])
        i++;

    if(i < node->n && key == node->key[i])
        return 1;

    if(node->leaf)
        return 0;

    return search(node->child[i], key);
}

/* Split a full child */
void splitChild(struct Node *parent, int pos)
{
    struct Node *fullChild = parent->child[pos];
    struct Node *newChild;
    int middleKey;
    int i;

    middleKey = fullChild->key[1];

    newChild = createNode(middleKey, fullChild->leaf);

    newChild->key[0] = fullChild->key[1];
    newChild->n = 1;

    if(!fullChild->leaf)
    {
        newChild->child[0] = fullChild->child[2];
        newChild->child[1] = fullChild->child[3];
    }

    fullChild->n = 1;

    for(i = parent->n; i >= pos + 1; i--)
        parent->child[i + 1] = parent->child[i];

    parent->child[pos + 1] = newChild;

    for(i = parent->n - 1; i >= pos; i--)
        parent->key[i + 1] = parent->key[i];

    parent->key[pos] = middleKey;
    parent->n++;
}

/* Insert into a non-full node */
void insertNonFull(struct Node *node, int key)
{
    int i;

    i = node->n - 1;

    if(node->leaf)
    {
        while(i >= 0 && key < node->key[i])
        {
            node->key[i + 1] = node->key[i];
            i--;
        }

        node->key[i + 1] = key;
        node->n++;
    }
    else
    {
        while(i >= 0 && key < node->key[i])
            i--;

        i++;

        if(node->child[i]->n == MAX)
        {
            splitChild(node, i);

            if(key > node->key[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}

/* Insert */
void insert(int key)
{
    struct Node *newRoot;

    if(search(root, key))
    {
        printf("Roll Number already exists.\n");
        return;
    }

    if(root == NULL)
    {
        root = createNode(key, 1);
        return;
    }

    if(root->n == MAX)
    {
        newRoot = createNode(0, 0);

        newRoot->n = 0;
        newRoot->child[0] = root;

        root = newRoot;

        splitChild(root, 0);

        insertNonFull(root, key);
    }
    else
    {
        insertNonFull(root, key);
    }
}

/* Inorder traversal */
void inorder(struct Node *node)
{
    if(node == NULL)
        return;

    if(node->leaf)
    {
        if(node->n == 1)
            printf("%d ", node->key[0]);
        else
            printf("%d %d ", node->key[0], node->key[1]);
    }
    else
    {
        inorder(node->child[0]);
        printf("%d ", node->key[0]);

        inorder(node->child[1]);

        if(node->n == 2)
        {
            printf("%d ", node->key[1]);
            inorder(node->child[2]);
        }
    }
}

/* Simple deletion from leaf */
int deleteKey(struct Node *node, int key)
{
    int i, j;

    if(node == NULL)
        return 0;

    i = 0;

    while(i < node->n && key > node->key[i])
        i++;

    if(node->leaf)
    {
        if(i < node->n && node->key[i] == key)
        {
            for(j = i; j < node->n - 1; j++)
                node->key[j] = node->key[j + 1];

            node->n--;
            return 1;
        }

        return 0;
    }

    return deleteKey(node->child[i], key);
}

/* Delete */
void deleteNode(int key)
{
    if(root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    if(deleteKey(root, key))
        printf("Roll Number deleted successfully.\n");
    else
        printf("Roll Number not found.\n");
}

/* Main */
int main()
{
    int choice, rollNo;

    while(1)
    {
        printf("\n===== 2-3 TREE =====\n");
        printf("1. Insert Roll Number\n");
        printf("2. Search Roll Number\n");
        printf("3. Delete Roll Number\n");
        printf("4. Display Sorted Roll Numbers\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &rollNo);

                insert(rollNo);
                printf("Roll Number inserted successfully.\n");
                break;

            case 2:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNo);

                if(search(root, rollNo))
                    printf("Roll Number %d found.\n", rollNo);
                else
                    printf("Roll Number %d not found.\n", rollNo);

                break;

            case 3:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNo);

                deleteNode(rollNo);
                break;

            case 4:
                if(root == NULL)
                    printf("Tree is empty.\n");
                else
                {
                    printf("Roll Numbers in sorted order:\n");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 5:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}