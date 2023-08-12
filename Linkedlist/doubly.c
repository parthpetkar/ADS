#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;
struct node *ptr, *temp;

void insert_beg()
{
    int item;
    printf("Enter a element:");
    scanf("%d\n", &item);
    ptr->data = item;
    ptr->next = NULL;
    ptr->prev = NULL;
    if (ptr == NULL)
    {
        printf("OverFlow\n");
    }
    else
    {
        if (head == NULL)
        {
            head = ptr;
        }
        else
        {
            ptr->next = head;
            head->prev = ptr;
            head = ptr;
        }
    }
}
void insert_end()
{
    int item;
    printf("Enter a element:");
    scanf("%d\n", &item);
    ptr->data = item;
    ptr->next = NULL;
    if (ptr == NULL)
    {
        printf("OverFlow\n");
    }
    else
    {
        if (head == NULL)
        {
            head = ptr;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->prev = temp;
            ptr->next = NULL;
        }
    }
}
void insert_random()
{
    int item, loc;
    printf("Enter a element:");
    scanf("%d\n", &item);
    printf("Enter the location for insertion:");
    scanf("%d", &loc);
    ptr->data = item;
    ptr->next = NULL;
    if (ptr == NULL)
    {
        printf("OverFlow\n");
    }
    else
    {
        if (head == NULL)
        {
            head = ptr;
        }
        else
        {
            temp = head;
            for (int i = 0; i < loc; i++)
            {
                temp = temp->next;
            }
            ptr->next = temp->next;
            ptr->prev = temp;
            temp->next = ptr;
            temp->next->prev = ptr;
        }
    }
}
void deletebeg()
{
    if (head->next == NULL)
    {
        head = NULL;
        free(head);
    }
    else
    {
        ptr = head;
        head = head->next;
        head->prev = NULL;
        free(ptr);
    }
}
void deleteend()
{
    if (head->next == NULL)
    {
        head = NULL;
        free(head);
    }
    else
    {
        ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->prev->next = NULL;
    }
}
void deletion_specified()
{
    int val;
    printf("\n Enter the data after which the node is to be deleted : ");
    scanf("%d", &val);
    ptr = head;
    while (ptr->data != val)
        ptr = ptr->next;
    if (ptr->next == NULL)
    {
        printf("\nCan't delete\n");
    }
    else if (ptr->next->next == NULL)
    {
        ptr->next = NULL;
    }
    else
    {
        temp = ptr->next;
        ptr->next = temp->next;
        temp->next->prev = ptr;
        free(temp);
        printf("\nnode deleted\n");
    }
}
void display()
{
    printf("\n printing values...\n");
    ptr = head;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
}
