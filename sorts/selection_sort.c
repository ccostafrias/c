#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int * numbers, int iA, int iB) {
  if (iA == iB) return;
  
  int temp = numbers[iB];
  numbers[iB] = numbers[iA];
  numbers[iA] = temp;
}

void selection_sort(int * numbers, int len) {
  int i, j;
  int indexMin;

  for (i = 0; i < len; i++) {
    indexMin = numbers[i];
    for (j = i; j < len; j++) {
      if (numbers[j] < numbers[indexMin]) indexMin = j;
    }
    swap(numbers, i, indexMin);
  }
}

void print_vec(int * vec, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}


int main(int argc, char * argv[]) {
  srand(time(NULL));
  
  if (argc == 3) {
    char command[128];
    sprintf(command, "random_numbers.exe %d %d numbers.txt", atoi(argv[1]), atoi(argv[2]));
    system(command);
  }

  freopen("numbers.txt", "r", stdin);
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);

  clock_t start = clock();

  print_vec(numbers, len);
  selection_sort(numbers, len);
  print_vec(numbers, len);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  fprintf(stderr, "Tempo de execução: %.6f segundos\n", time_spent);

  free(numbers);

  return 0;
}