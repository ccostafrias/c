#include <stdio.h>

int soma(int * vec, int start, int end, int sum) {
  if (start >= end) return sum;
  int actual = vec[start];

  if (actual > 0 && actual < 10) return soma(vec, start+1, end, sum+actual);
  return soma(vec, start+1, end, sum);
}

int main() {
  int vec[] = {0, 11, 1, 8, 4, 39};
  int size = sizeof(vec)/sizeof(vec[0]);
  printf("SOMA: %d", soma(vec, 0, size, 0));

  return 0;
}