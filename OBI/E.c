#include <stdio.h>

int gcd(int a, int b) {
    int res;

    while (1) {
        res = a % b;
        if (res == 0) return b;
        a = b;
        b = res;
    }
}

int main() {
    int Y, K, X = 1;
    scanf("%d %d", &Y, &K);

    for (int i = 0; i < K; i++) {
        X += gcd(X, Y);
    }
    
    printf("%d", X);

    return 0;
}