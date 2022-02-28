#include <stdio.h>
#include <math.h>
#include <string.h>

void selecionar_parametro(int no_argumentos, char **entrada){

	char opt = entrada[1][1];
	char nome_arquivo[15];
	FILE *pont_arq;

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

			printf("Arquivo: %s\n", nome_arquivo);
			printf("Entrada em arquivo!\n");

			pont_arq = fopen(nome_arquivo,"r");
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


int main( int argc, char *argv[ ] )
{
	int cont;
  
	for(cont=0; cont < argc; cont++)
		printf("%d Parametro: %s\n", cont,argv[cont]);

	selecionar_parametro(argc, argv);
  
  return 0;
}