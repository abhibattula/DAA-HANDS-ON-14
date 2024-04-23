#include <stdio.h>
#include <stdlib.h>


struct Node 
{
    int data;
    struct Node* next;
};


struct Graph 
{
    int numVertices;
    struct Node** adjLists;
    int* visited;
};


struct Node* createNode(int data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int numVertices) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; ++i) 
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) 
{
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}


void DFS(struct Graph* graph, int vertex) 
{
    // Mark the current vertex as visited
    graph->visited[vertex] = 1;
    printf("%d ", vertex);


    struct Node* temp = graph->adjLists[vertex];
    while (temp != NULL) 
    {
        int adjVertex = temp->data;
        if (!graph->visited[adjVertex]) 
        {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

int main() 
{
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < numEdges; ++i) 
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int sourceVertex;
    printf("Enter the source vertex for DFS: ");
    scanf("%d", &sourceVertex);

    printf("Depth-First Traversal starting from vertex %d: ", sourceVertex);
    DFS(graph, sourceVertex);

    return 0;
}
