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
	graph* g = (graph*)(malloc(sizeof(graph)));
	int V, E, v1, v2, w;
	scanf("%d%d", &V, &E);
	g->V = V;
	g->E = E;

	for(int i = 0 ; i < E ; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		
		g->edge[i][0] = v1;
		g->edge[i][1] = v2;
		g->edge[i][2] = w;
	}
	
	kruskal(g);

	//selecionar_parametro(argc, argv);
}