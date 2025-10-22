#include <stdio.h>
#include <stdlib.h>

#include "lista_dupla.h"

ListaLigada * cria_lista(){

	No * cabeca =  (No *) malloc (sizeof(No));
	cabeca->proximo = cabeca;
	cabeca->anterior = cabeca;

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->cabeca = cabeca;
	lista->tamanho = 0;
	
	return lista;
}

void destroi_lista(ListaLigada * lista){

	No * p = lista->cabeca->proximo;
	No * tmp;

	while(p != lista->cabeca){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista->cabeca);
	free(lista);
}

int tamanho(ListaLigada * lista){

	return lista->tamanho;
}

void imprime(ListaLigada * lista){

	No * p;

	printf("Lista:");

	for(p = lista->cabeca->proximo; p != lista->cabeca; p = p->proximo){

		printf(" %d", p->valor);
	}

	printf(" [ ");

	for(p = lista->cabeca->anterior; p != lista->cabeca; p = p->anterior){

		printf("%d ", p->valor);
	}

	printf("]\n");
}

No * busca_no_anterior(ListaLigada * lista, Elemento e, int * indice) {

	No * p = lista->cabeca->proximo;
	*indice = 0;

	while(p != lista->cabeca && p->valor < e){

		p = p->proximo;
		(*indice)++;
	}

	if (p->anterior != lista->cabeca && p->valor == e)
		return p->anterior;
	else
		return NULL;
}

No * busca_no(ListaLigada * lista, Elemento e, int * indice) {
	No * p = busca_no_anterior(lista, e, indice);

	return p ? p->proximo : NULL;
}

int busca(ListaLigada * lista, Elemento e){

	int indice;
	No * no = busca_no(lista, e, &indice);

	return no ? indice : -1;
}

No * no_indice(ListaLigada * lista, int indice) {
	if (!lista)
		return NULL;

	if (indice < 0)
		return lista->cabeca;

	int k = 0;
	No * node = lista->cabeca->proximo;

	while (k < indice && node != lista->cabeca) {
		node = node->proximo;
		k++;	
	}
	
	if (node == lista->cabeca) return NULL;
	return node;
}

Boolean insere(ListaLigada * lista, Elemento e){

	No * p;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	novo->proximo = novo->anterior = NULL;

	p = lista->cabeca->proximo;

	while(p != lista->cabeca){

		if(e < p->valor) break;
			
		p = p->proximo;
	}
	
	novo->proximo = p;
	novo->anterior = p->anterior;
	p->anterior->proximo = novo;
	p->anterior = novo;

	lista->tamanho++;
	return TRUE;
}

Boolean remove_elemento(ListaLigada * lista, Elemento e){

	int indice;
	No * a_remover = busca_no(lista, e, &indice);

	if(a_remover) {

		a_remover->anterior->proximo = a_remover->proximo;
		a_remover->proximo->anterior = a_remover->anterior;

		free(a_remover);

		lista->tamanho--;
		return TRUE;
	}

	return FALSE;
}

Elemento valor_indice(ListaLigada * lista, int indice) {
	No * node = no_indice(lista, indice);

	return node ? node->valor : -1;
}

Elemento soma(ListaLigada * lista) {
	Elemento sum = 0;

	for(int i = 0; i < lista->tamanho; i++) sum += valor_indice(lista, i);

	return sum;
}

ListaLigada * junta_listas_1(ListaLigada * lista_1, ListaLigada * lista_2) {
	ListaLigada * juntado = cria_lista();
	No * temp;

	for (temp = lista_1->cabeca->proximo; temp != lista_1->cabeca; temp = temp->proximo) {
		insere(juntado, temp->valor);
	}

	for (temp = lista_2->cabeca->proximo; temp != lista_2->cabeca; temp = temp->proximo) {
		insere(juntado, temp->valor);
	}

	return juntado;
}

ListaLigada * junta_listas_2(ListaLigada * lista_1, ListaLigada * lista_2) {
	No * ultimo1 = lista_1->cabeca->anterior;
	No * ultimo2 = lista_2->cabeca->anterior;

	ultimo1->proximo = lista_2->cabeca->proximo;
	ultimo2->proximo = lista_1->cabeca;

	return lista_1;
}

ListaLigada * divide_lista(ListaLigada * lista) {
	if (!lista || lista->tamanho <= 1) return NULL;

	int tamanhoPrimeira = (lista->tamanho + 1) / 2;
	No * temp = lista->cabeca;

	// Avaça até o fim da primeira
	for (int i = 0; i < tamanhoPrimeira; i++)
		temp = temp->proximo;

	No * inicioSegundaLista = temp->proximo;
	No * fimPrimeira = temp;
	No * fimSegunda = lista->cabeca->anterior;

	// Fecha primeira
	fimPrimeira->proximo = lista->cabeca;
	lista->cabeca->anterior = fimPrimeira;

	// Cria a segunda
	ListaLigada * segundaLista = cria_lista();

	// Liga cabeça <-> inicio
	segundaLista->cabeca->proximo = inicioSegundaLista;
	inicioSegundaLista->anterior = segundaLista->cabeca;

	// Liga cabeça <-> fim
	segundaLista->cabeca->anterior = fimSegunda;
	fimSegunda->proximo = segundaLista->cabeca;

	// Ajusta os tamanhos
	segundaLista->tamanho = lista->tamanho - tamanhoPrimeira;
	lista->tamanho = tamanhoPrimeira;

	return segundaLista;
}

Boolean processa_lista(ListaLigada * lista, Elemento max) {
	if (!lista || lista->tamanho == 0) return FALSE;

	No * temp;

	for (temp = lista->cabeca->proximo; temp != lista->cabeca; temp = temp->proximo) {
		while (temp->valor > max) {
			No * novo = (No *) malloc(sizeof(No));

			novo->valor = max;
			
			// anterior <-> novo
			temp->anterior->proximo = novo;
			novo->anterior = temp->anterior;

			// novo <-> temp
			temp->anterior = novo;
			novo->proximo = temp;

			temp->valor -= max;
			lista->tamanho++;
		} 
	}

	return TRUE;
}

Boolean inverte_lista(ListaLigada * lista) {
	No * atual = lista->cabeca;
	No * proximo;

	do {
		proximo = atual->proximo;

		atual->proximo = atual->anterior;
		atual->anterior = proximo;

		atual = proximo;
	} while (atual != lista->cabeca);

	return TRUE;
}

ListaLigada * devolve_lista_invertida(ListaLigada * lista) {
	ListaLigada * invertida = cria_lista();
	No * temp, * livreInvertida = invertida->cabeca;

	for (temp = lista->cabeca->anterior; temp != lista->cabeca; temp = temp->anterior) {
		No * novo = (No *) malloc(sizeof(No));
		novo->valor = temp->valor;

		livreInvertida->proximo = novo;
		novo->anterior = livreInvertida;

		livreInvertida = novo;
	}

	livreInvertida->proximo = invertida->cabeca;
	invertida->cabeca->anterior = livreInvertida;
	
	invertida->tamanho = lista->tamanho;

	return invertida;
}