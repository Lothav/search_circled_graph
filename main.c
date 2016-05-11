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
    int come_from;
}City;

void mark(City* cities, int ant[], int depth){

    int i, city;

    city = ant[depth-1];

    while(true){
        for(i = 0; i < cities[ant[depth-1]].count_br; i++){
            if(cities[ant[depth-1]].bridges[i].to == ant[depth-2] && !cities[ant[depth-1]].bridges[i].counted ){
                cities[ant[depth-1]].bridges[i].counted = true;
                count++;
                break;
            }
        }

        for(i = 0; i < cities[ant[depth-2]].count_br; i++){
            if(cities[ant[depth-2]].bridges[i].to == ant[depth-1] && !cities[ant[depth-2]].bridges[i].counted){
                cities[ant[depth-2]].bridges[i].counted = true;
                break;
            }
        }
        if(ant[depth-2] == city) break;
        depth--;
    }
}

void search(City* cities, int city, int depth, int* ant){

    int i, to;
    int this_ant[depth];

    for(i = 0; i < depth-1; i++) this_ant[i] = ant[i];
    this_ant[depth-1] = city;

    if(cities[city].visited){
        mark(cities, this_ant, depth);
    }else{
        cities[city].visited = true;
        for(i = 0; i < cities[city].count_br; i++){
            to = cities[city].bridges[i].to;
            if(to != cities[city].come_from){
                cities[to].come_from = city;
                search(cities,cities[city].bridges[i].to, depth+1, this_ant);
            }
        }
    }
}

int main(){

    int x, y;
    int C, B;
    int i;
    char str[10000];
    int *ant;

    City *cities;

    while(!feof(stdin)){
        fgets(str, sizeof(str), stdin);
        sscanf(str," %d %d", &C, &B);
        count = 0;

        cities = (City *) malloc(sizeof(City) * (C+1));
        ant = (int *) malloc(sizeof(int)*B*20);

        for(i = 1; i <= C; i++){
            cities[i].bridges = (Bridge *) malloc(sizeof(Bridge) * (B+1));
            cities[i].count_br = 0;
            cities[i].come_from = 0;
        }

        for(i = 0; i < B; i++){
            fgets(str, sizeof(str), stdin);
            sscanf(str," %d %d", &x, &y);
            cities[x].bridges[cities[x].count_br].to = y;
            cities[x].bridges[cities[x].count_br].counted = false;
            cities[x].count_br++;

            cities[y].bridges[cities[y].count_br].to = x;
            cities[y].bridges[cities[y].count_br].counted = false;
            cities[y].count_br++;
        }

        search(cities, 1, 1, ant);

        printf("%d\n", B - count);
    }
    return (EXIT_SUCCESS);
}
