#include <stdio.h>

int soma() {
  int temp, sum = 0;
  do {
    scanf("%d", &temp);
    sum += temp * (temp != -1);
  } while (temp != -1);

  return sum;
}

int main() {
  printf("SOMA: %d", soma());

  return 0;
}