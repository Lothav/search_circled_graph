// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Number of vertices in the graph
#define bool int
#define true 1
#define false 0

int minDistance(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int **graph, int src, int n) {
    int dist[n];

    bool sptSet[n];

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < n-1; count++) {

        int u = minDistance(dist, sptSet, n);

        sptSet[u] = true;

        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for (int i = 0; i < n; i++) printf("%d \t\t %d\n", i, dist[i]);
}

int main(int* argc, char* argv[]) {

    int size_x, size_y, **graph;
    int i, j;
    FILE *map;

    map = fopen(argv[1], "r");

    fscanf(map, "%d %d", &size_x, &size_y);

    graph = (int **) malloc( sizeof(int *) * size_x );
    for(i = 0; i <  size_x; i++){
        graph[i] = (int *) malloc( sizeof(int) * size_y );
    }

    graph[9][9] = 1;

    for(i = 0; i < size_x; i++){
        for(j = 0; j < size_y; j++){
            fscanf(map, "%d", &graph[i][j]);
        }
    }

    dijkstra(graph, 0, size_x);

    return 0;
}