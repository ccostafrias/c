#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void preencheEspiral(int ** v, int layer, int size, int *contagem, int direction) {
  int top = layer, left = layer;
  int bottom = size - layer - 1, right = size - layer - 1;

  // right -> left
  for (int j = right; j > left; --j) {
    v[bottom][j] = (*contagem); 
    (*contagem) += direction;
  }
  // bottom -> top
  for (int i = bottom; i > top; --i) {
    v[i][left] = (*contagem); 
    (*contagem) += direction;
  }
  // left -> right
  for (int j = left; j < right; ++j) {
    v[top][j] = (*contagem); 
    (*contagem) += direction;
  }
  // top -> bottom
  for (int i = top; i < bottom; ++i) {
    v[i][right] = (*contagem); 
    (*contagem) += direction;
  }
}

void printfMatriz(int **v, int size) {

  int maxNum = size * size;
  int width = (int)floor(log10(maxNum)) + 1;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%0*d ", width, v[i][j]);
    }
    if (i != size-1) printf("\n");
  }
  // printf("\n");
}

int main() {
  freopen("espiral.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("espiral.out", "w", stdout);

  int casos;
  scanf("%d", &casos);

  for (int c = 0; c < casos; c++) {
    int sizeEspiral; scanf("%d", &sizeEspiral);

    if (sizeEspiral <= 0 || (sizeEspiral % 2 == 0)) {
      continue;
    }

    int **matriz = (int **) malloc(sizeEspiral * sizeof(int*));
    for (int i = 0; i < sizeEspiral; i++) matriz[i] = (int *) malloc(sizeEspiral * sizeof(int));

    int dir = -1;
    int contagem = dir == 1 ? 0 : sizeEspiral*sizeEspiral;
    int camadas = sizeEspiral / 2;

    for (int layer = 0; layer < camadas; ++layer) {
      preencheEspiral(matriz, layer, sizeEspiral, &contagem, dir);
    }

    matriz[sizeEspiral/2][sizeEspiral/2] = contagem;

    printfMatriz(matriz, sizeEspiral);

    for (int i = 0; i < sizeEspiral; i++)
      free(matriz[i]);
    free(matriz);
  }

  
  return 0;
}