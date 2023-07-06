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

struct node *search(struct node *root, int data)
{
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
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

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d\n", root->data);
}
void inorderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d\n", root->data);
    inorderTraversal(root->right);
}
int main()
{
    int ch, item;
    struct node *root = NULL;

    do
    {
        printf("1. Insert\n");
        printf("2. Preorder\n");
        printf("3. Postorder\n");
        printf("4. Inorder\n");
        printf("5. Search\n");
        printf("6. Exit\n");
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
            printf("Enter element to be searched:");
            scanf("%d", &item);
            if (search(root, item) == NULL)
            {
                printf("Not Found!!\n");
            }
            else
            {
                printf("Found\n");
            }
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (ch != 7);

    return 0;
}
