#include <stdio.h>

//#include "lista_ligada.h"
// #include "lista_ligada_circular.h"
#include "lista_dupla.h"

int main(){

	int x;
	ListaLigada * lista = cria_lista();	

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

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	remove_elemento(lista, 4);
	remove_elemento(lista, 5);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	// printf("------------------------------------------------------------------------------------\n");

	// for(x = 1; x <= 6; x++) {

	// 	remove_elemento(lista, x);
	// 	imprime(lista);
	// }


	// for(x = 9; x <= 14; x++) {

	// 	insere(lista, (x % 6) + 1);
	// 	imprime(lista);
	// }
	
	printf("------------------------------------------------------------------------------------\n");

	for (int i = 0; i <= tamanho(lista) + 1; i++) {
		printf("elemento %d: %d\tvalor: %d\n", i, valor_indice(lista, i), no_indice(lista, i));
	}

	printf("------------------------------------------------------------------------------------\n");

	imprime(lista);
	printf("Soma: %d\n", soma(lista));
	remove_elemento(lista, 3);
	remove_elemento(lista, 1);
	remove_elemento(lista, 6);
	remove_elemento(lista, 2);
	imprime(lista);

	int TAM = 10;

	for (int i = 0; i < TAM; i++) {
		insere(lista, 3*i);
	}
	imprime(lista);

	ListaLigada * lista2 = cria_lista();

	for (int i = 0; i < TAM; i++) {
		insere(lista2, 2*i);
	}
	imprime(lista2);

	ListaLigada * juntinho1 = junta_listas_1(lista, lista2);
	// ListaLigada * juntinho2 = junta_listas_2(lista, lista2);

	printf("------------------------------------------------------------------------------------\n");
	
	imprime(juntinho1);
	printf("Soma: %d\n", soma(juntinho1));

	printf("------------------------------------------------------------------------------------\n");

	ListaLigada * dividida = divide_lista(juntinho1);
	imprime(juntinho1);
	printf("Soma: %d\n", soma(juntinho1));
	imprime(dividida);
	printf("Soma: %d\n", soma(dividida));

	printf("------------------------------------------------------------------------------------\n");

	processa_lista(juntinho1, 8);
	imprime(juntinho1);
	processa_lista(dividida, 10);
	imprime(dividida);

	printf("------------------------------------------------------------------------------------\n");

	inverte_lista(dividida);
	imprime(dividida);
	ListaLigada * divididaInvertida = devolve_lista_invertida(dividida);
	imprime(divididaInvertida);

	printf("------------------------------------------------------------------------------------\n");

	destroi_lista(lista);
	return 0;
}