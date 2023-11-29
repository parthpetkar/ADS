#include <stdio.h>

struct student
{
    int roll;
    char name[50];
    int marks;
};

struct student arr[3];
int n = sizeof(arr) / sizeof(arr[0]);

void swap(struct student *l, struct student *h)
{
    struct student temp;
    temp = *l;
    *l = *h;
    *h = temp;
}
int partition(int p, int q)
{
    int i = p + 1;
    int j = q;

    while (1)
    {
        while (arr[i].roll <= arr[p].roll)
        {
            i++;
        }
        while (arr[j].roll > arr[p].roll)
        {
            j--;
        }
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
        else
        {
            swap(&arr[j], &arr[p]); 
            break;
        }
       
    }
    // swap(&arr[j],&arr[p]);
    return j;
}
void quicksort(int l, int h)
{
    if (l < h)
    {
        int j = partition(l, h);
        quicksort(l, j - 1);
        quicksort(j + 1, h);
    }
}
int main()
{
    printf("---Quick sort---");
    printf("\nEnter the details of students - \n");
    for (int i = 0; i < n; i++)
    {
        printf("Name : ");
        scanf("%s",&arr[i].name);
        printf("Roll no : ");
        scanf("%d", &arr[i].roll);
        printf("Marks : ");
        scanf("%d",&arr[i].marks);
    }

    printf("\n");

    quicksort(0, n - 1);
    printf("The students in sorted order - \n");
    printf("\nName\tRoll no\tMarks\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t %d\n", arr[i].name, arr[i].roll,arr[i].marks);
    }

    return 0;
}