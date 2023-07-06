#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *ptr(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int data)
{
    if (root == NULL)
        return ptr(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}
void preorderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    printf("%d\n", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
void postorderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    preorderTraversal(root->left);
    preorderTraversal(root->right);
    printf("%d\n", root->data);
}
void inorderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    preorderTraversal(root->left);
    printf("%d\n", root->data);
    preorderTraversal(root->right);
}
int main()
{
    int ch, item;
    struct node *root = NULL;

    do
    {
        printf("1. Insert\n");
        printf("2. Preorder\n");
        printf("3. Preorder\n");
        printf("4. Preorder\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter value to be inserted: ");
            scanf("%d", &item);
            root = insert(root, item);
            break;
        case 2:
            preorderTraversal(root);
            break;
        case 3:
            postorderTraversal(root);
            break;
        case 4:
            inorderTraversal(root);
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (ch != 6);

    return 0;
}
