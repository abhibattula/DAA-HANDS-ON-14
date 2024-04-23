#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'numVertices' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Function to perform topological sort
void topologicalSortUtil(struct Graph* graph, int v, int visited[], struct Node** stack) {
    visited[v] = 1;

    struct Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            topologicalSortUtil(graph, adjVertex, visited, stack);
        }
        temp = temp->next;
    }

    // Push the vertex onto the stack after all its adjacent vertices have been visited
    struct Node* newNode = createNode(v);
    newNode->next = *stack;
    *stack = newNode;
}

// Function to perform topological sort
void topologicalSort(struct Graph* graph) {
    int visited[graph->numVertices];
    struct Node* stack = NULL;

    // Mark all vertices as not visited
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    // Call the utility function to perform topological sort
    for (int i = 0; i < graph->numVertices; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, &stack);
        }
    }

    // Print the vertices in topological order by popping from the stack
    printf("Topological Sort: ");
    while (stack != NULL) {
        printf("%d ", stack->data);
        stack = stack->next;
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    topologicalSort(graph);

    return 0;
}
