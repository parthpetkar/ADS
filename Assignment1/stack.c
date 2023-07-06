#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct node
{
    int data;
    struct node *next;
};

struct node *top = NULL;
struct node *ptr;

void push(int num)
{
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = num;

    ptr->next = top;
    top = ptr;
}

void pop()
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    ptr = top;
    top = top->next;
    free(ptr);
}

void display()
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("\nPrinting values: ");
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    int ch, num;

    do
    {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter a number: ");
            scanf("%d", &num);
            push(num);
            break;
        case 2:
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (ch != 4);

    return 0;
}
