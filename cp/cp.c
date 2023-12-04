#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Edge
{
    int source;
    int destination;
    int weight;
    struct Edge *next;
};

struct ResultSet
{
    int parent;
    int weight;
};

struct Graph
{
    int vertices;
    struct Edge *adjacencylist[MAX_VERTICES];
};

struct Edge *createEdge(int source, int destination, int weight)
{
    struct Edge *edge = (struct Edge *)malloc(sizeof(struct Edge));
    edge->source = source;
    edge->destination = destination;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

struct ResultSet *createResultSet(int parent, int weight)
{
    struct ResultSet *resultSet = (struct ResultSet *)malloc(sizeof(struct ResultSet));
    resultSet->parent = parent;
    resultSet->weight = weight;
    return resultSet;
}

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacencylist[i] = NULL;
    }
    return graph;
}

void display(struct ResultSet *resultSet[], int vertices)
{
    int total_min_weight = 0;
    printf("Minimum Spanning Tree: \n");
    for (int i = 1; i < vertices; i++)
    {
        printf("Edge: %d - %d weight: %d\n", i, resultSet[i]->parent, resultSet[i]->weight);
        total_min_weight += resultSet[i]->weight;
    }
    printf("Total minimum key: %d\n", total_min_weight);
}

void primMST(struct Graph *graph)
{
    int vertices = graph->vertices;
    struct ResultSet *resultSet[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool inMST[MAX_VERTICES];

    // Initialize keys and MST set
    for (int i = 0; i < vertices; i++)
    {
        resultSet[i] = createResultSet(-1, INT_MAX);
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    // Include the first vertex in MST
    key[0] = 0;
    resultSet[0]->parent = -1;

    // Construct MST
    for (int count = 0; count < vertices - 1; count++)
    {
        // Find the vertex with the minimum key value
        int minKey = INT_MAX;
        int minIndex = -1;
        for (int v = 0; v < vertices; v++)
        {
            if (!inMST[v] && key[v] < minKey)
            {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Add the picked vertex to the MST
        inMST[minIndex] = true;

        // Update key value and parent index for adjacent vertices
        struct Edge *edge = graph->adjacencylist[minIndex];
        while (edge != NULL)
        {
            int destination = edge->destination;
            if (!inMST[destination] && edge->weight < key[destination])
            {
                resultSet[destination]->parent = minIndex;
                resultSet[destination]->weight = edge->weight;
                key[destination] = edge->weight;
            }
            edge = edge->next;
        }
    }

    // Print the MST
    display(resultSet, vertices);
}

void addEdge(struct Graph *graph, int source, int destination, int weight)
{
    struct Edge *edge = createEdge(source, destination, weight);
    edge->next = graph->adjacencylist[source];
    graph->adjacencylist[source] = edge;

    edge = createEdge(destination, source, weight);
    edge->next = graph->adjacencylist[destination];
    graph->adjacencylist[destination] = edge;
}

int main()
{
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph *graph = createGraph(vertices);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++)
    {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(graph, source, destination, weight);
    }

    primMST(graph);

    return 0;
}