#include "ford_fulkerson.h"

void print_help() {
    printf("\n---------Ford-Fulkerson Algorithm---------\n\n\n");
    printf("The inputs needed to run the algorithm are:\n\n");
    printf(" -f <input_file_name>\n");
    printf(" -i <initial_vertex>\n");
    printf(" -l <end_vertex>\n\n\n");
    printf("Others possible arguments are:\n\n");
    printf(" -o <output_file_name>\n");
    printf(" -s (solution in ascending order)");
    printf("\n\n------------------------------------------\n\n");
}

int dfs(int v, int residual[][v], int start, int end, int visited[v], int path[v]) {
    int i, j, current;

    if (start == end) {
        return 1;
    }

    for(i = 1 ; i <= v ; i++) {
        current = residual[start][i];
        if(visited[i] == 0 && current > 0) {
            path[start] = i;
            visited[i] = 1;

            if(dfs(v, residual, i, end, visited, path) != 0) {
                visited[i] = 0;

                return 1;
            } 
            else {
                visited[i] = 0;
                path[start] = -1;
            }
        }
    }

    return 0;
}

int ford_fulkerson(graph g, int start, int end, int residual[g.V][g.V]) {
    int u, v, max_flow = 0, i, j, path[g.V], visited[g.V];

    for(i = 1 ; i <= g.V ; i++) {
        path[i] = 0;
        visited[i] = 0;

        for(j = 1 ; j <= g.V ; j++){
            residual[i][j] = g.adj_list[i][j];
        }
    }

    visited[start] = 1;

    while(dfs(g.V, residual, start, end, visited, path) == 1) {
        int path_f = INT_MAX;

        for(u = start ; u != end ; u = path[u]) {
            v = path[u];
            path_f = MIN(residual[u][v], path_f);
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