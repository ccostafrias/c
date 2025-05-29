#include <stdio.h>

int main() {
    int C, G;

    scanf("%d %d", &C, &G);

    // aberta
    if (C == 0) {
        if (G == 0) printf("morto");
        else if (G == 1) printf("vivo");
    } else if (C == 1) {
        printf("vivo e morto");
    }

    return 0;
}