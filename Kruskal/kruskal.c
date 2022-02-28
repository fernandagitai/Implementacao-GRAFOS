#include "kruskal.h"

int find(subset subsets[], int i) {
    if(subsets[i].parent == i){
        return i;
    }

    return find(subsets, subsets[i].parent);
}

void do_union(subset subsets[], int v1, int v2) {
    int root1 = find(subsets, v1);
    int root2 = find(subsets, v2);

    if(subsets[root1].rank < subsets[root2].rank) {
        subsets[root1].parent = root2;
    }
    else if(subsets[root1].rank > subsets[root2].rank) {
        subsets[root2].parent = root1;
    }
    else {
        subsets[root2].parent = root1;
        subsets[root1].rank++;
    }
}

void kruskal(graph* g) {
    int V = g->V, j = 0, i = 0, x, y, cost;
    float mst[V - 1][3];

    subset* subsets = subsets_init(V);

    qsort(g->edge, g->E, sizeof(g->edge[0]), compare);

    while(j < V - 1) {
        int* edge = g->edge[i++];

        x = find(subsets, edge[0]);
        y = find(subsets, edge[1]);

        if(x != y) {
            mst[j][0] = edge[0];
            mst[j][1] = edge[1];
            mst[j][2] = edge[2];
            j++;
            do_union(subsets, x, y);
        }
    }

    cost = 0;

    for(i = 0 ; i < j ; ++i) {
        //printf("%d -- %d == %d\n", (int) mst[i][0], (int) mst[i][1], (int) mst[i][2]);
        cost += mst[i][2];
    }

    //printf("Cost: %d", cost);

    return;
}