#include <stdio.h>
#include <stdlib.h>
int source, V, E;
int visited_dfs[30], visited_bfs[30], A[30][30];

void DFS(int i)
{
    printf("%d", i + 1);
    visited_dfs[i] = 1;
    for (int j = 0; j < V; j++)
    {
        if (A[i][j] != 0 && visited_dfs != 1)
        {
            DFS(j);
        }
    }
}

int main()
{
    printf("Enter no.of Vertices: ");
    scanf("%d", &V);
    printf("Enter no.of Edges: ");
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
        visited_dfs[i] = visited_bfs[i] = 0;
    }

    for (int i = 0; i < E; i++)
    {
        int v1, v2;
        printf("Enter Edges: ");
        scanf("%d %d", &v1, &v2);
        A[v1 - 1][v2 - 1] = A[v2 - 1][v1 - 1] = 1;
    }
    printf("Enter Source: ");
    scanf("%d", &source);

    BFS(source - 1);
    DFS(source - 1);
}