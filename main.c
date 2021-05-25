#include "graph.h"

int main() {
    int command, amt = 0;
    Vertex *graph = NULL;
    srand(time(NULL));

    do {
        printf("0. Exit.\n");
        printf("1. Add Vertex.\n");
        printf("2. Delete Vertex.\n");
        printf("3. Add Edge.\n");
        printf("4. Delete Edge.\n");
        printf("5. Depth-First Search.\n");
        printf("6. Dijkstra.\n");
        printf("7. Topological Sorting.\n");
        printf("8. Create Graph.\n");
        printf("9. Loading Graph.\n");
        printf("10. Show Graph.\n");
        printf("11. Timing and Profiling.\n");
        printf("Enter the command ->");
        getInt(&command);
        switch(command) {
            case 0:
                exitGraph(graph, amt);
                break;
            case 1:
                graph = addVertex(graph, &amt);
                break;
            case 2:
                graph = deleteVertex(graph, &amt);
                break;
            case 3:
                addEdge(graph, amt);
                break;
            case 4:
                deleteEdge(graph, amt);
                break;
            case 5:
                DFS(graph, amt);
                break;
            case 6:
                Dijkstra(graph, amt);
                break;
            case 7:
                topologicalSorting(graph, amt);
                break;
            case 8:
                createGraph(graph);
                break;
            case 9:
                graph = loadingGraph(graph, &amt);
                break;
            case 10:
                showGraph(graph, amt);
                break;
            case 11:
                timingFunction(graph, amt);
                break;
            default:
                printf("ERROR! There is no such command.\n");
        }
    } while (command != 0);

    return 0;
}
