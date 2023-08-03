#include <stdio.h>
#include <stdlib.h>

struct ThreadedTreeNode {
    int data;
    struct ThreadedTreeNode *left;
    struct ThreadedTreeNode *right;
    int isThreadedRight; 
};

typedef struct ThreadedTreeNode ThreadedTreeNode;

ThreadedTreeNode *createThreadedNode(int data) {
    ThreadedTreeNode *newNode = (ThreadedTreeNode *)malloc(sizeof(ThreadedTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreadedRight = 0;
    return newNode;
}

ThreadedTreeNode *insert(ThreadedTreeNode *root, int data) {
    if (root == NULL) {
        return createThreadedNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

ThreadedTreeNode *findInorderSuccessor(ThreadedTreeNode *node) {
    if (node->isThreadedRight) {
        return node->right;
    }

    node = node->right;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void createThreads(ThreadedTreeNode *root, ThreadedTreeNode **prev) {
    if (root == NULL) {
        return;
    }

    createThreads(root->left, prev);

    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreadedRight = 1;
    }
    *prev = root;

    createThreads(root->right, prev);
}

void preorderTraversal(ThreadedTreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorderTraversal(root->left);
    if (root->isThreadedRight) {
        preorderTraversal(root->right);
    }
}

void inorderTraversal(ThreadedTreeNode *root) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    if (root->isThreadedRight) {
        inorderTraversal(root->right);
    }
}

void postorderTraversal(ThreadedTreeNode *root) {
    if (root == NULL) {
        return;
    }

    if (root->isThreadedRight) {
        postorderTraversal(root->right);
    }
    postorderTraversal(root->left);
    printf("%d ", root->data);
}

int main() {
    ThreadedTreeNode *root = NULL;

    int choice, data;
    do {
        printf("1. Insert Node\n");
        printf("2. Create Threads\n");
        printf("3. Preorder Traversal\n");
        printf("4. Inorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                ThreadedTreeNode *prev = NULL;
                createThreads(root, &prev);
                printf("Threads created.\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}
