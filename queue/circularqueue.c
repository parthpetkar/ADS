#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int queue[MAX], rear = -1, front = -1;

void insert()
{
    int item;
    if ((rear + 1) % MAX == front)
    {
        printf("Overflow\n");
        return;
    }
    else
    {
        printf("Enter the element to be inserted: ");
        scanf("%d", &item);
        if (front == -1 && rear == -1)
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % MAX;
        }
        queue[rear] = item;
    }
}

void delete()
{
    if (front == -1)
    {
        printf("Underflow\n");
    }
    else
    {
        printf("Deleted element: %d\n", queue[front]);
        if (front == rear)
        {
            front = rear = -1;
        }
        else if (front == MAX - 1)
        {
            front = 0;
        }
        else
        {
            front = (front + 1) % MAX;
        }
    }
}

void display()
{
    int i = front;
    if (front == -1 && rear == -1)
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("\nElements in a Queue are : ");
        while (i <= rear)
        {
            printf("%d ", queue[i]);
            i = (i + 1) % MAX;
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
            insert();
            break;
        case 2:
            delete ();
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