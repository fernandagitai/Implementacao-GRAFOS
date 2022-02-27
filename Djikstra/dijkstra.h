#include "grafo.h"

void dijkstra(Grafo *gr, int inicial, int *ant, int *dist);
int procura_menor_distancia(int *dist, int *visitado, int NV);
int encontra_caminho(int origem, int objetivo, int n_vertices, int *caminho, int *ant, int cont);
void imprime_caminho(int origem, int n_vertices, int *caminho);