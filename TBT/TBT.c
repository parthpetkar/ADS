#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    char data;
    bool lbit, rbit;
    struct node *left, *right;
};

struct node *TBTcreate(struct node *head, char key)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    head->lbit = head->rbit = 0;
    head->right = head->left = head;
    temp->data = key;
    if (head->left == head)
    {
        temp->left = head;
        temp->right = head;
        head->left = temp;
        head->lbit = 1;
        return head;
    }
    else
    {
        struct node *p = head->left;
        while (1)
        {
            if (key < p->data && p->lbit == 1)
            {
                p = p->left;
            }
            else if (key > p->data && p->rbit == 1)
            {
                p = p->right;
            }
            else
            {
                break;
            }
        }
        if (key > p->data)
        {
            temp->right = p->right;
            temp->left = p;
            p->right = temp;
            p->rbit = 1;
        }
        else
        {
            temp->left = p->left;
            temp->right = p;
            p->left = temp;
            p->lbit = 1;
        }
    }
    return head;
}

void inorder(struct node *root)
{
    if (root == NULL)
        return;

    struct node *current = root->left;
    while (current != root)
    {
        while (current->lbit == 1)
            current = current->left;

        printf("%c ", current->data);

        while (current->rbit == 0)
        {
            current = current->right;
            if (current == root)
                return;
            printf("%c ", current->data);
        }

        current = current->right;
    }
}

void preorder(struct node *root)
{
    if (root == NULL)
        return;

    struct node *current = root->left;
    while (current != root)
    {
        printf("%c ", current->data);

        while (current->lbit == 1)
        {
            current = current->left;
            printf("%c ", current->data);
        }

        while (current->rbit == 0)
            current = current->right;

        current = current->right;
    }
}

int main()
{
    int choice;
    char num;
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->lbit = root->rbit = 1;
    root->left = root->right = root;

    do
    {
        printf("\nProgram of Threaded Tree in C\n");
        printf("1.Insert\n");
        printf("2.Inorder Traversal\n");
        printf("3.Preorder Traversal\n");
        printf("4.Quit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter the character to be inserted : ");
            scanf(" %c", &num);
            root = TBTcreate(root, num);
            break;
        case 2:
            printf("\nInorder Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 3:
            printf("\nPreorder Traversal: ");
            preorder(root);
            printf("\n");
            break;
        case 4:
            exit(0);
        default:
            printf("\nWrong choice\n");
        }
    } while (choice != 4);

    return 0;
}
