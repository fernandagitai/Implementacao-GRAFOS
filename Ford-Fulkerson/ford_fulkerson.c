#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

// struct AdjListNode {
//     int vertex;
//     struct AdjListNode* next;
// };

// typedef struct {
//     struct AdjListNode* head;
// } AdjList;

#define MAX_NODES 10

typedef struct {
    int V;
    int E;
    int adj_list[MAX_NODES][MAX_NODES];
} graph;

int head, tail;
int q[MAX_NODES + 2];

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

void selecionar_parametro(int no_argumentos, char **entrada, int *start, int *end){
    int i = 1;
	char opt = entrada[i][1];
	char nome_arquivo[15];
	FILE *pont_arq;

	switch (opt) {
		case 'h':
			printf("HELP!\n");
            break;
			
		case 'o':
			strcpy(nome_arquivo, entrada[2]);

			printf("Arquivo: %s\n", nome_arquivo);
			printf("Saida no arquivo!\n");

			pont_arq = fopen(nome_arquivo,"w");
			fclose(pont_arq);
            i++;
			
		case 'f':
			strcpy(nome_arquivo, entrada[i++]);

			printf("Arquivo: %s\n", nome_arquivo);
			printf("Entrada em arquivo!\n");

			pont_arq = fopen(nome_arquivo,"r");
			fclose(pont_arq);
			
		case 's':
			printf("Ordem crescente!\n");
            i++;
			
		case 'i':
            *start = atoi(entrada[i]);
			printf("Vertice inicial!\n");
			
		case 'l':
            *end = atoi(entrada[i]);
			printf("Vertice final!\n");
		
		default:
			break;
	}
}


int main( int argc, char *argv[ ] )
{
    graph g;
	int v1, v2, weight, start = -1, end = -1, cont;
  
	for(cont = 0 ; cont < argc ; cont++)
		printf("%d Parametro: %s\n", cont, argv[cont]);

    selecionar_parametro(argc, argv, &start, &end);

    printf("start %d end %d", start, end);
  
  return 0;
}