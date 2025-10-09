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
    // se percorreu tudo e chegou no 0, é porque não cabe
    if (n == 0) return 0;

    // subtrai o item da mochila da capacidade da mochila e arredonda para até 4 casas decimais
    double teste = roundN(k - v[n-1], 4);

    if (teste == 0) return 1; // se não sobrou nada, é porque ele coube certinho
    else if (teste > 0) return cabeMochila(v, n-1, k-v[n-1]) || cabeMochila(v, n-1, k); // se ainda sobrou espaço, ele vai tentar avançar para o próximo item usando a nova capacidade e/ou avançar usando a capacidade anterior
    else return cabeMochila(v, n-1, k); // se ultrapassou a capacidade da mochila, só avança para o próximo
}

int main() {
    float v[] = {3, 2, 4, 3, 2, 4};
    float capacidadeMochila = 5;
    int sizeVec = sizeof(v)/sizeof(v[0]);

    printf("%d", cabeMochila(v, sizeVec, capacidadeMochila));

    return 0;
}