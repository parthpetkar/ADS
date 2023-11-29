#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

int V, E;
int A[30][30];

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
};

struct AdjListNode *newAdjListNode(int dest, int weight)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int vertex;
    int weight;
    struct Node *next;
};

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Node **adjList;
};

struct Node *createNode(int vertex, int weight)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->adjList = (struct Node **)malloc((V + 1) * sizeof(struct Node *));
    for (int i = 1; i <= V; i++)
    {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    struct Node *newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void prim(struct Graph *graph)
{
    int *visited = (int *)malloc((graph->V + 1) * sizeof(int));
    for (int i = 1; i <= graph->V; i++)
    {
        visited[i] = 0;
    }

    visited[1] = 1;

    printf("\nEdges in Minimum Cost Spanning Tree:\n");

    for (int ne = 1; ne < graph->V; ne++)
    {
        int min = 999, a, b;

        for (int i = 1; i <= graph->V; i++)
        {
            if (visited[i] != 0)
            {
                struct Node *temp = graph->adjList[i];
                while (temp != NULL)
                {
                    if (!visited[temp->vertex] && temp->weight < min)
                    {
                        min = temp->weight;
                        a = i;
                        b = temp->vertex;
                    }
                    temp = temp->next;
                }
            }
        }

        visited[b] = 1;

        printf("Edge %d: (%d, %d) cost: %d\n", ne, a, b, min);

        // Remove the edge from the graph (optional)
        // graph->adjList[a] = graph->adjList[b] = NULL;
    }

    free(visited);
}

int main()
{
    printf("-----Prim's algorithm-----\n");

    int V, E;
    printf("\nEnter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph *graph = createGraph(V, E);

    printf("\nEnter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++)
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    prim(graph);

    free(graph->adjList);
    free(graph);

    return 0;
}

    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; i++)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

void add_edge(struct Graph *graph, int src, int dest, int weight)
{
    struct AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

int minKey(int key[], bool mstSet[], int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

int printMST(int parent[], int key[], struct Graph *graph, int min)
{
    printf("\nEdge and Weight of Minimum Spanning Tree : \n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < graph->V; i++)
    {
        printf("%d - %d \t%d\n", parent[i] + 1, i + 1, key[i]);
    }
    printf("\nThe Minimum Cost of Spanning Tree is : %d\n", min);
}

void primMST(struct Graph *graph)
{
    int min_cost = 0;
    int V = graph->V;
    int parent[V], key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        struct AdjListNode *node = graph->array[u].head;
        while (node != NULL)
        {
            int v = node->dest;
            int weight = node->weight;

            if (mstSet[v] == 0 && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
            }

            node = node->next;
        }
    }

    for (int i = 0; i < V; i++)
    {
        min_cost += key[i];
    }

    printMST(parent, key, graph, min_cost);
}

void printAdjList(struct Graph *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        printf("Node %d : ", i + 1);
        struct AdjListNode *node = graph->array[i].head;
        while (node != NULL)
        {
            printf(" -> %d(%d)", node->dest + 1, node->weight);
            node = node->next;
        }
        printf("\n");
    }
}

int main()
{
    printf("Prim's Algorithm on Graph using Adjacency List\n\n");
    printf("Enter number of Vertices : ");
    scanf("%d", &V);
    struct Graph *graph = createGraph(V);

    printf("Enter number of Edges : ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++)
    {
        int v1, v2, weight;
        printf("Enter the Edges (Format : V1 V2) -> ");
        scanf("%d %d", &v1, &v2);
        printf("Enter Weight for Edge (%d %d) : ", v1, v2);
        scanf("%d", &weight);
        add_edge(graph, v1 - 1, v2 - 1, weight);
    }

    printf("\nThe Adjacency List is : \n");
    printAdjList(graph);

    primMST(graph);

    return 0;
}