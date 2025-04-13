#include <stdio.h>

int main() {
    int num = 5;
    float altura = 1.75;
    double pi = 3.1415926535;
    char letra[] = "sexo";

    printf("%d\n", num);
    printf("%.3f\n", altura);
    printf("%.20lf\n", pi);
    // printf("%c\n", letra[0]);

    int size = sizeof(letra);

    for (int i = 0; i < size-1; i++) {
        printf("%c", letra[i]);
    }

    return 0;
}