#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomN(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void swap(int * vec, int iA, int iB) {
  if (iA == iB) return;
  
  int temp = vec[iB];
  vec[iB] = vec[iA];
  vec[iA] = temp;
}

void print_vec(int * vec, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}

void bogo_sort(int * numbers, int len) {
  int ordenado;
  int i, randI;

  do {
    ordenado = 1;
    for (i = 0; i < len; i++) {
      randI = randomN(i, len-1);
      swap(numbers, i, randI);
      if (i != 0 && numbers[i-1] > numbers[i]) ordenado = 0;
    }
    print_vec(numbers, len);
  } while(!ordenado);

}

int main(int argc, char * argv[]) {
  srand(time(NULL));
  
  if (argc == 3) {
    char command[128];
    sprintf(command, "random_numbers.exe %d %d numbers.txt", atoi(argv[1]), atoi(argv[2]));
    system(command);
  }

  srand(time(NULL));  
  freopen("numbers.txt", "r", stdin);
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);

  clock_t start = clock();

  print_vec(numbers, len);
  bogo_sort(numbers, len);
  print_vec(numbers, len);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  fprintf(stderr, "Tempo de execução: %.6f segundos\n", time_spent);

  free(numbers);

  return 0;
}