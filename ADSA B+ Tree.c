#include <stdio.h>
#include <stdlib.h>

#define ORDER 3

struct Node
{
    int keys[ORDER];
    struct Node *child[ORDER + 1];

    int n;
    int leaf;

    struct Node *next;
};

struct Node *root = NULL;

/* Create a new node */
struct Node* createNode(int leaf)
{
    struct Node *newNode;
    int i;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->n = 0;
    newNode->leaf = leaf;
    newNode->next = NULL;

    for(i = 0; i <= ORDER; i++)
        newNode->child[i] = NULL;

    return newNode;
}

/* Search for an article ID */
int search(struct Node *node, int key)
{
    int i = 0;

    if(node == NULL)
        return 0;

    while(i < node->n && key >= node->keys[i])
        i++;

    if(node->leaf)
    {
        for(i = 0; i < node->n; i++)
        {
            if(node->keys[i] == key)
                return 1;
        }

        return 0;
    }

    return search(node->child[i], key);
}

/* Insert key into a leaf */
void insertIntoLeaf(struct Node *leaf, int key)
{
    int i;

    i = leaf->n - 1;

    while(i >= 0 && leaf->keys[i] > key)
    {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }

    leaf->keys[i + 1] = key;
    leaf->n++;
}

/* Simple insertion */
void insert(int key)
{
    struct Node *newNode;
    int i;

    /* Empty tree */
    if(root == NULL)
    {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    /* For this practical implementation, root is a leaf
       until it becomes full */
    if(root->leaf)
    {
        if(root->n < ORDER)
        {
            insertIntoLeaf(root, key);
        }
        else
        {
            /* Split root leaf */
            struct Node *oldRoot = root;
            struct Node *newLeaf = createNode(1);
            struct Node *newRoot = createNode(0);

            insertIntoLeaf(oldRoot, key);

            newLeaf->keys[0] = oldRoot->keys[2];
            newLeaf->n = 1;

            oldRoot->n = 2;

            oldRoot->next = newLeaf;

            newRoot->keys[0] = newLeaf->keys[0];
            newRoot->n = 1;

            newRoot->child[0] = oldRoot;
            newRoot->child[1] = newLeaf;

            root = newRoot;
        }

        return;
    }

    /* Root is internal */
    {
        struct Node *leaf = root;
        int pos = 0;

        while(!leaf->leaf)
        {
            pos = 0;

            while(pos < leaf->n && key >= leaf->keys[pos])
                pos++;

            leaf = leaf->child[pos];
        }

        if(leaf->n < ORDER)
        {
            insertIntoLeaf(leaf, key);
        }
        else
        {
            struct Node *newLeaf = createNode(1);

            insertIntoLeaf(leaf, key);

            newLeaf->keys[0] = leaf->keys[2];
            newLeaf->n = 1;

            leaf->n = 2;

            newLeaf->next = leaf->next;
            leaf->next = newLeaf;

            /*
             * For demonstration, add the new leaf's
             * first key to the root.
             */
            if(root->n < ORDER)
            {
                for(i = root->n; i > pos; i--)
                {
                    root->keys[i] = root->keys[i - 1];
                    root->child[i + 1] = root->child[i];
                }

                root->keys[pos] = newLeaf->keys[0];
                root->child[pos + 1] = newLeaf;
                root->n++;
            }
        }
    }
}

/* Display all article IDs in sorted order */
void display()
{
    struct Node *temp;

    if(root == NULL)
    {
        printf("B+ Tree is empty.\n");
        return;
    }

    temp = root;

    /* Move to leftmost leaf */
    while(!temp->leaf)
        temp = temp->child[0];

    printf("\nArticle IDs in sorted order:\n");

    while(temp != NULL)
    {
        for(int i = 0; i < temp->n; i++)
            printf("%d ", temp->keys[i]);

        temp = temp->next;
    }

    printf("\n");
}

/* Delete an article ID */
void deleteKey(int key)
{
    struct Node *temp;

    if(root == NULL)
    {
        printf("B+ Tree is empty.\n");
        return;
    }

    temp = root;

    /* Find leaf */
    while(!temp->leaf)
    {
        int i = 0;

        while(i < temp->n && key >= temp->keys[i])
            i++;

        temp = temp->child[i];
    }

    /* Search inside leaf */
    for(int i = 0; i < temp->n; i++)
    {
        if(temp->keys[i] == key)
        {
            for(int j = i; j < temp->n - 1; j++)
                temp->keys[j] = temp->keys[j + 1];

            temp->n--;

            printf("Article ID %d deleted successfully.\n", key);
            return;
        }
    }

    printf("Article ID %d not found.\n", key);
}

/* Main */
int main()
{
    int choice, key;

    while(1)
    {
        printf("\n===== B+ TREE DIGITAL LIBRARY =====\n");
        printf("1. Insert Article ID\n");
        printf("2. Search Article ID\n");
        printf("3. Delete Article ID\n");
        printf("4. Display Article IDs\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Article ID: ");
                scanf("%d", &key);

                if(search(root, key))
                    printf("Article ID already exists.\n");
                else
                {
                    insert(key);
                    printf("Article ID inserted successfully.\n");
                }
                break;

            case 2:
                printf("Enter Article ID to search: ");
                scanf("%d", &key);

                if(search(root, key))
                    printf("Article ID %d found.\n", key);
                else
                    printf("Article ID %d not found.\n", key);
                break;

            case 3:
                printf("Enter Article ID to delete: ");
                scanf("%d", &key);

                deleteKey(key);
                break;

            case 4:
                display();
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