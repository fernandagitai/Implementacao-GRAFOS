#include "ford_fulkerson.h"

void enqueue(int x) {
    q[tail] = x;
    tail++;
}

int dequeue() {
    int x = q[head];
    head++;
    return x;
}

int bfs(graph g, int residual[MAX_NODES][MAX_NODES], int start, int end, int parent[]) {
    int visited[g.V], i;
    memset(visited, 0, sizeof(visited));
    visited[start] = 1;

    enqueue(start);

    int dequeued;

    while(head != tail){
        dequeued = dequeue();

        for(i = 0 ; i < g.V ; i++) {
            if(visited[i] == 0 && residual[dequeued][i] > 0) {
                parent[i] = dequeued;
                visited[i] = 1;
                enqueue(i);
            }
        }
    }

    return visited[end];
}

int ford_fulkerson(graph g, int start, int end) {
    int u, v, max_flow = 0, i, j;
    int *parent;

    int residual[MAX_NODES][MAX_NODES];

    for(i = 0 ; i < g.V ; i++) {
        for(j = 0 ; j < g.V ; j++){
            residual[i][j] = g.adj_list[i][j];
        }
    }

    while(bfs(g, residual, start, end, parent) == 1) {
        int path = INT_MAX;

        for(v = end ; v != start ; v = parent[v]) {
            u = parent[v];
            path = (residual[u][v] < path)? residual[u][v] : path;
        }

        for(v = end ; v != start ; v = parent[v]) {
            u = parent[v];
            residual[u][v] -= path;
            residual[v][u] += path;
        }

        max_flow += path;
    }

    return max_flow;
}