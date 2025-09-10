#include <stdio.h>
#include <stdlib.h>

double myPow(double x, int n) {
  if (x == 0) return 0;
  else if (n == 0 || x == 1) return 1;
  else {
    double base = x;

    for (int i = 1; i < abs(n); ++i) {
      base *= x;
    }
    
    if (n > 0) return base;
    else return 1.0/base;
  }
}

int main() {
  double x; int n;

  scanf("%lf %d", &x, &n);
  if (x == 0 && n == 0) printf("ERROR! BOTH ZERO");
  printf("%g", myPow(x, n));

  return 0;
}