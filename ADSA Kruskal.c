
#include <stdio.h>

#define MAX 100

struct Edge
{
    int src, dest, weight;
};

struct Edge edges[MAX];
int parent[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
        parent[rootY] = rootX;
}

void sortEdges(int e)
{
    int i, j;
    struct Edge temp;

    for (i = 0; i < e - 1; i++)
    {
        for (j = 0; j < e - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int v, e, i, count = 0, total = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &v);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    if (v < 1 || v > MAX || e < 0 || e > MAX)
    {
        printf("Invalid number of vertices or edges.\n");
        return 0;
    }

    printf("Enter source destination weight for each edge:\n");

    for (i = 0; i < e; i++)
    {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);

        if (edges[i].src < 0 || edges[i].src >= v ||
            edges[i].dest < 0 || edges[i].dest >= v)
        {
            printf("Invalid vertex number.\n");
            return 0;
        }
    }

    for (i = 0; i < v; i++)
        parent[i] = i;

    sortEdges(e);

    printf("\nEdges in Minimum Spanning Tree:\n");

    for (i = 0; i < e && count < v - 1; i++)
    {
        int u = edges[i].src;
        int w = edges[i].dest;

        if (find(u) != find(w))
        {
            unionSet(u, w);

            printf("%d - %d : Weight = %d\n",
                   u, w, edges[i].weight);

            total += edges[i].weight;
            count++;
        }
    }

    if (count != v - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printf("Total Minimum Cost = %d\n", total);

    return 0;
}

