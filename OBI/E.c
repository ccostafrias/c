#include <stdio.h>

long int gcd(long int a, long int b) {
    long int res;

    while (1) {
        res = a % b;
        if (res == 0) return b;
        a = b;
        b = res;
    }
}

int main() {
    long int Y, K, X = 1;
    scanf("%ld %ld", &Y, &K);

    for (int i = 0; i < K; i++) {
        X += gcd(X, Y);
    }
    
    printf("%ld", X);

    return 0;
}