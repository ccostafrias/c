#include <stdio.h>

void print_vec(int *vec, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}

void insert(int * vec, int k) {
  int el = vec[k];
  int i = k - 1;

  while (i >= 0 && vec[i] > el) {
    vec[i + 1] = vec[i];
    i--;
  }

  vec[i + 1] = el;
}

void insertion_sort(int * vec, int size) {
  for (int k = 1; k < size; k++) {
    insert(vec, k);
  }
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
  insertion_sort(numbers, len);
  print_vec(numbers, len);

  return 0;
}