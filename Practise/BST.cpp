#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *r, *l;
    int flag;
};

struct stack
{
    int size;
    int top;
    struct node *arr[30];
};
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        return Newnode(data);
    }
    else if (data <= root->data)
    {
        root->l = insert(root->l, data);
    }
    else
    {

        root->r = insert(root->r, data);
    }
    return root;
}
struct node *Newnode(int data)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->r = n->l = NULL;
    n->flag = 0;
    return n;
}

struct node *stackTop(struct stack *sp)
{
    return sp->arr[sp->top];
}
int isEmpty(struct stack *ptr)
{
    return ptr->top == -1;
}

void push(struct stack *ptr, struct node *val)
{

    ptr->top++;
    ptr->arr[ptr->top] = val;
}

struct node *pop(struct stack *ptr)
{

    struct node *val = ptr->arr[ptr->top];
    ptr->top--;
    return val;
}

struct node *preorder(struct node *root)
{
    struct stack *sp = (struct stack *)malloc(sizeof(struct stack));
    sp->size = 30;
    sp->top = -1;
    while (1)
    {
        while (root != NULL)
        {
            printf("%d", root->data);
            if (root->r != NULL)
            {
                push(sp, root->r);
            }
            root = root->l;
        }
        if (!isEmpty(sp))
        {
            pop(sp);
        }
        else
        {
            break;
        }
    }
}

int main()
{
    struct node *root = NULL;
    int n, val;
    printf("Enter no.of node: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        root = insert(root, val);
    }
    return 0;
}