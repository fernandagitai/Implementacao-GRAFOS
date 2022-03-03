#include <values.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "prim.h"


int main(int argc, char **argv) {
	Prim prim1;

	// inicializa prim com no maximo 200 vertices
	inicializar_prim(&prim1, argc, argv);

	// calcula o custo minimo
	calcular_custo_minimo(&prim1);

	// salva informacoes no arquivo "saida.txt"
	gerar_saida(&prim1, argc, argv); 

	liberar_grafo(&prim1);   

	return 0;
}