#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <limits.h>


 struct node
{
    int data;
    struct node *left  ;
    struct node *right ;   

};

 struct queue{

    struct node** arr;
    int size;
    int front, rare;

};

void enqueue(struct queue* q,struct node* root){
    if(root == NULL){
        return;
    }
    q->arr[q->rare++] = root;
}

int dequeue(struct queue*q){
    int a = (q->arr[q->front])->data;
    q->front++;
    return a;
}

struct node* SearchNode(struct node *root, int parent_data){

    struct queue* q = (struct queue*)malloc(sizeof(queue));
    q->arr = (struct node*)malloc(sizeof(node)*20);
    q->size = 20;
    q->front = 0;
    q->rare = 0;

    enqueue(q,root);
    while(q->front != q->rare){

        struct node* current = q->arr[q->front];
        if(current->data == parent_data){
            return current;
        }
        enqueue(q, current->left);
        enqueue(q, current->right);
        q->front++;
    }

    printf("\nInvalid Parent Entered\n");
    return root;
}

struct node* create(node* root, int data){

    struct node *x = (struct node*) malloc (sizeof(node));
    x->data = data;
    x->left = x->right = NULL;
    root = x;
    return root;
}

struct node* insert (struct node *root, int parent, int data, char pos) {

        struct node *x = (struct node*) malloc (sizeof(node));
        x->data = data;
        x->left = x->right = NULL;

    struct node* temp = SearchNode(root,parent);
    if(pos == 'L' && !temp->left){
        temp->left = x;
    }
    else if(pos == 'R' && !temp->right){
        temp->right = x;
    }
    else{
        printf("\nKey already exists\n");
    }
    return root;
}

void LevelOrderTraversal(struct node* root){

    struct queue* q = (struct queue*)malloc(sizeof(queue));
    q->arr = (struct node*)malloc(sizeof(node)*20);
    q->size = 20;
    q->front = 0;
    q->rare = 0;

    enqueue(q,root);
    while(q->front != q->rare){

       struct node* current = q->arr[q->front];
        enqueue(q, current->left);
        enqueue(q, current->right);
        printf("%d ", dequeue(q));
    }
}

int maxfunc(int a, int b){
    if(a>b)
        return a;
    else 
        return b;
}

int maxHeight(struct node* root){

    //base case
    if (root == NULL){
        return 0;
    }
    //recursive case
    int leftDepth = maxHeight(root->left);
    int rightDepth = maxHeight(root->right);

    return maxfunc(leftDepth, rightDepth)+1;
}

void MirrorImage(node *root){

    if (root != NULL)
    {  
        struct node* temp;
        MirrorImage(root->left);      
        MirrorImage(root->right);     
        temp = root->left;
        root->left  = root->right;   
        root->right = temp;
    }
}

bool isMirror(struct node* leftSubtree,struct node* rightSubtree) {

    if (leftSubtree == NULL && rightSubtree == NULL)
        return true;
    if (leftSubtree == NULL || rightSubtree == NULL)
        return false;

    return (leftSubtree->data == rightSubtree->data) && isMirror(leftSubtree->left, rightSubtree->right) && 
            isMirror(leftSubtree->right, rightSubtree->left);
}

bool isSymmetric(struct node* root) {
    if (root == NULL)
        return true;

    return isMirror(root->left, root->right);
}


bool isBSTUntil(struct node* root, int min, int max) {
    if (root == NULL)
        return true;

    if (root->data < min || root->data > max)
        return false;

    return isBSTUntil(root->left, min, root->data - 1) &&
           isBSTUntil(root->right, root->data + 1, max);
}

bool isBST(struct node* root) {
    return isBSTUntil(root, INT_MIN, INT_MAX);
}

void printLeafNodes(struct node* root){
    
    if(root!=NULL){
        if(!(root->left) && !(root->right)){
            printf("%d ",root->data);
            return ;
        }
        if(root->left)
            printLeafNodes(root->left);
        if(root->right)
            printLeafNodes(root->right);
        return;
    }
}

int main() {

    struct node *root = NULL;
    int parent; 
    int n;
    char position;
    int choice = 1;
    int data;

    do {

        printf("What do you want to do:\n 1. Create Tree\n 2. Insert node\n 3. LevelOrder Traversal\n 4. Height \n 5. Mirror Image \n");
        printf(" 6. Check Symmetricity \n 7. Check BST \n 8. Print leaf nodes \n");
        scanf("%d", &n);

        switch(n) {
            case 1:
                printf("Enter the data of the root of the tree\n");
                scanf("%d", &data);
                root = create(root, data);
                break;
            case 2:
                printf("Enter the data, it's parent and whether it is left(L) or right(R) child\n");
                scanf("%d", &data);
                fflush(stdin);
                scanf("%d", &parent);
                fflush(stdin);
                scanf("%c", &position);
                root = insert(root, parent, data, position);
                break;

            case 3:
                LevelOrderTraversal(root);
                break;
            case 4:
                printf("The depth of the tree is : %d\n",maxHeight(root));
                break;
            case 5:
                printf("The Mirror Image of the Tree is \n");
                MirrorImage(root);
                LevelOrderTraversal(root);
                break;
            case 6:
                if(isSymmetric(root)){
                    printf("\nTHE TREE IS SYMMETRIC\n");
                }
                else{
                    printf("\nTHE TREE IS NOT SYMMETRIC\n");
                }
                break;
              case 7:
                if(isBST(root))
                    printf("\n The given tree is a BST\n");
                else
                    printf("\n The given tree is not a BST\n");
                break;
            case 8:
                printf("\nThe Leaf Nodes are : ");
                printLeafNodes(root);
                printf("\n");
                break;
        }   
        printf("\nDo you want to continue? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);

    } while(choice);
    
    return 0;
}