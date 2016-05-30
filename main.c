// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Number of vertices in the graph
#define bool int
#define true 1
#define false 0

#define pos_center 1

#define pos_edge_top 2
#define pos_edge_right 3
#define pos_edge_left 4
#define pos_edge_bottom 5

#define pos_corner_right_top 6
#define pos_corner_left_bottom 7

typedef struct city_st{
    int pos;
    int x;
    int y;
    int cost;
} City;

int minDistance(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index;

    min_index = 0;
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

int getPos(int x, int y, int max_x, int max_y){
    return ( x == 0 && y == max_y) ? pos_corner_left_bottom : (x == max_x && y == max_y) ? pos_corner_right_top :
           (x == 0) ? pos_edge_left : (y == 0) ? pos_edge_top : (x == max_x) ? pos_edge_right : (y == max_y) ? pos_edge_bottom :
           pos_center;
}

int getAdjMatCost(City *cit, int i, int j) {

    int sum_cost;
    if(cit[i].cost && cit[j].cost){

        sum_cost= (cit[i].cost + cit[j].cost);
        switch (cit[i].pos) {
            case pos_corner_right_top:
                return (cit[i].x == cit[j].x && cit[i].y - 1 == cit[j].y) ||
                       (cit[i].x - 1 == cit[j].x && cit[i].y == cit[j].y) ?
                       sum_cost : 0;
            case pos_corner_left_bottom:
                return (cit[i].x == cit[j].x && cit[i].y + 1 == cit[j].y) ||
                       (cit[i].x + 1 == cit[j].x && cit[i].y == cit[j].y) ?
                       sum_cost : 0;

            case pos_edge_left:
                return ((cit[i].x == cit[j].x && (cit[i].y + 1 == cit[j].y || cit[i].y - 1 == cit[j].y)) ||
                        cit[i].x + 1 == cit[j].x && cit[i].y == cit[j].y) ? sum_cost : 0;
            case pos_edge_top:
                return ((cit[i].y == cit[j].y && (cit[i].x + 1 == cit[j].x || cit[i].x - 1 == cit[j].x)) ||
                        cit[i].y + 1 == cit[j].y && cit[i].x == cit[j].x) ? sum_cost : 0;
            case pos_edge_right:
                return ((cit[i].x == cit[j].x && (cit[i].y + 1 == cit[j].y || cit[i].y - 1 == cit[j].y)) ||
                        cit[i].x - 1 == cit[j].x && cit[i].y == cit[j].y) ? sum_cost : 0;
            case pos_edge_bottom:
                return ((cit[i].y == cit[j].y && (cit[i].x + 1 == cit[j].x || cit[i].x - 1 == cit[j].x)) ||
                        cit[i].y + 1 == cit[j].y && cit[i].x == cit[j].x) ? sum_cost : 0;

            case pos_center:
                return ((cit[i].y == cit[j].y && (cit[i].x + 1 == cit[j].x || cit[i].x - 1 == cit[j].x)) ||
                        (cit[i].x == cit[j].x && (cit[i].y + 1 == cit[j].y || cit[i].y - 1 == cit[j].y))) ? sum_cost : 0;
            default:
                return 0;
        }
    }else return 0;
}

int main(int* argc, char* argv[]) {

    int size_x, size_y, size_adj_matrix;
    int **adj_matrix;
    int i, j, a;

    FILE *map;
    City *cit;

    map = fopen(argv[1], "r");
    fscanf(map, "%d %d", &size_x, &size_y);

    a = 0;
    cit = (City *) malloc(sizeof(City) * size_x * size_y);
    for(i = 0; i < size_y; i++)
        for(j = 0; j < size_x; j++){
            cit[a].x = j;
            cit[a].y = i;
            cit[a].pos = (i == 0 && j == 0) || (j == size_x && i == size_y) ? 0 : getPos(j, i, size_x, size_y);
            fscanf( map, "%d", &cit[a].cost );
            a++;
        }

    size_adj_matrix = size_x * size_y;
    adj_matrix = (int **) malloc( sizeof(int *) * size_adj_matrix );
    for(i = 0; i <  size_adj_matrix; i++)
        adj_matrix[i] = (int *) malloc( sizeof(int) * size_adj_matrix );

    for(i = 0; i < size_adj_matrix; i++)
        for(j = 0; j < size_adj_matrix; j++){
            adj_matrix[i][j] = adj_matrix[j][i] = i == j ? 0 : getAdjMatCost(cit, i, j);
        }

    for(i = 0; i < size_adj_matrix; i++) {
        for(j = 0; j < size_adj_matrix; j++)
            printf("%d     ",adj_matrix[i][j]);
            printf("\n");
    }

    dijkstra(adj_matrix, 0, size_adj_matrix);

    return 0;
}

