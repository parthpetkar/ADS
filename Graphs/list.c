#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *adjList[100];
int visited[100];

void addEdge(int a, int b)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = b;
    newNode->next = adjList[a];
    adjList[a] = newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = a;
    newNode->next = adjList[b];
    adjList[b] = newNode;
}

void printGraph(int v)
{
    struct node *temp;
    for (int i = 0; i < v; i++)
    {
        printf("%d : ", i);
        temp = adjList[i];
        while (temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("Null\n");
    }
}

void bfs(int start, int v)
{
    int queue[100], rear, front, curr;
    rear = -1;
    front = -1;

    struct node *temp;
    queue[++rear] = start;
    visited[start] = 1;
    while (front != rear)
    {
        curr = queue[++front];
        printf("%d ", curr);
        temp = adjList[curr];
        while (temp != NULL)
        {
            if (visited[temp->data] != 1)
            {
                queue[++rear] = temp->data;
                visited[temp->data] = 1;
            }
            temp = temp->next;
        }
    }
}

void dfs(int start)
{
    visited[start] = 1;
    printf("%d ", start);
    struct node *temp;
    temp = adjList[start];
    while (temp != NULL)
    {
        if (visited[temp->data] != 1)
        {
            dfs(temp->data);
        }
        temp = temp->next;
    }
}

int main()
{
    int v, e;
    int a, b;
    int start;

    printf("Enter no of vertex: ");
    scanf("%d", &v);
    printf("Enter no of edges : ");
    scanf("%d", &e);

    for (int i = 0; i < v; i++)
    {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    for (int i = 0; i < e; i++)
    {
        printf("Enter edge %d (u, v): ", i + 1);
        scanf("%d %d", &a, &b);
        addEdge(a, b);
    }

    printf("Adjacency List: \n");
    printGraph(v);

    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);
    printf("BFS traversal: ");
    bfs(start, v);

    for (int i = 0; i < v; i++)
    {
        visited[i] = 0;
    }

    printf("\nEnter starting vertex for DFS: ");
    scanf("%d", &start);
    printf("DFS traversal: ");
    dfs(start);

    return 0;
}
