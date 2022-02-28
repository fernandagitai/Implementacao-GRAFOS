#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int V;
    int E;
    int adj_list[MAX_NODES][MAX_NODES];
} graph;

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x);

int dequeue();

int bfs(graph g, int residual[MAX_NODES][MAX_NODES], int start, int end, int parent[]);

int ford_fulkerson(graph g, int start, int end);