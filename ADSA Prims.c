
#include <stdio.h>
#include <limits.h>

#define MAX 20

int graph[MAX][MAX];
int key[MAX], parent[MAX], visited[MAX];
int heap[MAX * MAX], heapSize = 0;

void insertHeap(int v)
{
    int i = ++heapSize;

    while (i > 1 && key[heap[i / 2]] > key[v])
    {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = v;
}

int deleteMin()
{
    int min = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (2 * i <= heapSize)
    {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            key[heap[child + 1]] < key[heap[child]])
            child++;

        if (key[last] <= key[heap[child]])
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = last;
    return min;
}

void prim(int n)
{
    int i, u, v, total = 0, count = 0;

    for (i = 0; i < n; i++)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    key[0] = 0;
    insertHeap(0);

    while (heapSize > 0)
    {
        u = deleteMin();

        if (visited[u])
            continue;

        visited[u] = 1;
        count++;

        for (v = 0; v < n; v++)
        {
            if (graph[u][v] > 0 && !visited[v] &&
                graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
                insertHeap(v);
            }
        }
    }

    if (count != n)
    {
        printf("Graph is disconnected. MST does not exist.\n");
        return;
    }

    printf("\nEdges in Minimum Spanning Tree:\n");

    for (i = 1; i < n; i++)
    {
        printf("%d - %d : Weight = %d\n",
               parent[i], i, key[i]);
        total += key[i];
    }

    printf("Total Minimum Cost = %d\n", total);
}

int main()
{
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 0;
    }

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    prim(n);

    return 0;
}
