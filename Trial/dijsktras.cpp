#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#define MAX_VERTICES 100

struct Node
{
    int vertex;
    int weight;
    Node *next;
};

struct List
{
    Node *head;
};

struct Graph
{
    int vertices;
    List *array;
};

Node *createNode(int vertex, int weight)
{
    Node *newNode = new Node();
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = nullptr;
    return newNode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = new Graph();
    graph->vertices = vertices;
    graph->array = new List[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        graph->array[i].head = nullptr;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight)
{
    Node *newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

int minDistance(int dist[], bool visited[], int vertices)
{
    int min = numeric_limits<int>::max(), minIndex;
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
        cout << j << " ";
        return;
    }
    printPath(parent, parent[j]);
    cout << j << " ";
}

void printSolution(int dist[], int parent[], int src, int vertices)
{
    cout << "Vertex\t Distance\tPath\n";
    for (int i = 0; i < vertices; ++i)
    {
        if (i != src)
        {
            cout << src << " -> " << i << "\t " << dist[i] << "\t\t" << src << " ";
            printPath(parent, i);
            cout << endl;
        }
    }
}

void dijkstra(Graph *graph, int src)
{
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = numeric_limits<int>::max();
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;
    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minDistance(dist, visited, vertices);
        visited[u] = true;
        Node *temp = graph->array[u].head;
        while (temp != nullptr)
        {
            int v = temp->vertex;
            int weight = temp->weight;
            if (!visited[v] && dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    printSolution(dist, parent, src, vertices);
}

int main()
{
    int vertices, edges, src, dest, weight;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;
    Graph *graph = createGraph(vertices);
    cout << "Enter the number of edges: ";
    cin >> edges;
    for (int i = 0; i < edges; ++i)
    {
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> src >> dest >> weight;
        addEdge(graph, src, dest, weight);
    }
    cout << "Enter the source vertex: ";
    cin >> src;
    dijkstra(graph, src);
    delete[] graph->array;
    delete graph;
    return 0;
}
