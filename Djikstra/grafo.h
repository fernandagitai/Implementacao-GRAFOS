struct grafo{
    int nro_vertices;
    int grau_max;
    int** arestas;
    int** pesos;
    int* grau;
};

typedef struct grafo Grafo;

Grafo *cria_grafo(int nro_vertices, int grau_max);
int remove_aresta(Grafo* gr, int origem, int destino, int eh_digrafo);
int insere_aresta(Grafo* gr, int origem, int destino, int peso);
void libera_grafo(Grafo *gr);
void printa_grafo(Grafo *gr, int nro_vertices);