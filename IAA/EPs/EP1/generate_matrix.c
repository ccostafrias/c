#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PESO
#define MAX 200

int rand_num(int min, int max) { return rand() % (max - min) + min; }

int get_element(int peso) {
  int percent = rand_num(0, 101);
  return percent < peso ? 0 : rand_num(1, MAX); 
}

void matriz_xadrez(int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if ((j + (i % 2)) % 2 == 0) printf("0");
      else printf("%d", rand_num(1, 200));

      if (j != cols-1) printf(" ");
    }
    if (i != rows-1) printf("\n");
  }
}

void matriz_peso(int rows, int cols, int peso) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d", get_element(peso));
      if (j != cols - 1) printf(" ");
    }
    if (i != rows - 1) printf("\n");
  }
}

int main (int argc, char *argv[]) {
  srand(time(NULL));  // Define a semente baseada no tempo atual
  freopen("arquivo.txt", "w", stdout);

  if (argc < 3) {
    printf("Nao ha parametros suficientes, faça:\n./ARQUIVO.exe <peso> <tamanho>");
    return 1;
  }

  int size = atoi(argv[2]);

  #ifdef PESO
    int peso = atoi(argv[1]);

    matriz_peso(size, size, peso);
  #else
    matriz_xadrez(size, size);
  #endif

  return 0;
}