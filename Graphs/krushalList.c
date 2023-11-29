#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge *edges;
};

int *parent, *rank;

int find(int i)
{
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void uni(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void kruskal(struct Graph *graph)
{
    int ne = 0; // Number of edges included in the MST
    int i = 0;  // Index for sorted edges

    printf("The edges of Minimum Cost Spanning Tree are\n");

    while (ne < graph->V - 1)
    {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int w = graph->edges[i].weight;

        int setU = find(u);
        int setV = find(v);

        if (setU != setV)
        {
            printf("%d edge (%d,%d) = %d\n", ne + 1, u, v, w);
            ne++;
            uni(setU, setV);
        }

        i++;
    }
}

int compareEdges(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge *)malloc(E * sizeof(struct Edge));
    return graph;
}

int main()
{
    printf("-----Kruskal's algorithm-----\n");

    int V, E;
    printf("Enter the no. of vertices: ");
    scanf("%d", &V);
    printf("Enter the no. of edges: ");
    scanf("%d", &E);

    struct Graph *graph = createGraph(V, E);

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    parent = (int *)malloc((V + 1) * sizeof(int));
    rank = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    kruskal(graph);

    free(parent);
    free(rank);
    free(graph->edges);
    free(graph);

    getch();
    return 0;
}
