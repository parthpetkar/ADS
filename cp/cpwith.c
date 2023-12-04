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

struct HeapNode
{
    int vertex;
    int key;
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

struct MinHeap
{
    int capacity;
    int currentSize;
    struct HeapNode *mH[MAX_VERTICES + 1];
    int indexes[MAX_VERTICES];
};

bool isEmpty(struct MinHeap *minHeap)
{
    return minHeap->currentSize == 0;
}

struct Edge *createEdge(int source, int destination, int weight)
{
    struct Edge *edge = (struct Edge *)malloc(sizeof(struct Edge));
    edge->source = source;
    edge->destination = destination;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

struct HeapNode *createHeapNode(int vertex, int key)
{
    struct HeapNode *node = (struct HeapNode *)malloc(sizeof(struct HeapNode));
    node->vertex = vertex;
    node->key = key;
    return node;
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

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->currentSize = 0;
    minHeap->mH[0] = createHeapNode(-1, INT_MIN);
    for (int i = 0; i < capacity; i++)
    {
        minHeap->indexes[i] = -1;
    }
    return minHeap;
}

void display(struct MinHeap *minHeap)
{
    for (int i = 0; i <= minHeap->currentSize; i++)
    {
        printf(" %d   key   %d\n", minHeap->mH[i]->vertex, minHeap->mH[i]->key);
    }
    printf("________________________\n");
}

void swap(struct MinHeap *minHeap, int a, int b)
{
    struct HeapNode *temp = minHeap->mH[a];
    minHeap->mH[a] = minHeap->mH[b];
    minHeap->mH[b] = temp;
}

void bubbleUp(struct MinHeap *minHeap, int pos)
{
    int parentIdx = pos / 2;
    int currentIdx = pos;
    while (currentIdx > 0 && minHeap->mH[parentIdx]->key > minHeap->mH[currentIdx]->key)
    {
        struct HeapNode *currentNode = minHeap->mH[currentIdx];
        struct HeapNode *parentNode = minHeap->mH[parentIdx];
        minHeap->indexes[currentNode->vertex] = parentIdx;
        minHeap->indexes[parentNode->vertex] = currentIdx;
        swap(minHeap, currentIdx, parentIdx);
        currentIdx = parentIdx;
        parentIdx = parentIdx / 2;
    }
}

void insert(struct MinHeap *minHeap, struct HeapNode *x)
{
    minHeap->currentSize++;
    int idx = minHeap->currentSize;
    minHeap->mH[idx] = x;
    minHeap->indexes[x->vertex] = idx;
    bubbleUp(minHeap, idx);
}

void sinkDown(struct MinHeap *minHeap, int k)
{
    int smallest = k;
    int leftChildIdx = 2 * k;
    int rightChildIdx = 2 * k + 1;
    if (leftChildIdx < minHeap->currentSize && minHeap->mH[smallest]->key > minHeap->mH[leftChildIdx]->key)
    {
        smallest = leftChildIdx;
    }
    if (rightChildIdx < minHeap->currentSize && minHeap->mH[smallest]->key > minHeap->mH[rightChildIdx]->key)
    {
        smallest = rightChildIdx;
    }
    if (smallest != k)
    {
        struct HeapNode *smallestNode = minHeap->mH[smallest];
        struct HeapNode *kNode = minHeap->mH[k];
        minHeap->indexes[smallestNode->vertex] = k;
        minHeap->indexes[kNode->vertex] = smallest;
        swap(minHeap, k, smallest);
        sinkDown(minHeap, smallest);
    }
}

struct HeapNode *extractMin(struct MinHeap *minHeap)
{
    struct HeapNode *min = minHeap->mH[1];
    struct HeapNode *lastNode = minHeap->mH[minHeap->currentSize];
    minHeap->indexes[lastNode->vertex] = 1;
    minHeap->mH[1] = lastNode;
    minHeap->mH[minHeap->currentSize] = NULL;
    sinkDown(minHeap, 1);
    minHeap->currentSize--;
    return min;
}

void decreaseKey(struct MinHeap *minHeap, int newKey, int vertex)
{
    int index = minHeap->indexes[vertex];
    struct HeapNode *node = minHeap->mH[index];
    node->key = newKey;
    bubbleUp(minHeap, index);
}

void printMST(struct ResultSet *resultSet[], int vertices)
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
    bool inHeap[MAX_VERTICES] = {false};
    struct ResultSet *resultSet[MAX_VERTICES];
    int key[MAX_VERTICES];
    struct HeapNode *heapNodes[MAX_VERTICES];
    for (int i = 0; i < vertices; i++)
    {
        heapNodes[i] = createHeapNode(i, INT_MAX);
        resultSet[i] = createResultSet(-1, INT_MAX);
        inHeap[i] = true;
        key[i] = INT_MAX;
    }
    heapNodes[0]->key = 0;
    struct MinHeap *minHeap = createMinHeap(vertices);
    for (int i = 0; i < vertices; i++)
    {
        insert(minHeap, heapNodes[i]);
    }
    while (!isEmpty(minHeap))
    {
        struct HeapNode *extractedNode = extractMin(minHeap);
        int extractedVertex = extractedNode->vertex;
        inHeap[extractedVertex] = false;
        struct Edge *edge = graph->adjacencylist[extractedVertex];
        while (edge != NULL)
        {
            int destination = edge->destination;
            if (inHeap[destination])
            {
                int newKey = edge->weight;
                if (key[destination] > newKey)
                {
                    decreaseKey(minHeap, newKey, destination);
                    resultSet[destination]->parent = extractedVertex;
                    resultSet[destination]->weight = newKey;
                    key[destination] = newKey;
                }
            }
            edge = edge->next;
        }
    }
    printMST(resultSet, vertices);
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