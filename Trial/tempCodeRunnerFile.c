#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Node
{
    int vertex;
    int weight;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    int vertices;
    struct List *array;
    int **matrix;
};

struct Node *createNode(int vertex, int weight)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct List *)malloc(vertices * sizeof(struct List));
    graph->matrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; ++i)
    {
        graph->array[i].head = NULL;
        graph->matrix[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; ++j)
        {
            graph->matrix[i][j] = INT_MAX;
        }
    }
    return graph;
}

void addEdgeList(struct Graph *graph, int src, int dest, int weight)
{
    struct Node *newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addEdgeMatrix(struct Graph *graph, int src, int dest, int weight)
{
    graph->matrix[src][dest] = weight;
}

int minDistance(int dist[], int visited[], int vertices)
{
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; ++v)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        printf("%d ", j);
        return;
    }
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void printSolution(int dist[], int parent[], int src, int vertices)
{
    printf("Vertex\t Distance\tPath\n");
    for (int i = 0; i < vertices; ++i)
    {
        if (i != src)
        {
            printf("%d -> %d\t %d\t\t%d ", src, i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

void dijkstraList(struct Graph *graph, int src)
{
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;
    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;
        struct Node *temp = graph->array[u].head;
        while (temp != NULL)
        {
            int v = temp->vertex;
            int weight = temp->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    printSolution(dist, parent, src, vertices);
}

void dijkstraMatrix(struct Graph *graph, int src)
{
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;
    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;
        for (int v = 0; v < vertices; ++v)
        {
            if (!visited[v] && dist[u] != INT_MAX && graph->matrix[u][v] != INT_MAX && dist[u] + graph->matrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph->matrix[u][v];
                parent[v] = u;
            }
        }
    }
    printSolution(dist, parent, src, vertices);
}

int main()
{
    int vertices, edges, src, dest, weight, choice;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);
    struct Graph *graph = createGraph(vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; ++i)
    {
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdgeList(graph, src, dest, weight);
        addEdgeMatrix(graph, src, dest, weight);
    }
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    printf("Choose representation method:\n");
    printf("1. Adjacency List\n");
    printf("2. Adjacency Matrix\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        dijkstraList(graph, src);
        break;
    case 2:
        dijkstraMatrix(graph, src);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }

    // Free allocated memory
    for (int i = 0; i < vertices; ++i)
    {
        free(graph->matrix[i]);
    }
    free(graph->array);
    free(graph);

    return 0;
}
