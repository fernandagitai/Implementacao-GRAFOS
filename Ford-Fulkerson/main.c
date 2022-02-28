#include "ford_fulkerson.h"

void main(int argc, char *argv[ ]) {
	int start = 0, end = 0, in = 0, out = 0, solution = 0, i, j, V, E, v1, v2, w, max_flow;
	int residual[MAX_NODES][MAX_NODES];
	char file_in_name[15], *line, line_in[100], file_out_name[15] = "", check;
	graph g;

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

	//printf("i -> %d l -> %d s -> %d txt -> %s", start, end, solution, file_in_name);

	FILE *file_in = fopen(file_in_name, "r");
	
	if(file_in == NULL){
		return;
	}

	fscanf(file_in, "%d%d", &V, &E);

	g.V = V;
	g.E = E;
	//memset(g.adj_list, 0, sizeof(g.adj_list));

	//printf("\nV -> %d E -> %d\n", g.V, g.E);

	for(i = 0 ; i < E ; i++) {
		fscanf(file_in, "%d%d%c", &v1, &v2, &check);
		if(check == ' ') {
			fscanf(file_in, "%d", &w);
		} else {
			w = 1;
		}
		//printf(" v1 -> %d v2 -> %d w -> %d\n", v1, v2, w);

		g.adj_list[v1][v2] = w;
	}

	// for(i = 1 ; i <= g.V ; i++) {
	// 	for(j = 1 ; j <= g.V ; j++) {
	// 		//if(g.adj_list[i][j] != 0)
	// 			printf("v1 -> %d v2 -> %d w -> %d\n", i, j, g.adj_list[i][j]);
	// 	}
	// }

	max_flow = ford_fulkerson(g, start, end);

	printf("%d", max_flow);

	if(strcmp(file_out_name, "")) {
		FILE *file_out = fopen(file_out_name, "w");

		if(solution) {
			for(i = 1 ; i <= g.V ; i++) {
				for(j = 1 ; j <= g.V ; j++){
					if(residual[i][j] != INT_MAX) {
						fprintf(file_out, "(%d,%d) %d\n", i, j, residual[i][j]);
					}
				}
			}
		}
		else {
			fprintf(file_out, "%d", max_flow);
		}
	}
	else {
		if(solution) {
			for(i = 1 ; i <= g.V ; i++) {
				for(j = 1 ; j <= g.V ; j++){
					if(residual[i][j] != INT_MAX) {
						printf("(%d,%d) %d\n", i, j, residual[i][j]);
					}
				}
			}
		}
		else {
			printf("%d", max_flow);
		}
	}


	//selecionar_parametro(argc, argv, &verticeInicial, &verticeFinal);
	//printf("inicio %d final %d", verticeInicial, verticeFinal);
}