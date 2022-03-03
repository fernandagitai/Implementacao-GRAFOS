#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define V 9
#define INFINITY 9999

int getInicio(int no_argumentos, char **entrada) {

    int verticeInicial;
    
    for(int i=0; i<no_argumentos; i++)
        if(strstr(entrada[i], "-i") != NULL) 
            verticeInicial = atoi(entrada[i+1]);
    
    return verticeInicial;
}

int getFinal(int no_argumentos, char **entrada) {

    int verticeFinal = -1;
    
    for(int i=0; i<no_argumentos; i++){
        if(strstr(entrada[i], "-l") != NULL) 
            verticeFinal = atoi(entrada[i+1]);
    }
    return verticeFinal;
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



void dijkstra(int Graph[V][V], int n, int start, int verticeFinal, int no_argumentos, char **entrada) {
  int cost[V][V], pred[V], distance[V];

  int visited[V], count, mindistance, nextnode, i, j;

  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i <= n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count <= n) {
    mindistance = INFINITY;

    for (i = 0; i <= n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i <= n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }


    FILE *arquivoO = getArquivoSaida(no_argumentos, entrada);
    char saida = getTipoDeSaida(no_argumentos, entrada);

    int verticeAux;
    if(verticeFinal != -1)
        verticeAux = distance[verticeFinal];

    // distance = {INFINITY};

    switch (saida)
    {    
    case 'o':
        if(verticeFinal != -1){
            fprintf(arquivoO, "%d", distance[verticeFinal]);
            break;
        }
        for (i = 0; i <= n; i++)
            if (distance[i] != INFINITY)
                fprintf(arquivoO, "%d:%d ", i, distance[i]);
        
        break;
    
    default:
        if(verticeFinal != -1){
            printf("%d\n", distance[verticeFinal]);
            break;
        }
        for (i = 0; i <= n; i++)
            if (distance[i] != INFINITY)
                printf("%d:%d ", i, distance[i]);
        break;
    }
}


int main( int argc, char *argv[ ] )
{
  int grafo[V][V] = {0};

  // Leitura de arquivo
  FILE *arquivoF = getArquivo(argc, argv);
  FILE *arquivoO = getArquivoSaida(argc, argv);
   
  char linha[50], *entrada_arq;

	int v1, v2, w;
	int no_vertices, no_arestas;

	int i = 0, j=0;

    // Lendo arquivo
  while (!feof(arquivoF))	{
	
		entrada_arq = fgets(linha, 100, arquivoF);  // o 'fgets' lê até 99 caracteres ou até o '\n'

		if (i == 0){ // VERTICES E ARESTAS
			no_vertices = linha[0]-'0';
			no_arestas = linha[2]-'0';

		} else { // VERTICE1, VERTICE2 E PESO

			v1 = linha[0]-'0';
			v2 = linha[2]-'0';

			if (linha[4]){
				w = linha[4]-'0';
			} else {
				w = 1;
			}
            grafo[v1][v2] = w;
            grafo[v2][v1] = w;
		}
		i++;
	}

  int verticeInicial, verticeFinal;

  verticeInicial = getInicio(argc, argv);
  verticeFinal = getFinal(argc, argv);

  dijkstra(grafo, no_vertices, verticeInicial, verticeFinal, argc, argv);

  fclose(arquivoF);
  fclose(arquivoO);
    
	return 0;
}
