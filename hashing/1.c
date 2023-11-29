#include <stdio.h>

#define SIZE 10
#define h(x) x % SIZE

void insert(int data[], int flag[], int chain[], int key)
{

    int i = 0, j, start = h(key);

    while (flag[start] && i < SIZE)
    {
        if (data[start] % SIZE == key % SIZE)
            break;
        i++;
        start = (start + 1) % SIZE;
    }

    while (chain[start] != -1)
        start = chain[start];
    j = start;

    while (flag[j] && j < SIZE)
    {
        j = (j + 1) % SIZE;
        i = i + 1;
    }

    data[j] = key;
    flag[j] = 1;

    if (j != start)
        chain[start] = j;
}

void display(int data[], int flag[], int chain[])
{

    for (int i = 0; i < SIZE; i++)
    {
        if (flag[i])
            printf("\n%d %d %d", i, data[i], chain[i]);
        else
            printf("\n%d ---- %d", i, chain[i]);
    }
}

int main()
{

    int data[SIZE], flag[SIZE], chain[SIZE], op, key;

    for (int i = 0; i < SIZE; i++)
    {
        flag[i] = 0;
        chain[i] = -1;
    }

    printf("Enter no. of keys to be inserted: ");
    scanf("%d", &op);

    for (int i = 0; i < op; i++)
    {
        printf("Enter key to be inserted: ");
        scanf("%d", &key);
        insert(data, flag, chain, key);
    }

    printf("\nHash table: ");
    display(data, flag, chain);

    return 0;
}