#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

long long int N = 10000;

double abs_value(double a) { return a < 0 ? -a : a; }

double pi_aprox(int max) {
  double sum = 0;
  
  for (int i = 1; i < max; i++) {
    sum += sqrt((max+i)*(max-i));
  }
  
  sum = 4*sum/(max*max);

  return sum;
}

int decimals(double diff, int count) {
  if ((int)diff != 0) return count;

  return decimals(diff*10, count+1);
}

int main() {
  double fakePI = pi_aprox(N);
  double diff = abs_value(PI-fakePI);
  int casasDecimais = decimals(diff, 0);

  printf("REAL PI: %lf\n", PI);
  printf("FAKE PI: %lf\n", fakePI);
  printf("DIFF: %lf\n", diff);
  printf("ERRO: %d casas decimais\n", casasDecimais);

  return 0;
} 