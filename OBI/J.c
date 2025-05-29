#include <stdio.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int A[N];
    int B[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        int c = i, ref = A[c];
        while (1) {
            if (ref <= A[c]) {
                ref += K;
                c = ((c+1) % N);
            } else {
                B[i] = (c + 1);
                break;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", B[i]);
    }

    return 0;
}