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

void quick_sort(int * numbers, int start, int end) {
  if (start >= end || end <= start) return;

  int iPivot = randomN(start, end);
  int pivot = numbers[iPivot];
  swap(numbers, iPivot, end);

  int iStart = start, iEnd = end - 1;

  while (iStart <= iEnd) {
    if (numbers[iStart] < pivot) {
      iStart++;
    } else {
      swap(numbers, iStart, iEnd);
      iEnd--;
    }
  }

  swap(numbers, end, iStart);

  quick_sort(numbers, start, iStart - 1);
  quick_sort(numbers, iStart + 1, end);

}

void print_vec(int * vec, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}


int main() {
  srand(time(NULL));
  freopen("numbers.txt", "r", stdin);
  
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);

  print_vec(numbers, len);
  quick_sort(numbers, 0, len - 1);
  print_vec(numbers, len);

  free(numbers);

  return 0;
}