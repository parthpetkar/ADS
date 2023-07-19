#include <stdio.h>
#define Max 100
int stack[100], i, j, ch = 0, n, top = -1;
void push();
void pop();
void show();
void main()
{
    while (ch != 4)
    {
        printf("\n1. Push\n2. Pop\n3. Show\n4. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            push();
            break;
        }
        case 2:
        {
            pop();
            break;
        }
        case 3:
        {
            show();
            break;
        }
        case 4:
        {
            printf("Exiting....\n");
            break;
        }
        default:
        {
            printf("Please Enter valid choice\n");
        }
        };
    }
}

void push()
{
    int val;
    if (top == Max - 1)
        printf("Overflow\n");
    else
    {
        printf("Enter the value:");
        scanf("%d", &val);
        top = top + 1;
        stack[top] = val;
    }
}

void pop()
{
    if (top == -1)
        printf("Underflow\n");
    else
        top = top - 1;
}
void show()
{
    for (i = top; i <= 0; i++)
    {
        printf("%d ", stack[i]);
    }
    if (top == -1)
    {
        printf("Stack is empty\n");
    }
}