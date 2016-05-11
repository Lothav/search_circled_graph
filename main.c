#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int count = 0;

typedef struct bridge_st{
    int to, counted;
}Bridge;

typedef struct city_sy{
    Bridge * bridges;
    int count_br;
    int visited;
}City;

void push(int *stack,int item,int *top){
    (*top)++;
    stack[*top] = item;
}

void mark(City* cities, int *ant, int top, int city, int root){

    int i;

    for(i = 0; i < cities[city].count_br; i++){
        if(cities[city].bridges[i].to == ant[(top)]){
            if(!cities[city].bridges[i].counted){
                cities[city].bridges[i].counted = true;
                count++;
                break;
            }
        }
    }

    for(i = 0; i < cities[ant[(top)]].count_br; i++){
        if(cities[ant[(top)]].bridges[i].to == city){
            if(!cities[ant[(top)]].bridges[i].counted){
                cities[ant[(top)]].bridges[i].counted = true;
                break;
            }
        }
    }

    if(ant[top] != root) mark(cities,ant,top-1,ant[top], root);

}

void search(City* cities, int city, int depth, int* ant, int* top, int last){

    int i;
    if(cities[city].visited && depth > 3){
        /// VISITADO
        mark(cities, ant, *top, city,city);

    }else{

        push(ant,city,top);

        cities[city].visited = true;
        for(i = 0; i < cities[city].count_br; i++){
            if(cities,cities[city].bridges[i].to != last){
                search(cities,cities[city].bridges[i].to, depth+1, ant, top, city);
            }
        }
    }
}

int main(){

    int x, y;
    int C, B;
    int i, j;
    char str[100];
    int top = -1, *ant;



    City *cities;

    while(!feof(stdin)){
        fgets(str, sizeof(str), stdin);
        sscanf(str," %d %d", &C, &B);
        count = 0;

        cities = (City *) malloc(sizeof(City) * (C+1));
        ant = (int *) malloc(sizeof(int)*4);

        for(i = 1; i <= C; i++){
            cities[i].bridges = (Bridge *) malloc(sizeof(Bridge) * (B+1));
            cities[i].count_br = 0;
        }

        for(i = 0; i < B; i++){
            fgets(str, sizeof(str), stdin);
            sscanf(str," %d %d", &x, &y);

            cities[x].bridges[cities[x].count_br].to = y;
            cities[y].bridges[cities[y].count_br].to = x;

            cities[x].bridges[cities[x].count_br].counted = false;
            cities[y].bridges[cities[y].count_br].counted = false;

            cities[y].count_br++;
            cities[x].count_br++;
        }
        search(cities, 1, 1, ant, &top, 1);

        printf("%d\n", B - count);
    }

    return (EXIT_SUCCESS);
}
/**


8 9
1 2
1 5
1 7
7 3
7 4
3 4
4 8
4 6
8 6


 */