#include <stdio.h>
#include <stdlib.h>

int source, V, E;
int visited_dfs[30], visited_bfs[30], A[30][30];

struct queue
{
    int size;
    int f;
    int r;
    int *arr;
};

int isEmpty(struct queue *q)
{
    if (q->r == q->f)
    {
        return 1;
    }
    return 0;
}

int isFull(struct queue *q)
{
    if (q->r == q->size - 1)
    {
        return 1;
    }
    return 0;
}

void enqueue(struct queue *q, int val)
{
    if (isFull(q))
    {
        printf("Queue Overflow\n");
    }
    else
    {
        q->r++;
        q->arr[q->r] = val;
    }
}

int dequeue(struct queue *q)
{
    int a;
    if (isEmpty(q))
    {
        printf("Queue Underflow\n");
    }
    else
    {
        q->f++;
        a = q->arr[q->f];
    }
    return a;
}

void BFSTraversal(int i)
{
    struct queue q;
    q.size = 30;
    q.f = q.r = 0;
    q.arr = (int *)malloc(q.size * sizeof(int));

    int size = sizeof(visited_bfs) / sizeof(int);

    printf("%d ", i + 1);
    visited_bfs[i] = 1;
    enqueue(&q, i);

    while (!isEmpty(&q))
    {
        int val = dequeue(&q);
        for (int j = 0; j < size; j++)
        {
            if (A[val][j] == 1 && visited_bfs[j] == 0)
            {
                printf("%d ", j + 1);
                visited_bfs[j] = 1;
                enqueue(&q, j);
            }
        }
    }
}

void DFSTraversal(int i)
{
    printf("%d ", i + 1);
    visited_dfs[i] = 1;
    for (int j = 0; j < V; j++)
    {
        if (A[i][j] != 0 && visited_dfs[j] != 1)
        {
            DFSTraversal(j);
        }
    }
}

int main()
{
    printf("-----DFS and BFS Traversal of Graph using Adjacency Matrix-----\n");
    printf("Enter number of Vertices : ");
    scanf("%d", &V);
    printf("Enter number of Edges : ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            A[i][j] = 0;
        }
    }

    for (int i = 0; i < V; i++)
    {
        visited_bfs[i] = 0;
        visited_dfs[i] = 0;
    }

    for (int k = 0; k < E; k++)
    {
        int v1, v2;
        printf("Enter the Edges (Format : V1 V2) -> ");
        scanf("%d %d", &v1, &v2);
        A[v1 - 1][v2 - 1] = A[v2 - 1][v1 - 1] = 1;
    }

    printf("\nThe Adjacency Matrix is : \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf(" %d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the Source : ");
    scanf("%d", &source);
    printf("\nDFS Traversal of Graph using Adjacency Matrix : ");
    DFSTraversal(source - 1);
    printf("\nBFS Traversal of Graph using Adjacency Matrix : ");
    BFSTraversal(source - 1);
    printf("\n");

    return 0;
}