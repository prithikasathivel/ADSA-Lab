
#include <stdio.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX];
int dist[MAX];
int heap[MAX * MAX];
int heapSize = 0;

/* Insert into min-heap */
void insertHeap(int value)
{
    int i = ++heapSize;

    while (i > 1 && value < heap[i / 2])
    {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = value;
}

/* Remove minimum element */
int deleteMin()
{
    int min = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (2 * i <= heapSize)
    {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            heap[child + 1] < heap[child])
            child++;

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = last;
    return min;
}

/* Dijkstra's algorithm */
void dijkstra(int n, int source)
{
    int i, u, v;

    for (i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[source] = 0;
    heapSize = 0;
    insertHeap(source);

    while (heapSize > 0)
    {
        u = deleteMin();

        for (v = 0; v < n; v++)
        {
            if (graph[u][v] > 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                insertHeap(v);
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n",
           source);

    for (i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

int main()
{
    int n, i, j, source;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix (0 = no edge):\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] < 0)
            {
                printf("Negative weights are not allowed.\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    if (source < 0 || source >= n)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(n, source);

    return 0;
}
