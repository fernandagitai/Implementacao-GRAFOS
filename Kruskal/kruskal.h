#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int V, E;
    int** edge;
} graph;


typedef struct {
    int parent, rank;
} subset;


void print_help();


void free_graph(graph* g);


void free_subsets(subset** subsets, int V);


subset** subsets_init(int V);


int find(subset** subsets, int i);


void do_union(subset** subsets, int v1, int v2);


int kruskal(graph* g, int mst[g->E][3], int *mst_length);