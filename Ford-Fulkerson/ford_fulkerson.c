#include "ford_fulkerson.h"

int dfs(int residual[MAX_NODES][MAX_NODES], int start, int end, int visited[], int path[], int v) {
    int i, j, current;

    printf("dfs");

    if (start == end) {
        return 1;
    }

    for(i = 1 ; i <= v ; i++) {
        for(j = 1 ; j <= v ; j++){
            printf("dfs resdiual %d %d %d\n", i, j, residual[i][j]);
        }
    }

    for(i = 1 ; i <= v ; i++) {
        current = residual[start][i];
        if(visited[i] == 0 && (current > 0 && current < INT_MAX)) {
            path[start] = i;
            visited[i] = 1;
            printf("visted");

            if(dfs(residual, i, end, visited, path, v) != 0) {
                visited[i] = 0;
                return 1;
            } else {
                visited[i] = 0;
                path[start] = -1;
            }
        }
    }

    for(int i = 1 ; i < v ; i++){
        printf("dfs: i -> %d visited -> %d path -> %d\n", i, visited[i], path[i]);
    }

    return 0;
}

int ford_fulkerson(graph g, int start, int end) {
    int u, v, max_flow = 0, i, j, path[g.V], visited[g.V];

    for(i = 1 ; i <= g.V ; i++) {
        path[i] = 0;
        visited[i] = 0;
    }

    // for(i = 1 ; i <= g.V ; i++) {
    //     printf("i -> %d path[i] -> %d visited[i] -> %d\n", i, path[i], visited[i]);
    // }

    visited[start] = 1;

    int residual[g.V][g.V];

    for(i = 1 ; i <= g.V ; i++) {
        for(j = 1 ; j <= g.V ; j++){
            residual[i][j] = g.adj_list[i][j];
        }
    }

    // for(i = 1 ; i <= g.V ; i++) {
    //     for(j = 1 ; j <= g.V ; j++){
    //         if(residual[i][j] != 0)
    //             printf("%d %d %d\n", i, j, residual[i][j]);
    //     }
    // }

    int x = dfs(residual, start, end, visited, path, g.V);

    printf("x -> %d\n", x);
    for(i = 1 ; i <= g.V ; i++) {
        printf("%d %d %d\n", i, visited[i], path[i]);
    }

    while(x == 1) {
        printf("chega");
        int path_f = INT_MAX;

        for(u = start ; u != end ; u = path[u]) {
            v = path[u];
            path_f = MIN(residual[u][v], path_f);
            printf("path -> %d\n", path_f);
        }

        for(u = start ; u != end ; u = path[u]) {
            v = path[u];
            residual[u][v] -= path_f;
            residual[v][u] += path_f;
        }

        max_flow += path_f;
    }

    return max_flow;
}