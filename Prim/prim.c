#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prim.h"




int getInicio(int no_argumentos, char **entrada) {

    int verticeInicial;
    
    for(int i=0; i<no_argumentos; i++)
        if(strstr(entrada[i], "-i") != NULL) 
            verticeInicial = atoi(entrada[i+1]);
    
    return verticeInicial;
}

char getTipoDeSaida(int no_argumentos, char **entrada){
    
    for(int i=0; i<no_argumentos; i++)
        if(strstr(entrada[i], "-s") != NULL) 
            return 's';
        else if(strstr(entrada[i], "-o") != NULL)
            return 'o';
    
    return 'x';
}

FILE *getArquivoSaida(int no_argumentos, char **entrada) {
    
    char nomeArquivo[20];
    FILE *arqSaida;
    
    for(int i=0; i<no_argumentos; i++){
        if(strstr(entrada[i], "-o") != NULL) 
            strcpy(nomeArquivo, entrada[i+1]);
    }

    arqSaida = fopen(nomeArquivo, "wb");
    return arqSaida;
}

FILE *getArquivo(int no_argumentos, char **entrada) {
    
    char nomeArquivo[20];
    FILE *pont_arq;
    
    for(int i=0; i<no_argumentos; i++){
        if(strstr(entrada[i], "-f") != NULL) 
            strcpy(nomeArquivo, entrada[i+1]);
    }

    pont_arq = fopen(nomeArquivo, "r");
    return pont_arq;
}



void inicializar_prim(Prim *prim, int no_argumentos, char **entrada) {

	prim->max_vertices = V;
	prim->infinito = INFINITY; 
	alocar_grafo(prim);
	

    // Leitura de arquivo
    FILE *arquivo = getArquivo(no_argumentos, entrada);
    
    char linha[50], *entrada_arq;

	int v1, v2, w;
	int no_vertices, no_arestas;

	int i = 0;

    // Lendo arquivo
    while (!feof(arquivo))	{
	
		entrada_arq = fgets(linha, 100, arquivo);  // o 'fgets' lê até 99 caracteres ou até o '\n'

		if (i == 0){ // VERTICES E ARESTAS
			prim->vertices = linha[0]-'0';
			prim->arestas = linha[2]-'0';

		} else { // VERTICE1, VERTICE2 E PESO

			v1 = linha[0]-'0';
			v2 = linha[2]-'0';

			if (linha[4]){
				w = linha[4]-'0';
			} else {
				w = 1;
			}
			prim->grafo[v1][v2] = w;
			prim->grafo[v2][v1] = w;
		}
		i++;
	}

    int verticeInicial = getInicio(no_argumentos, entrada);

	fclose(arquivo);
}

void alocar_grafo(Prim *prim) {
	int i, j;

	// alocar linhas
	prim->grafo = (int**)malloc(sizeof(int*) * prim->vertices);

	// alocar colunas
	for(i = 0; i < prim->vertices; i++) {
		prim->grafo[i] = (int*)malloc(sizeof(int) * prim->vertices);
	}

	for(i = 0; i < prim->vertices; i++) {
		for(j = 0; j < prim->vertices; j++) {
			prim->grafo[i][j] = prim->infinito;
		}
	}

}

void calcular_custo_minimo(Prim *prim) {
	mostrar_custo_minimo(prim);
	mostrar_ordem_vertices(prim);
}

void mostrar_custo_minimo(Prim *prim) {
	int i, j;
	int visitados[prim->vertices];
	int minimo = prim->infinito;
	int u = 0, v = 0, total = 0;
	int esta_rodando = 1;

	for (v = 0; v < prim->vertices; v++)
		visitados[v] = -1;

	visitados[0] = 0;
	while (esta_rodando != 0) {
	   	minimo = prim->infinito;
	   	for (i = 0; i < prim->vertices; i++) 
	       	if (visitados[i] != -1) 
	          	for (j = 0; j < prim->vertices; j++)
	           		if (visitados[j] == -1 && minimo > prim->grafo[i][j]) {
	               		minimo = prim->grafo[i][j];
	               		u = i;
	               		v = j;
	           		}
	   	
	   	if (minimo == prim->infinito) {
	   		esta_rodando = 0; // fim do laco
	   		break; // sai do laco
	   	}

	   	visitados[v] = u;
	   	total+= minimo;
	}
	prim->custo_minimo = total;
	printf("%d\n", prim->custo_minimo);
}

void mostrar_ordem_vertices(Prim *prim) {
	int i, j;
	int visitados[prim->vertices];
	int minimo = prim->infinito;
	int u = 0, v = 0;
	int esta_rodando = 1;

	for (v = 0; v < prim->vertices; v++)
		visitados[v] = -1;

	visitados[0] = 0;
	while (esta_rodando != 0) {
	   	minimo = prim->infinito;
	   	for (i = 0; i < prim->vertices; i++) 
	       	if (visitados[i] != -1) 
	          	for (j = 0; j < prim->vertices; j++)
	           		if (visitados[j] == -1 && minimo > prim->grafo[i][j]) {
	               		minimo = prim->grafo[i][j];
	               		u = i;
	               		v = j;
	           		}
	   	
	   	if (minimo == prim->infinito) {
	   		esta_rodando = 0; // fim do laco
	   		break; // sai do laco
	   	}

	   	visitados[v] = u;
	   	printf("(%d, %d) ", u, v);
	}
	printf("\n");
}

void gerar_saida(Prim *prim, int no_argumentos, char **entrada) {
	
	FILE *arquivoSaida = getArquivoSaida(no_argumentos, entrada);

	fprintf(arquivoSaida, "%s: %d\n", prim->arquivo_saida, prim->custo_minimo); // salva informacoes no arquivo prim->arquivo_saida
	printf("%s: %d\n", prim->arquivo_saida, prim->custo_minimo); // salva informacoes no arquivo prim->arquivo_saida
	fclose(arquivoSaida);
}
