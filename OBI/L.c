#include <stdio.h>
#include <math.h>

double logbase(double a, double base) {
   return log(a) / log(base);
}

int main() {
    int memoryMB;

    scanf("%d", &memoryMB);
    int memoryb = memoryMB * 8000000;

    double result;

    result = logbase(memoryb, 2);
    int result2 = ceil(result);

    printf("%d", result2);

    return 0;
}