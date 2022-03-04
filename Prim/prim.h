#ifndef PRIM_C
#define PRIM_C

#define V 100
#define INFINITY 9999

struct prim {
	int vertices;
	int verticeInicial;
	int arestas;
	int **grafo; 
	int max_vertices;
	int infinito;
	int custo_minimo; 
    char arquivo_saida[64];
};

typedef struct prim Prim;

void inicializar_prim(Prim *prim, int no_argumentos, char **entrada);

void alocar_grafo(Prim *prim);

void calcular_custo_minimo(Prim *prim);

void mostrar_custo_minimo(Prim *prim);

void mostrar_ordem_vertices(Prim *prim);

void gerar_saida(Prim *prim, int no_argumentos, char **entrada);

int getInicio(int no_argumentos, char **entrada);

char getTipoDeSaida(int no_argumentos, char **entrada);

FILE *getArquivoSaida(int no_argumentos, char **entrada);

FILE *getArquivo(int no_argumentos, char **entrada);

void liberar_grafo(Prim *prim);

#endif 