#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NODES 100


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


typedef struct {
    int V, E;
    int adj_list[MAX_NODES][MAX_NODES];
} graph;


void print_help();


int dfs(int v, int residual[][v], int start, int end, int visited[], int path[]);


int ford_fulkerson(graph g, int start, int end, int residual[][g.V]);