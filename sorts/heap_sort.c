#include <stdio.h>
#include <stdlib.h>

void swap(int * vec, int iA, int iB) {
  if (iA == iB) return;
  
  int temp = vec[iB];
  vec[iB] = vec[iA];
  vec[iA] = temp;
}

void heapify(int * numbers, int last, int parent) {
  int left = 2*parent + 1;
  int right = left + 1;
  int max = parent;

  if (left <= last && numbers[left] > numbers[max])
    max = left;
    
  if (right <= last && numbers[right] > numbers[max])
    max = right;

  if (max != parent) {
    swap(numbers, parent, max);
    heapify(numbers, last, max);
  }

}

void build_max_heap(int * numbers, int last) {
  for (int index = (last - 1)/2; index >= 0; index--) {
    heapify(numbers, last, index);
  }
}

void heapsort(int * numbers, int last) {
  build_max_heap(numbers, last);

  for (int newLast = last; newLast > 0; newLast--) {
    swap(numbers, 0, newLast);
    heapify(numbers, newLast-1, 0);
  }
}

void print_vec(int * vec, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}


int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Insira a quantidade de números e o limite!");
    return 1;
  }

  char command[128];
  sprintf(command, "random_numbers.exe %d %d numbers.txt", atoi(argv[1]), atoi(argv[2]));
  system(command);

  freopen("numbers.txt", "r", stdin);
  
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);

  print_vec(numbers, len);
  heapsort(numbers, len-1);
  print_vec(numbers, len);

  free(numbers);

  return 0;
}