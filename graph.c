#include "graph.h"

/* ОСНОВНЫЕ ФУНКЦИИ */
// 0. Выход.
void exitGraph(Vertex *graph, int amt) {
    int i;
    Vertex *cur;

    for (i = 0; i < amt; i++) {
        if (graph[i].next) {
            while (graph[i].next) {
                if (graph[i].next->next) {
                    cur = graph[i].next->next;
                    free(graph[i].next);
                    graph[i].next = cur;
                }
                else {
                    free(graph[i].next);
                    graph[i].next = NULL;
                }
            }
        }
    }
    free(graph);

    return;
}

// 1. Добавление вершины.
Vertex* addVertex(Vertex *graph, int *amt) {
    int x, y, name, i;

    printf("Enter the x coordinates ->");
    getInt(&x);
    printf("Enter the y coordinates ->");
    getInt(&y);
    printf("Enter the name of vertex ->");
    getInt(&name);
    for (i = 0; i < *amt; i++) {
        if (x == graph[i].x && y == graph[i].y) {
            printf("ERROR! The entered coordinates are alredy in the graph.\n");
            return graph;
        }
        if (name == graph[i].name) {
            printf("ERROR! The entered coordinates are alredy in the graph.\n");
            return graph;
        }
    }
    graph = (Vertex*)realloc(graph, (*amt + 1) * sizeof(Vertex));
    graph[*amt].x = x;
    graph[*amt].y = y;
    graph[*amt].name = name;
    graph[*amt].weight = 0;
    graph[*amt].next = NULL;
    *amt += 1;
    return graph;
}

// 2. Удаление вершины.
Vertex* deleteVertex(Vertex *graph, int *amt) {
    int name, ind, i, signal = 0;
    Vertex del, *cur;

    printf("Enter the name of vertex: ");
    getInt(&name);
    for (i = 0; i < *amt; i++) {
        if (name == graph[i].name) {
            ind = i;
            signal = 1;
            break;
        }
    }
    if (!signal) {
        printf("ERROR! The entered vertex isn't in the graph.\n");
        return graph;
    }
    del = graph[ind];
    graph[ind] = graph[*amt - 1];
    graph[*amt - 1] = del;
    if (graph[*amt - 1].next) {
        while (graph[*amt - 1].next) {
            if (graph[*amt - 1].next->next) {
                cur = graph[*amt - 1].next->next;
                free(graph[*amt - 1].next);
                graph[*amt - 1].next = cur;
            }
            else {
                free(graph[*amt - 1].next);
                graph[*amt - 1].next = NULL;
            }
        }
    }
    graph = (Vertex*)realloc(graph, (*amt - 1) * sizeof(Vertex));
    *amt -= 1;
    for (i = 0; i < *amt; i++)
        deleteDefiniteEdge(graph, *amt, i, name);
    return graph;
}

// 3. Добавление ребра.
void addEdge(Vertex *graph, int amt) {
    int name1, name2, ind1, ind2, i, signal = 0;
    Vertex *cur, *ptr, *head;

    printf("Enter the first graph: ");
    getInt(&name1);
    printf("Enter the second graph: ");
    getInt(&name2);
    for (i = 0; i < amt; i++) {
        if (name1 == graph[i].name) {
            ind1 = i;
            signal += 1;
        }
        if (name2 == graph[i].name) {
            ind2 = i;
            signal += 1;
        }
    }
    if (signal != 2) {
        printf("ERROR! The entered vertex(es) isn't (aren't) in the graph.\n");
        return;
    }
    head = graph[ind1].next;
    while (head) {
        if (name2 == head->name) {
            printf("ERROR! The entered edge is already in the graph.\n");
            return;
        }
        head = head->next;
    }
    cur = (Vertex*)calloc(1, sizeof(Vertex));
    cur->x = graph[ind1].x;
    cur->y = graph[ind2].y;
    cur->name = graph[ind2].name;
    cur->weight = returnWeight(graph[ind1].x, graph[ind2].x, graph[ind1].y, graph[ind2].y);
    head = graph[ind1].next;
    graph[ind1].next = cur;
    cur->next = head;
    return;
}

// 4. Удаление ребра.
void deleteEdge(Vertex *graph, int amt) {
    int name1, name2, ind1, ind2, i, signal = 0;
    Vertex *head;

    printf("Enter the first graph: ");
    getInt(&name1);
    printf("Enter the second graph: ");
    getInt(&name2);
    for (i = 0; i < amt; i++) {
        if (name1 == graph[i].name) {
            ind1 = i;
            signal += 1;
        }
        if (name2 == graph[i].name) {
            ind2 = i;
            signal += 1;
        }
    }
    if (signal != 2) {
        printf("ERROR! The entered vertex(es) isn't (aren't) in the graph.\n");
        return;
    }
    head = graph[ind1].next;
    while (head) {
        if (name2 == head->name)
            break;
        head = head->next;
    }
    if (head == NULL) {
        printf("ERROR! The entered edge isn't in the graph.\n");
        return;
    }
    deleteDefiniteEdge(graph, amt, ind1, name2);
    return;
}

// 5. Поиск в глубину.
void DFS(Vertex *graph, int amt) {
    int ind1, ind2, name1, name2, signal = 0, i;

    printf("Enter the first graph: ");
    getInt(&name1);
    printf("Enter the second graph: ");
    getInt(&name2);
    for (i = 0; i < amt; i++) {
        if (name1 == graph[i].name) {
            ind1 = i;
            signal += 1;
        }
        if (name2 == graph[i].name) {
            ind2 = i;
            signal += 1;
        }
    }
    if (signal != 2) {
        printf("ERROR! The entered vertex(es) isn't (aren't) in the graph.\n");
        return;
    }
    DeapthFirstSearch(graph, amt, ind1, ind2);
    return;
}

void DeapthFirstSearch(Vertex *graph, int amt, int ind1, int ind2) {
    int i;
    int colors[amt];
    for (i = 0; i < amt; i++)
        colors[i] = 0;
    checkDFS(graph, amt, colors, ind1);
    if (colors[ind2] == 2)
        printf("The vertex is reachable.\n");
    else
        printf("The vertex isn't reachable.\n");
    return;
}

void checkDFS(Vertex *graph, int amt, int *colors, int ind1) {
    int name, new;
    Vertex *ptr;

    colors[ind1] = 1;
    ptr = &graph[ind1];
    if (ptr->next) {
        ptr = ptr->next;
        while (ptr->next) {
            new = findIndex(graph, amt, ptr->name);
            if (colors[new] == 0)
                checkDFS(graph, amt, colors, new);
            ptr = ptr->next;
        }
        new = findIndex(graph, amt, ptr->name);
        if (colors[new] == 0)
            checkDFS(graph, amt, colors, new);
    }
    colors[ind1] = 2;
    return;
}

int findIndex(Vertex* graph, int amt, int name) {
    int i;

    for (i = 0; i < amt; i++) {
        if (name == graph[i].name)
            return i;
    }
}

// 6. Алгоритм Дейкстры.
void Dijkstra(Vertex *graph, int amt) {
    printf("6\n");
    return;
}

// 7. Топологическая сортировка.
void topologicalSorting(Vertex *graph, int amt) {
    printf("7\n");
    return;
}

// 8. Создание графа.
void createGraph(Vertex *graph) {
    int x, y, i, j, amt, coin, signal, counter;
    Vertex *head, *cur;

    printf("Enter the number of vertex ->");
    getInt(&amt);
    if (amt < 1) {
        printf("ERROR! The number of vertex must be bigger than 0.\n");
        return;
    }
    if (amt > MAX_VERTEX * MAX_VERTEX) {
        printf("ERROR! The number of vertex must be smaller than %d.\n", MAX_VERTEX * MAX_VERTEX + 1);
        return;
    }
    graph = (Vertex*)calloc(amt, sizeof(Vertex));
    for (i = 0; i < amt; i++) {
        do {
            x = 1 + rand() % MAX_VERTEX;
            y = 1 + rand() % MAX_VERTEX;
            signal = 0;
            for (j = 0; j < i; j++) {
                if (x == graph[j].x && y == graph[j].y) {
                    signal = 1;
                    break;
                }
            }
        } while (signal);
        graph[i].x = x;
        graph[i].y = y;
        graph[i].name = i;
    }
    for (i = 0; i < amt; i++) {
        counter = 0;
        x = graph[i].x;
        y = graph[i].y;
        head = graph[i].next;
        for (j = 0; j < amt; j++) {
            coin = rand() % 2;
            if (coin) {
                counter++;
                head = graph[i].next;
                cur = (Vertex*)calloc(1, sizeof(Vertex));
                cur->x = graph[j].x;
                cur->y = graph[j].y;
                cur->name = graph[j].name;
                cur->weight = returnWeight(x, graph[j].x, y, graph[j].y);
                graph[i].next = cur;
                cur->next = head;
                head = cur;
            }
        }
        graph[i].weight = counter;
    }
    FILE *fd = fopen("GRAPH.txt", "w");
    fprintf(fd, "%d\n", amt);
    for (i = 0; i < amt; i++) {
        fprintf(fd, "%d %d %d ", graph[i].x, graph[i].y, graph[i].name);
    }
    fprintf(fd, "\n");
    for (i = 0; i < amt; i++) {
        fprintf(fd, "%d\t\t", graph[i].weight);
        cur = graph[i].next;
        while (cur) {
            fprintf(fd, "%d %d %d %d\t", cur->x, cur->y, cur->name, cur->weight);
            cur = cur->next;
        }
        fprintf(fd, "\n");
    }
    fclose(fd);

    for (i = 0; i < amt; i++) {
        if (graph[i].next) {
            while (graph[i].next) {
                if (graph[i].next->next) {
                    cur = graph[i].next->next;
                    free(graph[i].next);
                    graph[i].next = cur;
                }
                else {
                    free(graph[i].next);
                    graph[i].next = NULL;
                }
            }
        }
    }
    free(graph);
    return;
}

// 9. Загрузка графа из файла.
Vertex* loadingGraph(Vertex *graph, int *amt) {
    FILE *fd = fopen("GRAPH.txt", "r");
    int x, y, name, weight, i, j;
    Vertex *head, *cur;

    fscanf(fd, "%d", &(*amt));
    graph = (Vertex*)calloc(*amt, sizeof(Vertex));
    for (i = 0; i < *amt; i++)
        fscanf(fd, "%d %d %d", &(graph[i].x), &(graph[i].y), &(graph[i].name));
    for (i = 0; i < *amt; i++) {
        fscanf(fd, "%d", &(graph[i].weight));
        head = graph[i].next;
        for (j = 0; j < graph[i].weight; j++) {
            cur = (Vertex*)calloc(1, sizeof(Vertex));
            fscanf(fd, "%d %d %d %d", &(cur->x), &(cur->y), &(cur->name), &(cur->weight));
            graph[i].next = cur;
            cur->next = head;
            head = cur;
        }
    }
    fclose(fd);
    return graph;
}

// 10. Вывод графа.
void showGraph(Vertex *graph, int amt) {
    int i;
    Vertex *cur;

    for (i = 0; i < amt; i++) {
        printf("\nElement #%d\n", graph[i].name);
        printf("x -> %d\n", graph[i].x);
        printf("y -> %d\n", graph[i].y);

        cur = graph[i].next;
        printf("Adjacent Vertex: ");
        while (cur) {
            printf("%d ", cur->name);
            cur = cur->next;
        }
        printf("\n");
    }
    printf("\n");
}

// 11. Таймировние и профилирование.
void timingFunction(Vertex *graph) {
    printf("11\n");
    return;
}


/* ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ */
// Ввод целого числа.
int getInt(int *integer) {
    int n;
    do {
        n = scanf("%d", integer);
        if (n < 0)
            return 0;
        if (n == 0) {
            printf("ERROR! Enter the natural number ->");
            scanf("%*[^\n]");
        }
    } while (n == 0);
    return 1;
}

// Возврат веса ребра.
int returnWeight(int x1, int y1, int x2, int y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

// Удаление определённого ребра.
void deleteDefiniteEdge(Vertex *graph, int amt, int ind1, int name2) {
    Vertex *ptr, *cur;

    ptr = &graph[ind1];
    while (ptr->next) {
        if (ptr->next->name == name2) {
            if (ptr->next->next) {
                cur = ptr->next->next;
                free(ptr->next);
                ptr->next = cur;
                return;
            }
            else {
                free(ptr->next);
                ptr->next = NULL;
                return;
            }
        }
        ptr = ptr->next;
    }
    return;
}

