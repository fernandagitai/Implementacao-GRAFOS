#include "ford_fulkerson.h"

void main(int argc, char *argv[ ]) {
	int start = -1, end = -1, solution = 0, i, j, V, E, v1, v2, w, max_flow;
	char file_in_name[100], file_out_name[100] = "", check;
	graph g;

	for(i = 0 ; i < argc ; i++){
		if(!strcmp(argv[i], "-h")) {
			printf("\n\n---------Ford-Fulkerson Algorithm---------\n\n\n");
			printf("The inputs needed to run the algorithm are:\n\n");
			printf(" -f <input_file_name>\n");
			printf(" -i <initial_vertex>\n");
			printf(" -l <end_vertex>\n\n\n");
			printf("Others possible arguments are:\n\n");
			printf(" -o <output_file_name>\n");
			printf(" -s (solution in ascending order)");
			printf("\n\n------------------------------------------\n\n");

			return;
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
	
	if(file_in == NULL || start == -1 || end == -1) {
		printf("Invalid input.\n");
		return;
	}

	fscanf(file_in, "%d%d", &V, &E);

	g.V = V;
	g.E = E;

	int residual[g.V][g.V];

	for(i = 0 ; i < E ; i++) {
		fscanf(file_in, "%d%d%c", &v1, &v2, &check);
		if(check == ' ') {
			fscanf(file_in, "%d", &w);
		} else {
			w = 1;
		}

		g.adj_list[v1][v2] = w;
	}

	max_flow = ford_fulkerson(g, start, end, residual);

	if(strcmp(file_out_name, "")) {
		FILE *file_out = fopen(file_out_name, "w");

		if(solution) {
			for(i = 1 ; i <= g.V ; i++) {
				for(j = 1 ; j <= g.V ; j++){
					if(residual[i][j] != 0) {
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
					if(residual[i][j] != 0) {
						printf("(%d,%d) %d\n", i, j, residual[i][j]);
					}
				}
			}
		}
		else {
			printf("%d\n", max_flow);
		}
	}
}