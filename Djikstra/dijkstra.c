#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

void dijkstra(Grafo *gr, int inicial, int *ant, int *dist){
    int i, cont, NV, ind, *visitado, u;

    cont = NV = gr->nro_vertices;

    visitado = (int*) malloc(NV * sizeof(int));

    for(i = 0; i < NV; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }

    dist[inicial] = 0;

    while(cont > 0){
        u = procura_menor_distancia(dist, visitado, NV);

        if(u == -1){
            break;
        }

        visitado[u] = 1;
        cont--;

        for(i = 0; i < gr->grau[u]; i++){
            ind = gr->arestas[u][i];
            if(dist[ind] < 0){
                dist[ind] = dist[u] + gr->pesos[u][i];

                ant[ind] = u;
            }else{
                if(dist[ind] > dist[u] + gr->pesos[u][i]){
                    dist[ind] = dist[u] + gr->pesos[u][i];

                    ant[ind] = u;
                }
            }
        }
    }

    free(visitado);
}

int procura_menor_distancia(int *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i = 0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i]){
                    menor = i;
                }
            }
        }
    }

    return menor;
}

int encontra_caminho(int origem, int objetivo, int n_vertices, int *caminho, int *ant, int cont) {
    int i;
    for(i = 0; i < n_vertices; i++){
        caminho[i] = -1;
    }

    while(objetivo != origem) {
        if(cont < 0 || objetivo < 0) {
            printf("Não existe caminho\n");
            return 0;
        }
        caminho[cont] = objetivo;
        objetivo = ant[objetivo];
        cont--;
    }

    return 1;
}

void imprime_caminho(int origem, int n_vertices, int *caminho) {
    int i;
    printf("%d ->", origem);
    for(i = 0; i < n_vertices; i++){
        if(caminho[i] != -1){
            printf(" %d", caminho[i]);
            if(i + 1 != n_vertices){
                printf(" ->");   
            }
        }
    }
    printf("\n");
}