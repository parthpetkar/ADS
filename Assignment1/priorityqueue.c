#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int priority;
    struct node *next;
};

struct node *front;
struct node *rear;

void insert()
{
    struct node *ptr, *temp;
    int item, priority;

    ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL)
    {
        printf("OVERFLOW\n");
        return;
    }
    else
    {
        printf("\nEnter value: ");
        scanf("%d", &item);
        printf("Enter priority: ");
        scanf("%d", &priority);

        ptr->data = item;
        ptr->priority = priority;

        // If the queue is empty or the new element has higher priority than the front
        if (front == NULL || priority < front->priority)
        {
            ptr->next = front;
            front = ptr;
        }
        else
        {
            temp = front;
            while (temp->next != NULL && temp->next->priority <= priority)
            {
                temp = temp->next;
            }
            ptr->next = temp->next;
            temp->next = ptr;
        }
    }
}

void deleteByPriority()
{
    struct node *ptr, *temp;
    if (front == NULL)
    {
        printf("UNDERFLOW\n");
        return;
    }
    else
    {
        ptr = front;
        if (ptr->next == NULL)
        {
            front = NULL;
            free(ptr);
        }
        else
        {
            while (ptr->next != NULL)
            {
                if (ptr->next->priority == front->priority)
                {
                    temp = ptr->next;
                    ptr->next = temp->next;
                    free(temp);
                }
                else
                {
                    ptr = ptr->next;
                }
            }
            if (front->priority == ptr->priority)
            {
                temp = front;
                front = front->next;
                free(temp);
            }
        }
    }
}

void display()
{
    struct node *ptr;
    ptr = front;
    if (front == NULL)
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("\nPrinting values: ");
        while (ptr != NULL)
        {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
    }
}

int main()
{
    int ch;
    front = rear = NULL;

    while (ch != 5)
    {
        printf("\n1. Insert an element\n2. Delete elements by priority\n3. Display the queue\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            insert();
            break;
        case 2:
            deleteByPriority();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Enter a valid choice.\n");
        }
    }

    return 0;
}
