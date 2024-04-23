#include <stdio.h>
#include <stdlib.h>


struct Edge 
{
    int src, dest, weight;
};

struct Subset 
{
    int parent;
    int rank;
};


struct Graph 
{
    int numVertices, numEdges;
    struct Edge* edges;
};


struct Graph* createGraph(int numVertices, int numEdges) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph == NULL) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->numEdges = numEdges;

    graph->edges = (struct Edge*)malloc(numEdges * sizeof(struct Edge));
    if (graph->edges == NULL) 
    {
        printf("Memory allocation failed!\n");
        free(graph);
        exit(1);
    }

    return graph;
}

int find(struct Subset subsets[], int i) 
{
    if (subsets[i].parent != i) 
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) 
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) 
    {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) 
    {
        subsets[yroot].parent = xroot;
    } else 
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) 
{
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}


void KruskalMST(struct Graph* graph) 
{
    int numVertices = graph->numVertices;
    struct Edge result[numVertices]; // Stores the MST
    int e = 0; // Index for result[] array
    int i = 0; // Index for sorted edges array

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edges, graph->numEdges, sizeof(struct Edge), compareEdges);

    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(numVertices * sizeof(struct Subset));

    // Create numVertices subsets with single elements
    for (int v = 0; v < numVertices; ++v) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 2: Process all edges in sorted order
    while (e < numVertices - 1 && i < graph->numEdges) 
    {
       
        struct Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        
        if (x != y) 
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }


    printf("Edges of MST:\n");
    int totalWeight = 0;
    for (i = 0; i < e; ++i) 
    {
        printf("%d -- %d  weight: %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

int main() 
{
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    struct Graph* graph = createGraph(numVertices, numEdges);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) 
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edges[i].src = src;
        graph->edges[i].dest = dest;
        graph->edges[i].weight = weight;
    }

    KruskalMST(graph);

    return 0;
}