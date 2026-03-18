#include <stdio.h>

#include "arvore_binaria.h"

int teste1(){

	int x;

	Arvore * arvore = cria_arvore();
	insere_ord(arvore, 80);
	insere_ord(arvore, 100);
	insere_ord(arvore, 50);
	insere_ord(arvore, 90);
	insere_ord(arvore, 10);
	insere_ord(arvore, 70);
	insere_ord(arvore, 20);
	insere_ord(arvore, 5);
	insere_ord(arvore, 30);
	insere_ord(arvore, 105);
	insere_ord(arvore, 120);
	imprime(arvore);
	display(arvore);
	printf("%s", verifica_ABB1(arvore->raiz) ? "EH\n" : "NUM EH\n");

	remove_ord(arvore, busca(arvore, 10));
	imprime(arvore);
	display(arvore);
	printf("%s", verifica_ABB1(arvore->raiz) ? "EH\n" : "NUM EH\n");

	remove_ord(arvore, busca(arvore, 80));
	imprime(arvore);
	display(arvore);
	printf("%s", verifica_ABB1(arvore->raiz) ? "EH\n" : "NUM EH\n");
	
	return 0;
}

int teste2(){

	int i, x;
	
	int valores[] = { 40, 20, 70, 10, 30, 50, 80, 15, 200};

	Arvore * arvore = cria_arvore();

	for(i = 0; i < sizeof(valores)/sizeof(int); i++){

		insere_ord(arvore, valores[i]);
		imprime(arvore);
	}

	display(arvore);

	debug_on();

	x = 50;
	printf("\nProcurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");
	
	x = 90;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");

	x = 30;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");

	debug_off();

	imprime(arvore);
	display(arvore);

	for(i = 0; i < sizeof(valores)/sizeof(int); i++){

		x = valores[i];
		printf("removendo %d...\n", x); getchar();

		remove_ord(arvore, busca_bin(arvore, x));
		imprime(arvore);
		display(arvore);
	}
	
	return 0;
}

int main(){

	return teste1();
	// return teste2();
}

