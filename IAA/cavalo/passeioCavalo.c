#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int movX[] = {2, 1, -1, -2, -2, -1, 1, 2};
int movY[] = {1, 2, 2, 1, -1, -2, -2, -1};

int ** inicia(int x, int y, int size) {
  int **matriz = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) matriz[i] = malloc(size * sizeof(int));
  
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matriz[i][j] = 0;
    }
  }

  matriz[y][x] = 1;

  return matriz;
}

void printa(int **matriz, int size) {
  int maxNum = size * size;
  int width = (int)floor(log10(maxNum)) + 1;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%0*d ", width, matriz[i][j]);
    }
    
    if (i != size - 1) printf("\n");
  }
}

void limpa(int **matriz, int n) {
  for (int i = 0; i < n; i++) {
    free(matriz[i]);
  }

  free(matriz);
}

int tenta(int **matriz, int indice, int x, int y, int size) {
  if (indice > size * size) return 1; // sucesso

  // k = movimento do cavalo (existem 8 no total)
  for (int k = 0; k < 8; k++) {
    int newX = x + movX[k];
    int newY = y + movY[k];

    // confirma se a nova posição está dentro dos limites
    if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
      // se a nova posição estiver vazia (não foi visitada)
      if (matriz[newY][newX] == 0) {
        matriz[newY][newX] = indice;
        if (tenta(matriz, indice + 1, newX, newY, size)) return 1;
        matriz[newY][newX] = 0; // se não conseguiu, volta
      }
    }
  }

  return 0; // falhou
}

int main() {
  freopen("saida.out", "w", stdout);
  
  int size, startX, startY;
  scanf("%d", &size);
  scanf("%d %d", &startX, &startY);

  int **matriz = inicia(startX, startY, size);

  if (tenta(matriz, 2, startX, startY, size)) {
    printa(matriz, size);
  } else {
    printf("num deu :(");
  }

  limpa(matriz, size);
  return 0;
}