#include <stdio.h>
#include <limits.h>
#include <math.h>

double myPow(double x, int n) {
  if (x == 0) {
    if (n == 0) return 1;
    else if (n > 0) return 0;
    else return NAN;
  } else if (n == 0 || x == 1) return 1;
  else if (n < 0) {
    if (n == INT_MIN) return myPow(1.0/x, -(n+1)) * 1.0/x;
    else return myPow(1.0/x, -n);
  }
  else {
    if (n % 2 == 0) {
        double newPow = myPow(x, n/2);
        return newPow*newPow;
    } else {
        double newPow = myPow(x, n/2);
        return newPow*newPow*x;
    }
  }
}

int main() {
  double x; int n;
  scanf("%lf %d", &x, &n);

  printf("%g", myPow(x, n));

  return 0;
}