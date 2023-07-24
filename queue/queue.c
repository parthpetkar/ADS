#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int queue[MAX], rear = -1, front = -1;

void nqueue()
{
    int num;
    if (rear == MAX - 1)
    {
        printf("Overflow\n");
    }
    else
    {
        printf("Enter the number to be inserted: ");
        scanf("%d", &num);
        rear = rear + 1;
        queue[rear] = num;
        if (front == -1)
        {
            front = 0;
        }
    }
}

void dqueue()
{
    if (front == -1 || front > rear)
    {
        printf("Underflow\n");
    }
    else
    {
        printf("Deleted element = %d\n", queue[front]);
        front = front + 1;
    }
}

void display()
{
    int i;
    if (front == -1 || front > rear)
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("Queue elements: ");
        for (i = front; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main()
{
    int ch;
    do
    {
        printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            nqueue();
            break;
        case 2:
            dqueue();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (ch != 4);

    return 0;
}
