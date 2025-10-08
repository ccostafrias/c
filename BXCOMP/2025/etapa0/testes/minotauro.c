#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define PALAVRA "MINOTAURO"

void free_matrix(char ** matrix, int row) {
    for (int i = 0; i < row; i++) {
      free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(char ** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        printf("%c", matrix[i][j]);
        if (j != col-1) printf(" ");
      }
      printf("\n");
    }
}

void read_matrix(char ** matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      scanf(" %c", &matrix[i][j]);
    }
  }
}

int tenta(char ** matrix, int row, int col, int i, int j, int indice) {
  if (PALAVRA[indice] == '\0') return TRUE;
  if (PALAVRA[indice] != matrix[i][j]) return FALSE;

  int tentou = 0;

  // cima
  if (i > 0 && !tentou) { tentou = tenta(matrix, row, col, i-1, j, indice+1); }

  // esquerda
  if (j > 0 && !tentou) { tentou = tenta(matrix, row, col, i, j-1, indice+1); }

  // baixo
  if (i < row-1 && !tentou) { tentou = tenta(matrix, row, col, i+1, j, indice+1); }

  // direita
  if (j < col-1 && !tentou) { tentou = tenta(matrix, row, col, i, j+1, indice+1); }

  if (tentou) return TRUE;
  return FALSE;
}

int percorre(char ** matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (tenta(matrix, row, col, i, j, 0)) return TRUE;
    }
  }
  return FALSE;
}

int main() {
  freopen("entrada.in", "r", stdin);
  freopen("saida.out", "w", stdout);

  int casos;
  scanf("%d", &casos);
  for (int caso = 0; caso < casos; caso++) {
    int row, col;
    scanf("%d %d", &row, &col);

    char ** matrix = (char**) malloc(row*sizeof(char*));
    for (int i = 0; i < row; i++) matrix[i] = (char*) malloc(col*sizeof(char));
    
    read_matrix(matrix, row, col);
    // print_matrix(matrix, row, col);

    if (percorre(matrix, row, col)) printf("ACHAMOS %s!\n", PALAVRA);
    else printf("NUM TEM %s\n", PALAVRA);

    free_matrix(matrix, row);
  }

  return 0;
}