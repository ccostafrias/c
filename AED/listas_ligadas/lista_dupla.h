#define FALSE 0
#define TRUE 1

#define LISTA_ORDENADA

typedef int Boolean;
typedef int Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;
	struct _no_ * anterior;

} No;

typedef struct {

	int tamanho;	
	No * cabeca;

} ListaLigada;

ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);
Boolean insere(ListaLigada * lista, Elemento e);
Boolean remove_elemento(ListaLigada * lista, Elemento e);
No * no_indice(ListaLigada * lista, int indice);
Elemento valor_indice(ListaLigada * lista, int indice);
Elemento soma(ListaLigada * lista);
ListaLigada * junta_listas_1(ListaLigada * lista_1, ListaLigada * lista_2);
ListaLigada * junta_listas_2(ListaLigada * lista_1, ListaLigada * lista_2);
ListaLigada * divide_lista(ListaLigada * lista);
Boolean processa_lista(ListaLigada * lista, Elemento max);
Boolean inverte_lista(ListaLigada * lista);
ListaLigada * devolve_lista_invertida(ListaLigada * lista);