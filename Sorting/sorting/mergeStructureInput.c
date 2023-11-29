#include <stdio.h>

struct student
{
    int roll;
    char name[50];
    int marks;
};

struct student a[3];
int n = sizeof(a) / sizeof(a[0]);

void merge( int mid, int low, int high)
{
    int i, j, k;
    struct student b[50];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (a[i].roll < a[j].roll)
        {
            b[k] = a[i];
            i++;
            k++;
        }
        else
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        b[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        b[k] = a[j];
        k++;
        j++;
    }
    for (int i = 0; i <= high; i++)
    {
        a[i] = b[i];
    }
}

void mergesort(int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergesort(low, mid);
        mergesort(mid + 1, high);
        merge(mid, low, high);
    }

}

int main()
{
    printf("---Merge sort---");
    printf("\nEnter the details of students - \n");
    for (int i = 0; i < n; i++)
    {
        printf("Name : ");
        scanf("%s", &a[i].name);
        printf("Roll no : ");
        scanf("%d", &a[i].roll);
         printf("Marks : "); 
        scanf("%d",&a[i].marks);
    }

        printf("\n");

        mergesort(0, n-1);

        printf("The students in sorted order - \n");
        printf("\nName\tRoll no\tMarks\n");
        for (int i = 0; i < n; i++)
        {
            printf("%s\t%d\t%d \n", a[i].name, a[i].roll,a[i].marks);
        }

        return 0;
    

    
}