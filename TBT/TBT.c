#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThreaded;
};

struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 1; 
    return newNode;
}

void insert(struct TreeNode** root, int key) {
    struct TreeNode* new_node = createNode(key);
    if (*root == NULL) {
        *root = new_node;
    } else {
        struct TreeNode* current = *root;
        while (1) {
            if (key < current->key) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new_node;
                    new_node->right = current;
                    new_node->isThreaded = 1;
                    break;
                }
            } else if (key > current->key) {
                if (current->isThreaded) {
                    new_node->right = current->right;
                    new_node->isThreaded = 1;
                    current->right = new_node;
                    current->isThreaded = 0;
                }
                current = current->right;
            } else {
                break;
            }
        }
    }
}

void inorder(struct TreeNode* root) {
    struct TreeNode* current = root;
    while (current) {
        while (current->left) {
            current = current->left;
        }
        printf("%d ", current->key);

        if (current->isThreaded) {
            current = current->right;
        } else {
            current = current->right;
            while (current && !current->isThreaded) {
                current = current->left;
            }
        }
    }
}

void preorder(struct TreeNode* root) {
    struct TreeNode* current = root;
    while (current) {
        printf("%d ", current->key);

        if (current->left) {
            current = current->left;
        } else if (current->isThreaded) {
            current = current->right;
        } else {
            current = current->right;
            while (current && !current->isThreaded) {
                current = current->left;
            }
        }
    }
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    while (1) {
        printf("\nBinary Search Tree Menu:\n");
        printf("1. Insert a key\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                printf("Key %d inserted into the BST.\n", key);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
