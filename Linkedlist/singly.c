#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 100

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *ptr, *temp;

void insert_beg()
{
    int item;
    ptr = (struct node *)malloc(sizeof(struct node));
    printf("Enter an element: ");
    scanf("%d", &item);
    ptr->data = item;
    ptr->next = NULL;

    if (ptr == NULL)
    {
        printf("Overflow\n");
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
            head = ptr;
        }
    }
}

void insert_end()
{
    int item;
    ptr = (struct node *)malloc(sizeof(struct node));
    printf("Enter an element: ");
    scanf("%d", &item);
    ptr->data = item;
    ptr->next = NULL;

    if (ptr == NULL)
    {
        printf("Overflow\n");
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
            ptr->next = NULL; 
        }
    }
}

void insert_random()
{
    int item, loc;
    ptr = (struct node *)malloc(sizeof(struct node));
    printf("Enter an element: ");
    scanf("%d", &item);
    printf("Enter the location you want to insert: ");
    scanf("%d", &loc);
    ptr->data = item;
    ptr->next = NULL;

    if (ptr == NULL)
    {
        printf("Overflow\n");
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
            for (int i = 1; i < loc; i++)
            {
                temp = temp->next;
                if (temp == NULL)
                {
                    printf("Location doesn't exist\n");
                    return;
                }
            }
            ptr->next = temp->next;
            temp->next = ptr;
        }
    }
}

void delete_beg()
{
    if (head == NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        ptr = head;
        head = head->next;
        free(ptr);
    }
}

void delete_end()
{
    if (head == NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        ptr = head;
        while (ptr->next != NULL)
        {
            temp = ptr;
            ptr = ptr->next;
        }
        if (ptr == head)
        {
            head = NULL;
        }
        else
        {
            temp->next = NULL;
        }
        free(ptr);
    }
}

void delete_random()
{
    int loc, i = 1;
    printf("Enter the location you want to delete: ");
    scanf("%d", &loc);
    if (head == NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        ptr = head;
        if (loc == 1)
        {
            head = ptr->next;
            free(ptr);
        }
        else
        {
            while (i < loc && ptr != NULL)
            {
                temp = ptr;
                ptr = ptr->next;
                i++;
            }
            if (ptr == NULL)
            {
                printf("Location doesn't exist\n");
                return;
            }
            temp->next = ptr->next;
            free(ptr);
        }
    }
}
void display()  
{    
    ptr = head;   
    if(ptr == NULL)  
    {  
        printf("Nothing to print");  
    }  
    else  
    {  
        printf("\nPrinting values: ");   
        while (ptr!=NULL)  
        {  
            printf("%d ",ptr->data);  
            ptr = ptr -> next;  
        }  
        printf("\n");
    }  
}  
void main()
{
    int ch;
    do
    {
        printf("1. Insert at Beginning\n2. Insert at End\n3. Insert at random position\n");
        printf("4. Delete at Beginning\n5. Delete at End\n6. Delete at random position\n");
        printf("7. Display\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            insert_beg();
            break;
        case 2:
            insert_end();
            break;
        case 3:
            insert_random();
            break;
        case 4:
            delete_beg();
            break;
        case 5:
            delete_end();
            break;
        case 6:
            delete_random();
            break;
        case 7:
            display();
            break;
        case 8:
            printf("Exit!!!");
            break;
        default:
            printf("Enter correct choice!");
            break;
        }
    } while (ch != 8);
}