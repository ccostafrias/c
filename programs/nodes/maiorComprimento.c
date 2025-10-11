#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int valor;
  struct Node* esquerda;
  struct Node* direita;

} Node;

Node * criarNode(int valor) {
  Node * newNode = (Node*)malloc(sizeof(Node));
  newNode->valor = valor;
  newNode->esquerda = NULL;
  newNode->direita = NULL;
  return newNode;
}

void imprimir(Node* node) {
  if (node == NULL) return;

  printf("%d ", node->valor);

  imprimir(node->esquerda);
  imprimir(node->direita);
}

void liberar(Node* node) {
  if (node == NULL) return;

  liberar(node->esquerda);
  liberar(node->direita);

  free(node);
}

int maiorCaminho(Node* node, int soma) {
  if (node == NULL) return soma;

  int novaSoma = soma + node->valor;
  int somaEsquerda = maiorCaminho(node->esquerda, novaSoma);
  int somaDireita = maiorCaminho(node->direita, novaSoma);

  if (somaDireita > somaEsquerda) return somaDireita;
  else return somaEsquerda;
}

void criarNodes(Node* raiz) {
  
}

int main() {
  Node* raiz = criarNode(4);
  raiz->esquerda = criarNode(5);
  raiz->direita = criarNode(7);

  raiz->esquerda->esquerda = criarNode(4);
  raiz->esquerda->direita = criarNode(8);

  raiz->esquerda->esquerda->esquerda = criarNode(9);
  raiz->esquerda->esquerda->direita = criarNode(6);

  raiz->direita->esquerda = criarNode(3);
  raiz->direita->direita = criarNode(2);

  raiz->direita->direita->esquerda = criarNode(10);
  raiz->direita->direita->direita = criarNode(1);

  imprimir(raiz);

  int soma = maiorCaminho(raiz, 0);
  printf("\nMaior soma: %d\n", soma);

  liberar(raiz);

  return 0;
}