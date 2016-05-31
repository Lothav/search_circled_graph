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
#define pos_corner_left_top 8
#define pos_corner_right_bottom 9

typedef struct {
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

void dijkstra(int **graph, int n, int src, int to) {
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
                dist[v] = dist[u] + (graph[u][v] > 1 ? graph[u][v] : 0);
    }

    printf("%d\n", dist[to] == INT_MAX ? -1 : dist[to]);
}

int getPos(int x, int y, int max_x, int max_y){
    return ( x == 0 && y == max_y) ? pos_corner_left_bottom : (x == max_x && y == 0) ? pos_corner_right_top : (x == 0 && y == 0) ? pos_corner_left_top : (x == max_x && y == max_y) ? pos_corner_right_bottom :
           (x == 0) ? pos_edge_left : (y == 0) ? pos_edge_top : (x == max_x) ? pos_edge_right : (y == max_y) ? pos_edge_bottom : pos_center;
}

int getAdjMatCost(City *cit, int i, int j, int rest_x, int rest_y, int offsetx) {

    int b, a, t, sig_x, sig_y, block_a, block_b, index, last_index;
    int cost_x, cost_y;

    if(cit[i].cost == -1 && cit[j].cost == -1) return 1;
    if(!cit[i].cost || !cit[j].cost ) return 0;
    for(t = 1; t <= 4; t++) {

        sig_x = t > 2 ? -1 : 1;
        sig_y = t % 2 == 0 ? -1 : 1;

        if(sig_x == 1)
            if(cit[i].pos == pos_edge_right || cit[i].pos == pos_corner_right_top || cit[i].pos == pos_corner_right_bottom)
                continue;
        if(sig_x == -1)
            if(cit[i].pos == pos_edge_left || cit[i].pos == pos_corner_left_top || cit[i].pos == pos_corner_left_bottom)
                continue;

        if(sig_y == 1)
            if(cit[i].pos == pos_edge_bottom || cit[i].pos == pos_corner_right_bottom || cit[i].pos == pos_corner_left_bottom)
                continue;
        if(sig_y == -1)
            if(cit[i].pos == pos_edge_top || cit[i].pos == pos_corner_left_top || cit[i].pos == pos_corner_right_top)
                continue;

        if( (i + (rest_x * sig_x) + (sig_y*offsetx*rest_y)) == j ){

            cost_x = block_a = block_b = index = false;
            last_index = sig_x + i;

            for(a = 1; a <= rest_x; a++){

                index = sig_x*a + i;

                if(cit[index].pos == pos_edge_left) block_a = true;
                if(cit[index].pos == pos_edge_right) block_b = true;

                if(!cit[index].cost || cit[index].pos == pos_edge_left && block_b || cit[index].pos == pos_edge_right && block_a){
                    cost_x = 0;
                    break;
                }

                cost_x += (cit[index].cost + cit[last_index].cost);
                last_index = index;
            }

            block_a = block_b = false;
            if(cost_x){
                for(b = 1; b <= rest_y; b++){

                    index += sig_y*offsetx;

                    if(cit[index].pos == pos_edge_top) block_a = true;
                    if(cit[index].pos == pos_edge_bottom) block_b = true;

                    if(!cit[index].cost || cit[index].pos == pos_edge_top && block_b || cit[index].pos == pos_edge_bottom && block_a){
                        cost_x = 0;
                        break;
                    }

                    cost_x += (cit[index].cost + cit[last_index].cost);
                    last_index = index;
                }
            }

            // cost y
            block_a = block_b = cost_y = index = false;
            last_index = i + (sig_y*offsetx);
            for(a = 1; a <= rest_y; a++){

                index = i + (sig_y*a*offsetx);
                if(cit[index].pos == pos_edge_top) block_a = true;
                if(cit[index].pos == pos_edge_bottom) block_b = true;

                if(!cit[index].cost || cit[index].pos == pos_edge_top && block_b || cit[index].pos == pos_edge_bottom && block_a){
                    cost_y = 0;
                    break;
                }

                cost_y += (cit[index].cost + cit[last_index].cost);
                last_index = index;
            }
            block_a = false;
            block_b = false;

            if(cost_y){
                for(b = 1; b <= rest_x; b++) {

                    index += sig_x;
                    if(cit[index].pos == pos_edge_left) block_a = true;
                    if(cit[index].pos == pos_edge_right) block_b = true;

                    if(!cit[index].pos || cit[index].pos == pos_edge_top && block_b || cit[index].pos == pos_edge_bottom && block_a){
                        cost_y = 0;
                        break;
                    }

                    cost_y += (cit[index].cost + cit[last_index].cost);
                    last_index = index;
                }
            }
            return !cost_x ? cost_y : !cost_y ? cost_x : (cost_x > cost_y) ? cost_y : cost_x;
        }
    }
    return 0;
}

int main(int* argc, char* argv[]) {

    int size_x, size_y, size_adj_matrix;
    int **adj_matrix;
    int i, j, a, from, to;

    FILE *map;
    City *cit;

    map = fopen(argv[1], "r");
    fscanf(map, "%d %d", &size_x, &size_y);

    from = to = a = 0;

    cit = (City *) malloc(sizeof(City) * size_x * size_y);
    for(i = 0; i < size_y; i++)
        for(j = 0; j < size_x; j++){
            cit[a].x = j;
            cit[a].y = i;
            cit[a].pos = (i == 0 && j == 0) || (j == size_x && i == size_y) ? 0 : getPos(j, i, size_x-1, size_y-1);
            fscanf( map, "%d", &cit[a].cost );
            if(cit[a].x == atoi(argv[2]) && cit[a].y == atoi(argv[3])) from = a;
            if(cit[a].x == atoi(argv[4]) && cit[a].y == atoi(argv[5])) to = a;
            a++;
        }

    size_adj_matrix = size_x * size_y;
    adj_matrix = (int **) malloc( sizeof(int *) * size_adj_matrix );
    for(i = 0; i <  size_adj_matrix; i++)
        adj_matrix[i] = (int *) malloc( sizeof(int) * size_adj_matrix );

    for(i = 0; i < size_adj_matrix; i++)
        for(j = 0; j < size_adj_matrix; j++){
            adj_matrix[i][j] = adj_matrix[j][i] = i == j ? 0 : getAdjMatCost(cit, i, j, atoi(argv[6]), atoi(argv[7]), size_x);
        }

    for(i = 0; i < size_adj_matrix; i++) {
        for(j = 0; j < size_adj_matrix; j++)
            printf("%d\t",adj_matrix[i][j]);
        printf("\t %d \n", i);
    }
    printf("\n");
    for(i = 0; i < size_adj_matrix; i++) {
        printf("%d\t",i);
    }
    printf("\n\n");
    dijkstra(adj_matrix, size_adj_matrix, from, to);

    return 0;
}

//     0 1 4 3 2 1

/*

 0   1  2  3   4   5

198    0   0  35  20   14   5
|232|  0   0  14  21   13   11
147    72 61  66  33   16   17
87    78  81 141 |130| 40   23

 *
 *
 * */