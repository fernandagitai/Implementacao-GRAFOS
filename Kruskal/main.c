#include "kruskal.h"

void main( int argc, char *argv[ ] ) {
	int start = 0, end = 0, in = 0, out = 0, solution = 0, i, mst_length, V, E, v1, v2, w, cost;
	char file_in_name[1000], file_out_name[1000] = "", check;
	graph g;

	for(i = 0 ; i < argc ; i++){
		if(!strcmp(argv[i], "-h")) {
			printf("\n------------Kruskal Algorithm------------\n\n\n");
			printf("The input needed to run the algorithm is:\n\n");
			printf(" -f <input_file_name>\n\n\n");
			printf("Others possible arguments are:\n\n");
			printf(" -o <output_file_name>\n");
			printf(" -s (solution in ascending order)");
			printf(" -i <initial_vertex>\n");
			printf(" -l <end_vertex>\n");
			printf("\n------------------------------------------\n\n");

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
	
	if(file_in == NULL){
		return;
	}

	fscanf(file_in, "%d%d", &V, &E);

	g.V = V;
	g.E = E;
	g.edge = malloc(E * sizeof(int*));

	int mst[g.E][3];
	memset(mst, 0, sizeof(mst));

	for(i = 0 ; i < E ; i++) {
		fscanf(file_in, "%d%d%c", &v1, &v2, &check);
		if(check == ' ') {
			fscanf(file_in, "%d", &w);
		} else {
			w = 1;
		}
		g.edge[i] = malloc(3 * sizeof(int));

		g.edge[i][0] = v1;
		g.edge[i][1] = v2;
		g.edge[i][2] = w;
	}

	cost = kruskal(&g, mst, &mst_length);

	if(strcmp(file_out_name, "")) {
		FILE *file_out = fopen(file_out_name, "w");

		if(solution) {
			for(i = 0 ; i < mst_length ; i++) {
				fprintf(file_out, "(%d,%d) : %d\n", mst[i][0], mst[i][1], mst[i][2]);
			}
		}
		else {
			fprintf(file_out, "%d", cost);
		}
	}
	else {
		if(solution) {
			for(i = 0 ; i < mst_length ; i++) {
				printf("(%d,%d) : %d\n", mst[i][0], mst[i][1], mst[i][2]);
			}
		}
		else {
			printf("%d", cost);
		}
	}

	free_graph(&g);
}