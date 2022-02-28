#include "kruskal.h"

void main( int argc, char *argv[ ] ){
	int start = 0, end = 0, in = 0, out = 0, solution = 0, i, j, V, E, v1, v2, w, cost;
	int residual[MAX_NODES][MAX_NODES];
	char file_in_name[15], *line, line_in[100], file_out_name[15] = "", check;
	graph *g;

	for(i = 0 ; i < argc ; i++){
		if(!strcmp(argv[i], "-h")) {
			//show help
		}

		else if(!strcmp(argv[i], "-o")) {
			strcpy(file_out_name, argv[i + 1]);
		}

		else if(!strcmp(argv[i], "-f")) {
			if(!strcmp(argv[i + 1], "-s")) {
				strcpy(file_in_name, argv[i + 2]);
			} else {
				strcpy(file_in_name, argv[i + 1]);
			}
		}
		
		else if(!strcmp(argv[i], "-s")) {
			solution = 1;
		}

		else if(!strcmp(argv[i], "-i")) {
			start = atoi(argv[i + 1]);
		}

		else if(!strcmp(argv[i], "-l")) {
			end = atoi(argv[i + 1]);
		}		
	}

	FILE *file_in = fopen(file_in_name, "r");
	
	if(file_in == NULL){
		return;
	}

	fscanf(file_in, "%d%d", &V, &E);

	g->V = V;
	g->E = E;
	//memset(g.edge, 0, sizeof(g.edge));

	//printf("\nV -> %d E -> %d\n", g.V, g.E);

	for(i = 0 ; i < E ; i++) {
		fscanf(file_in, "%d%d%c", &v1, &v2, &check);
		if(check == ' ') {
			fscanf(file_in, "%d", &w);
		} else {
			w = 1;
		}
		//printf(" v1 -> %d v2 -> %d w -> %d\n", v1, v2, w);

		g->edge[v1][v2] = w;
	}

	cost = kruskal(g);

	printf("%d", cost);
}