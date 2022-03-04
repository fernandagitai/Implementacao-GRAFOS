#include "kruskal.h"

void print_help() {
    printf("\n------------Kruskal Algorithm------------\n\n\n");
    printf("The input needed to run the algorithm is:\n\n");
    printf(" -f <input_file_name>\n\n\n");
    printf("Others possible arguments are:\n\n");
    printf(" -o <output_file_name>\n");
    printf(" -s (solution in ascending order)\n");
    printf("\n------------------------------------------\n\n");
}

subset** subsets_init(int V) {
    subset** subsets = malloc(V * sizeof(subset *));

    for(int v = 1 ; v <= V ; ++v) {
        subsets[v] = malloc(sizeof(subset));
        subsets[v]->parent = v;
        subsets[v]->rank = 0;
    }

    return subsets;
}

void free_graph(graph* g){
    for(int i = 0 ; i < g->E ; i++) {
        free(g->edge[i]);
    }
    free(g->edge);
}

void free_subsets(subset** subsets, int V) {
	for(int v = 1; v <= V ; v++) {
		free(subsets[v]);
	}
	free(subsets);
}

int compare (const void *a, const void *b) {
    int *i = *(int **) a;
    int *j = *(int **) b;

    return i[2] - j[2];
}

int find(subset** subsets, int i) {
    if(subsets[i]->parent != i){
        subsets[i]->parent = find(subsets, subsets[i]->parent);
    }

    return subsets[i]->parent;
}

void do_union(subset** subsets, int root1, int root2) {
    if(subsets[root1]->rank < subsets[root2]->rank) {
        subsets[root1]->parent = root2;
    }
    else if(subsets[root1]->rank > subsets[root2]->rank) {
        subsets[root2]->parent = root1;
    }
    else {
        subsets[root2]->parent = root1;
        subsets[root1]->rank++;
    }
}

int kruskal(graph* g, int mst[g->E][3], int *mst_length) {
    int i, x, y, cost = 0, j = 0;

    subset** subsets = subsets_init(g->V);

    qsort(g->edge, g->E, sizeof(g->edge[0]), compare);

    for(i = 0 ; i < g->E ; i++) {
        x = find(subsets, g->edge[i][0]);
        y = find(subsets, g->edge[i][1]);

        if(x != y) {
            mst[j][0] = g->edge[i][0];
            mst[j][1] = g->edge[i][1];
            mst[j][2] = g->edge[i][2];

            cost += mst[j][2];
            j++;

            do_union(subsets, x, y);
        }
    }

    free_subsets(subsets, g->V);

    *mst_length = j;

    return cost;
}