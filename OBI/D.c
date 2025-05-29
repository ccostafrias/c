#include <stdio.h>
#include <stdlib.h>

int main() {
    int len;
    
    scanf("%d", &len);

    char *S = malloc(len*sizeof(char)+1);
    char *T = malloc(len*sizeof(char)+1);

    scanf("%s %s", S, T);
    
    float numerador, denominador;

    for (int i = 0; i < len; i++) {
        if (S[i] == '*') denominador++;
        if (S[i] != T[i]) numerador++;
    }

    printf("%.2f", (numerador/denominador));

    return 0;
}