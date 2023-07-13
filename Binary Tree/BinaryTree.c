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

        printf("Enter left child of the tree:");
        temp->left = create();

        printf("Enter right child of the tree:");
        temp->right = create();
    }
    else
    {
        printf("Invalid choice!\n");
        return NULL;
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
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            root = create();
            break;
        case 2:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 2);

    return 0;
}
