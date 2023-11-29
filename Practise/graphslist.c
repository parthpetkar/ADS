#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};

struct node *adjlist[100];
int visited[100];
void addedge(int a, int b)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = b;
    newnode->next = adjlist[a];
    adjlist[a] = newnode;

    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = a;
    newnode->next = adjlist[b];
    adjlist[b] = newnode;
}

BFSTraversal(int start, int V)
{
    int queue[100], rear, front, curr;
    struct node *temp;
    rear = front = -1;
    queue[++rear] = start;
    visited[start] = 1;
    while (front != rear)
    {
        curr = queue[++front];
        printf("%d ", curr);
        temp = adjlist[curr];
        while (temp != NULL)
        {
            if (visited[temp->data] = 1)
            {
                queue[++rear] = temp->data;
                visited[temp->data] = 1;
            }
            temp = temp->next;
        }
    }
}
DFSTraversal(int start)
{
    struct node *temp;
    visited[start] = 1;
    printf("%d ", start);
    temp = adjlist[start];
    while (temp != NULL)
    {

        if (visited[temp->data] != 1)
        {
            DFSTraversal(temp->data);
        }
        temp = temp->next;
    }
}
int main()
{
    int V, E, v1, v2, source;
    printf("-----DFS and BFS Traversal of Graph using Adjacency Matrix-----\n");
    printf("Enter number of Vertices : ");
    scanf("%d", &V);
    printf("Enter number of Edges : ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }

    for (int k = 0; k < E; k++)
    {
        int v1, v2;
        printf("Enter the Edges (Format : V1 V2) -> ");
        scanf("%d %d", &v1, &v2);
        addedge(v1, v2);
    }

    printf("\nEnter the Source : ");
    scanf("%d", &source);
    printf("\nBFS Traversal of Graph using Adjacency Matrix : ");
    BFSTraversal(source, V);
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
    printf("\nDFS Traversal of Graph using Adjacency Matrix : ");
    DFSTraversal(source);
    printf("\n");

    return 0;
}