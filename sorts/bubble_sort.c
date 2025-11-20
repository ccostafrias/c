#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int * numbers, int len) {
  int end = len - 1;
  int k, temp, trocou;

  do {
    trocou = 0;
    for (k = 0; k < end; k++) {
      if (numbers[k] > numbers[k+1]) {
        temp = numbers[k+1];
        numbers[k+1] = numbers[k];
        numbers[k] = temp;
        trocou = 1;
      }
    }
    end--;

  } while (trocou);
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
  bubble_sort(numbers, len);
  print_vec(numbers, len);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  fprintf(stderr, "Tempo de execução: %.6f segundos\n", time_spent);

  free(numbers);

  return 0;
}