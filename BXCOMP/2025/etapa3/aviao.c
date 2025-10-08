#include <stdio.h>

#define SIZE 6

double min(int a, int b) { return a < b ? a : b; }

void read_matrix(int matrix[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      scanf("%d", &matrix[i][j]);
    } 
  }
}

int sum_matrix(int matrix[SIZE][SIZE], int start, int end) {
  int sum = 0;

  for (int i = 0; i < SIZE; i++) {
    for (int j = start; j < end; j++) {
      sum += matrix[i][j];
    }
  }

  return sum;
}

int hasFound(int matrix[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (matrix[i][j] >= 3 && (j < 2 || j > 3)) return 1;
    }
  }

  return 0;
}

int main () {
  int casos; scanf("%d", &casos);
  for (int caso = 0; caso < casos; caso++) {
    int aviao[SIZE][SIZE];
    read_matrix(aviao);

    int sumEsq = sum_matrix(aviao, 0, 3), sumDir = sum_matrix(aviao, 3, 6);
    double minorSide = min(sumEsq, sumDir), maxSide = minorSide == sumEsq ? sumDir : sumEsq;

    if (minorSide >= 0.8*maxSide && !hasFound(aviao)) {
      printf("DEU BOM\n");
    } else printf("DEU RUIM\n");
  }

  return 0;
}