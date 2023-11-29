#include <stdio.h>
struct student
{
    int roll;
    char name[500];
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
void heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].roll > arr[largest].roll)
    {
        largest = left;
    }
    if (right < n && arr[right].roll > arr[largest].roll)
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(n, largest);
    }
}
void heapsort(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(i, 0);
    }
}

int main()
{
    printf("---Heap sort---");
    printf("\nEnter the details of students - \n");
    for (int i = 0; i < n; i++)
    {
        printf("Name : ");
        scanf("%s", &arr[i].name);
        printf("Roll no : ");
        scanf("%d", &arr[i].roll);
        printf("Marks : ");
        scanf("%d",&arr[i].marks);
    }

    printf("\n");
    heapsort(n);

    printf("The students in sorted order - \n");
        printf("\nName\tRoll no\tMarks \n");
        for (int i = 0; i < n; i++)
        {
            printf("%s\t%d\t%d \n", arr[i].name, arr[i].roll,arr[i].marks);
        }

        return 0;

    
}