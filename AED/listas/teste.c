#include <stdio.h>

#define LISTA_ORDENADA

#ifdef LISTA_ORDENADA
	#include "lista_sequencial_ordenada.h"
#else
	#include "lista_sequencial.h"
	//#include "lista_sequencial_dinamica.h"
#endif


int main(){
	int x;

	ListaSequencial * lista = cria_lista(10000);

	imprime(lista);
	printf("------------------------------------------------------------------------------------\n");

	#ifdef LISTA_ORDENADA
		insere(lista, 3);
		insere(lista, 1);
		insere(lista, 5);
		insere(lista, 4);
		insere(lista, 2);
	#else
		insere(lista, 3, 0);
		insere(lista, 1, 1);
		insere(lista, 5, 2);
		insere(lista, 4, 3);
		insere(lista, 2, 4);
	#endif	

	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));
	
	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	#ifdef LISTA_ORDENADA
		insere(lista, 6);
	#else
		insere(lista, 6, 2);
	#endif
	
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	remove_elemento(lista, 6);
	remove_elemento(lista, 5);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	for (int i = 0; i < tamanho(lista); i++) {
		printf("elemento %d: %d\n", i, valor_indice(lista, i));
	}

	printf("Soma: %d\n", soma(lista));

	for (int i = 0; i < lista->capacidade; i++) {
		insere(lista, i);
	}

	imprime(lista);
	printf("Soma: %d\n", soma(lista));

	destroi_lista(lista);
	return 0;
}

