#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

struct node *create()
{
    struct node *temp;
    int data, ch;
    temp = (struct node *)malloc(sizeof(struct node));

    printf("Press 0 to exit\n");
    printf("Press 1 to create a new node\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    if (ch == 0)
    {
        return NULL;
    }
    else if (ch == 1)
    {

        printf("Enter the data: ");
        scanf("%d", &data);
        temp->data = data;

        printf("\nEnter left child of the tree\n");
        temp->left = create();

        printf("\nEnter right child of the tree: ");
        temp->right = create();
    }
    else
    {
        printf("\nInvalid choice!\n");
        free(temp);
        return NULL;
    }

    return temp;
}

struct QNode
{
    struct node *key;
    struct QNode *next;
};

struct Queue
{
    struct QNode *front, *rear;
};

struct QNode *newNode(struct node *k)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}

struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue *q, struct node *k)
{
    struct QNode *temp = newNode(k);

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

struct node *deQueue(struct Queue *q)
{
    if (q->front == NULL)
        return NULL;

    struct QNode *temp = q->front;
    struct node *node = temp->key;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return node;
}

void levelOrderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    struct Queue *q = createQueue();
    enQueue(q, root);

    while (q->front != NULL)
    {
        struct node *node = deQueue(q);
        printf("%d ", node->data);

        if (node->left != NULL)
            enQueue(q, node->left);

        if (node->right != NULL)
            enQueue(q, node->right);
    }
}

int main()
{
    struct node *root = NULL;
    int choice;

    do
    {
        printf("\n----- Menu -----\n");
        printf("1. Create Binary Tree\n");
        printf("2. Perform Level Order Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            root = create();
            break;
        case 2:
            printf("Level Order Traversal: ");
            levelOrderTraversal(root);
            printf("\n");
            break;
        case 3:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}
