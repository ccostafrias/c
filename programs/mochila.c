#include <stdio.h>
#include <math.h>

typedef unsigned short int bool;

float roundN(float n, int k) {
    float tenzy = pow(10, k);
    float t = n*tenzy;
    t = round(t);
    t /= tenzy;
    return t; 
}

bool cabeMochila(float v[], int n, float k) {
    if (n == 0) return 0;

    double teste = roundN(k - v[n-1], 4);

    if (teste == 0) return 1;
    else if (teste > 0) return cabeMochila(v, n-1, k-v[n-1]) || cabeMochila(v, n-1, k);
    else return cabeMochila(v, n-1, k);
}

int main() {
    float v[] = {3, 2, 4, 3, 2, 4};
    float sizeMochila = 5;
    int sizeVec = sizeof(v)/sizeof(v[0]);

    printf("%d", cabeMochila(v, sizeVec, sizeMochila));

    return 0;
}