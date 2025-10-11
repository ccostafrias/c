#include <stdio.h>

typedef float Elemento;

Elemento modulo(Elemento n) { return n < 0 ? -n : n; }
Elemento max(Elemento a, Elemento b) { return a > b ? a : b; }
Elemento min(Elemento a, Elemento b) { return a < b ? a : b; }
int teto(Elemento n) {
  return n+1; 
}

int main() {
  Elemento n;
  scanf("%f", &n);

  printf("teto(%g) = %d", n, teto(n));

  return 0;
}