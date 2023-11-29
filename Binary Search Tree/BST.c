#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct node
{
    int data;
    struct node *left;
    struct node *right;
    int flag;
};

// Define the stack structure
struct stack
{
    int size;
    int top;
    struct node *arr[30];
};

// Function to get the top element of the stack
struct node *stackTop(struct stack *sp)
{
    return sp->arr[sp->top];
}

// Function to check if the stack is empty
int isEmpty(struct stack *ptr)
{
    return ptr->top == -1;
}

// Function to check if the stack is full
int isFull(struct stack *ptr)
{
    return ptr->top == ptr->size - 1;
}

// Function to push a node onto the stack
void push(struct stack *ptr, struct node *val)
{
    if (isFull(ptr))
    {
        printf("Stack Overflow, cannot push %d to the stack\n", val->data);
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

// Function to pop a node from the stack
struct node *pop(struct stack *ptr)
{
    if (isEmpty(ptr))
    {
        printf("Stack Underflow, cannot pop from the stack\n");
        return NULL;
    }
    else
    {
        struct node *val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

// Function to create a new node
struct node *createNode(int data)
{
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->flag = 0;
    return n;
}

// Function to perform preorder traversal
void preOrder(struct node *T)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->size = 30; // Set the size of the stack
    s->top = -1;

    while (1)
    {
        while (T != NULL)
        {
            printf("%d ", T->data);
            if (T->right != NULL)
            {
                push(s, T->right);
            }
            T = T->left;
        }

        if (!isEmpty(s))
        {
            T = pop(s);
        }
        else
        {
            break;
        }
    }
}
// Function to perform inorder traversal
void inOrder(struct node *T)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->size = 30;
    s->top = -1;

    while (1)
    {
        while (T != NULL)
        {
            push(s, T);
            T = T->left;
        }

        if (!isEmpty(s))
        {
            T = pop(s);
            printf("%d ", T->data);
            T = T->right;
        }
        else
        {
            break;
        }
    }
}

// Function to perform postorder traversal
void postOrder(struct node *T)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->size = 30;
    s->top = -1;

    while (1)
    {
        while (T != NULL)
        {
            push(s, T);
            T = T->left;
        }

        if (stackTop(s)->flag == 1)
        {
            if (!isEmpty(s))
            {
                T = pop(s);
                printf("%d ", T->data);
                T = NULL;
            }
            else
            {
                break;
            }
        }
        else
        {
            T = stackTop(s)->right;
            stackTop(s)->flag = 1;
        }
    }
}

// Function to insert a new node into the BST
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    else if (data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find the minimum value in the BST
int findMin(struct node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root->left != NULL)
    {
        root = root->left;
    }

    return root->data;
}

// Function to find the maximum value in the BST
int findMax(struct node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root->right != NULL)
    {
        root = root->right;
    }

    return root->data;
}
void MirrorWithoutRecursion(struct node *root)
{
    if (!root)
        return;

    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->size = 30;
    s->top = -1;

    push(s, root);
    while (!isEmpty(s))
    {
        struct node *current = pop(s);

        // Swap the children
        struct node *temp = current->right;
        current->right = current->left;
        current->left = temp;

        // Push the children on the stack
        if (current->right)
            push(s, current->right);

        if (current->left)
            push(s, current->left);
    }
}

// Main function
int main()
{
    struct node *root = NULL;
    int n, value;

    printf("Enter no. of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("The Preorder traversal is:\n");
    preOrder(root);
    printf("\n");

    MirrorWithoutRecursion(root);

    printf("\n");

    printf("The minimum value in the BST is: %d\n", findMin(root));
    printf("The maximum value in the BST is: %d\n", findMax(root));

    printf("\n");

    printf("The Preorder traversal is:\n");
    preOrder(root);
    printf("\n");

    printf("The Inorder traversal is:\n");
    inOrder(root);
    printf("\n");

    printf("The Postorder traversal is:\n");
    postOrder(root);
    printf("\n");

    return 0;
}
