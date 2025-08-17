#include <stdio.h>
#include <locale.h>

#define MIN(a, b) ((a < b) ? a : b)

int find(int v[], int x, int ini, int fim) {
    if (fim == ini) return -1;

    if (v[fim-1] == x) return fim-1;

    return find(v, x, ini, fim-1);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    int v[] = {0, 5, 2, 10, 8, 5, -2, 1};
    int size = sizeof(v)/sizeof(v[0]);
    int x, ini, fim;

    printf("Número a achar, início e fim: \n");
    scanf("%d %d %d", &x, &ini, &fim);

    // printf("%d", MIN(fim, size));
    printf("Index de %d: %d\n", x, find(v, x, ini, MIN(fim, size)));

    return 0;
}