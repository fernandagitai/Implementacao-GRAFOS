#ifndef KRUSKAL_H_
#define KRUSKAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_NODES 30


typedef struct {
    int V, E;
    int edge[MAX_NODES][3];
} graph;


typedef struct {
    int parent, rank;
} subset;


subset* create_subsets(int V) {
    return (subset*)malloc(V * sizeof(subset));
}


subset* subsets_init(int V) {
    subset* subsets = create_subsets(V);

    for(int v = 0 ; v < V ; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    return subsets;
}


int compare (const void *a, const void *b) {
    int *i = (int *) a;
    int *j = (int *) b;

    return i[2] > j[2];
}


int find(subset subsets[], int i);


void do_union(subset subsets[], int v1, int v2);


int kruskal(graph* g);


#endif