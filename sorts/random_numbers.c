#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));

  if (argc < 4) {
    printf("Insira a quantidade de números, um limite e o arquivo de saída!");
    return 1;
  }

  int num = atoi(argv[1]);
  int limit = atoi(argv[2]);
  FILE *f = freopen(argv[3], "w", stdout);
  if (f == NULL) {
    printf("Erro ao abrir arquivo de saída. Verifique se o caminho e a extensao do arquivo foram escritos corretamente.");
    return 1;
  }

  int *random_numbers = (int*) malloc(num * sizeof(int));
  if (random_numbers == NULL) {
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  for (int i = 0; i < num; i++) {
    random_numbers[i] = rand() % limit; // Gera números aleatórios entre 0 e limite
  }

  printf("%d\n", num); // Imprime a quantidade de números na primeira linha
  for (int i = 0; i < num; i++) {
    printf("%d", random_numbers[i]);
    if (i < num - 1) {
      printf("\n"); // Adiciona espaço entre os números, exceto após o último
    }
  }

  free(random_numbers);

  return 0;
}