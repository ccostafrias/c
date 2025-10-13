#include <stdio.h>

int max_segmento(int * vec, int size) {
  int maxActual = 1;
  int maxSufix = 1;

  for (int i = 0; i < size-1; i++) {
    if (vec[i] == vec[i+1]) {
      maxActual++;
      if (maxActual > maxSufix) {
        maxSufix = maxActual;
      }
    } else {
      maxActual = 1;
    }
  }

  return maxSufix;
}

int main() {
  int vec[] = {0, 1, 1, 2, 3, 4, 5};
  int size = sizeof(vec)/sizeof(vec[0]);
  printf("SEGMENTO MAX: %d", max_segmento(vec, size));

  return 0;
}