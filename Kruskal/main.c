#include "kruskal.h"

void ler_arquivo(FILE *arquivo){

	if (arquivo == NULL){
		printf("Problemas na abertura do arquivo\n");
		return;
	}

	char linha[50], *entrada_arq;

	int v1[100], v2[100], w[100];
	int no_vertices, no_arestas;

	int id_vertice = 0, i = 0, grau_maximo = 0;

	// Leitura por linhas
	while (!feof(arquivo))	{
	
		entrada_arq = fgets(linha, 100, arquivo);  // o 'fgets' lê até 99 caracteres ou até o '\n'
		if (entrada_arq)
			printf("Linha %d : %s",i,linha);

		if (i == 0){ // VERTICES E ARESTAS
			no_vertices = linha[0]-'0';
			no_arestas = linha[2]-'0';

		} else { // VERTICE1, VERTICE2 E PESO

			v1[id_vertice] = linha[0]-'0';
			v2[id_vertice] = linha[2]-'0';

			if (linha[4]){
				w[id_vertice] = linha[4]-'0';
			} else {
				w[id_vertice] = 1;
			}

			if (w[id_vertice] > grau_maximo){
				grau_maximo = w[id_vertice];
			}

			id_vertice++;

		}
		i++;
	}

	// Começa a aplicação do algoritmo
	graph g;
	g.V = no_vertices;
	g.E = grau_maximo;
	//printa_grafo(gr, no_vertices);
	
	// return gr;
}

void selecionar_parametro(int no_argumentos, char **entrada){
	char opt = entrada[1][1];
	char nome_arquivo[15];
	FILE *pont_arq;
	graph *gr;

	switch (opt)
	{
		case 'h':
			printf("HELP!\n");
			break;
			
		case 'o':
			strcpy(nome_arquivo, entrada[2]);

			printf("Arquivo: %s\n", nome_arquivo);
			printf("Saida no arquivo!\n");

			pont_arq = fopen(nome_arquivo,"w");
			fclose(pont_arq);

			break;
			
		case 'f':
			strcpy(nome_arquivo, entrada[2]);

			pont_arq = fopen(nome_arquivo,"r");

			// gr = ler_arquivo(pont_arq);
			
			fclose(pont_arq);

			break;
			
		case 's':
			printf("Ordem crescente!\n");
			break;
			
		case 'i':
			printf("Vertice inicial!\n");
			break;
			
		case 'l':
			printf("Vertice final!\n");
			break;
		
		default:
			break;
	}
}

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