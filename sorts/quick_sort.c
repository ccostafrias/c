#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomN(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void swap(int * vec, int iA, int iB) {
  int temp = vec[iB];
  vec[iB] = vec[iA];
  vec[iA] = temp;
}

int partition(int * numbers, int start, int end) {
  int iPivot = randomN(start, end);
  int pivot = numbers[iPivot];
  swap(numbers, iPivot, end);

  int iStart = start, iEnd = end - 1;

  while (iStart <= iEnd) {
    if (numbers[iStart] < pivot) {
      iStart++;
    } else {
      while (iEnd >= iStart && numbers[iEnd] >= pivot) {
        iEnd--;
      }
      if (iStart <= iEnd) {
        swap(numbers, iStart, iEnd);
        iEnd--;
        iStart++;
      }
    }
  }

  swap(numbers, end, iStart);

  return iStart;
}

void quick_sort(int * numbers, int start, int end) {
  if (start >= end) return;

  int mid = partition(numbers, start, end);
  quick_sort(numbers, start, mid - 1);
  quick_sort(numbers, mid + 1, end);
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

  srand(time(NULL));  
  freopen("numbers.txt", "r", stdin);
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);

  clock_t start = clock();

  print_vec(numbers, len);
  quick_sort(numbers, 0, len - 1);
  print_vec(numbers, len);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  fprintf(stderr, "Tempo de execução: %.6f segundos\n", time_spent);

  free(numbers);

  return 0;
}