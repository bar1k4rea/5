#ifndef GRAPH_H
#define GRAPH_H

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTEX 10

typedef struct Vertex {
    int x;
    int y;
    int name;
    int weight;
    struct Vertex* next;
} Vertex;

// Основные функции.
void exitGraph(Vertex *graph, int amt);
Vertex* addVertex(Vertex *graph, int *amt);
Vertex* deleteVertex(Vertex *graph, int *amt);
void addEdge(Vertex *graph, int amt);
void deleteEdge(Vertex *graph, int amt);
void DFS(Vertex *graph, int amt);
void Dijkstra(Vertex *graph, int amt);
void topologicalSorting(Vertex *graph, int amt);
void createGraph(Vertex *graph);
Vertex* loadingGraph(Vertex *graph, int *amt);
void showGraph(Vertex *graph, int amt);
void timingFunction(Vertex *graph);

// Дополнительные функции.
int getInt(int *integer);
int returnWeight(int x1, int y1, int x2, int y2);
void deleteDefiniteEdge(Vertex *graph, int amt, int ind1, int name2);
void DeapthFirstSearch(Vertex *graph, int amt, int ind1, int ind2);
int findIndex(Vertex* graph, int amt, int name);
void checkDFS(Vertex *graph, int amt, int *colors, int ind1);
int findIndex(Vertex* graph, int amt, int name);

#endif //GRAPH_H

