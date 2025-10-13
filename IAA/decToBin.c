#include <stdio.h>
#include <stdlib.h>

int * fill_bin(int num, int * count) {
  int power = 1;

  while (power*2 <= num) {
    power *= 2;
    (*count)++;
  }

  int * vec = malloc((*count) * sizeof(int));

  for (int i = 0; i < (*count); i ++) {
    if (power > num) {
      vec[i] = 0;
    }
    else {
      vec[i] = 1;
      num -= power;
    }
    power /= 2;
  }

  return vec;
}

void print_vec(int * vec, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", vec[i]);
  }
  printf("\n");
}

int main() {

  int num; scanf("%d", &num);
  int count = 1;
  int * vec = fill_bin(num, &count);
  // printf("COUNT: %d\n", count);

  print_vec(vec, count);

  return 0;
}