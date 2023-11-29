#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *front;
struct node *rear;
void insert()
{
    struct node *ptr;
    int item;

    ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL)
    {
        printf("OVERFLOW\n");
        return;
    }
    else
    {
        printf("\nEnter value:");
        scanf("%d", &item);
        ptr->data = item;
        if (front == NULL)
        {
            front = ptr;
            rear = ptr;
            front->next = NULL;
            rear->next = NULL;
        }
        else
        {
            rear->next = ptr;
            rear = ptr;
            rear->next = NULL;
        }
    }
}
void delete()
{
    struct node *ptr;
    if (front == NULL)
    {
        printf("UNDERFLOW\n");
        return;
    }
    else
    {
        ptr = front;
        front = front->next;
        free(ptr);
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
        printf("\nprinting values:");
        while (ptr != NULL)
        {
            printf("%d", ptr->data);
            ptr = ptr->next;
        }
    }
}
void main()
{
    int ch;
    while (ch != 4)
    {
        printf("\n1.insert an element\n2.Delete an element\n3.Display the queue\n4.Exit\n");
        printf("\nEnter your choice:");
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
            exit(0);
            break;
        default:
            printf("Enter valid choice??\n");
        }
    }
}
