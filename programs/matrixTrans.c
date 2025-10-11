#include <stdio.h>
#include <stdlib.h>

int ** start_matrix(int size) {
  int ** matrix = (int**) malloc(size * sizeof(int*));
  for (int i = 0; i < size; i++) matrix[i] = (int*) malloc(size * sizeof(int));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
  
  return matrix;
}

void print_matrix(int ** matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d", matrix[i][j]);
      if (j != size-1) printf(" ");
    }
    if (i != size-1) printf("\n");
  }
  printf("\n");
}

void transform_trans(int ** matrix, int size) {
  int temp;
  for (int i = 0; i < size; i ++) {
    for (int j = i+1; j < size; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }

}

int main(int argc, char * argv[]) {
  if (argc < 3) {
    printf("para de ser BURRO");
    return 1;
  }

  freopen(argv[2], "r", stdin);

  int size = atoi(argv[1]);
  int ** matrix = start_matrix(size);

  print_matrix(matrix, size);
  transform_trans(matrix, size);
  printf("==========\n");
  print_matrix(matrix, size);

  return 0;
}