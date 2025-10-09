#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int exists;
    int belongs;
} Cabe;

void cabeMochila(int S[], int n, int K, Cabe ** P) {
    P[0][0].exists = 1;

    for (int i = 1; i < n; i++) {
        for (int k = 0; k <= K; k++) {
            P[i][k].exists = 0;

            if (P[i-1][k].exists) {
                P[i][k].exists = 1;
                P[i][k].belongs = 1;
            } else {
                if (k-S[i] >= 0 && P[i-1][k-S[i]].exists) {
                    P[i][k].exists = 1;
                    P[i][k].belongs = 1;
                }
            }
        }
    }
}

void initMatrix(Cabe ** P, int n, int K) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= K; k++) {
            P[i][k].exists = 0;
            P[i][k].belongs = 0;
        }
    }
}

void printMatrix(Cabe ** P, int n, int K) {
    for (int i = 0; i < n; i++) {
        // printf("\nLINHA %d\n", i);
        for (int k = 0; k <= K; k++) {
            printf("%d/%d ", P[i][k].exists,  P[i][k].belongs);
        }
        printf("\n");
    }
}

int main() {
    freopen("saida.out", "w", stdout);

    int v[] = {0, 2, 3, 5, 6};
    int sizeMochila = 9;
    int sizeItems = sizeof(v) / sizeof(v[0]);

    Cabe ** matriz = malloc(sizeItems * sizeof(Cabe*));
    for (int i = 0; i < sizeItems; i++)  matriz[i] = malloc((sizeMochila+1) * sizeof(Cabe));

    initMatrix(matriz, sizeItems, sizeMochila);
    cabeMochila(v, sizeItems, sizeMochila, matriz);
    printMatrix(matriz, sizeItems, sizeMochila);

    // LIBERA MEMORIA
    for (int i = 0; i < sizeItems; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}