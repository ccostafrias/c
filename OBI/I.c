#include <stdio.h>

int maiorVec(int* nums, int size) {
    int maior = nums[0];
    for (int i = 1; i < size; i++) {
        if (nums[i] > maior) maior = nums[i];
    }

    return maior;
}

int main() {
    int N, T;

    scanf("%d %d", &N, &T);

    int matrix[N][T];

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < T; c++) {
            scanf("%d", &matrix[r][c]);
        }
    }

    int L, U;
    scanf("%d %d", &L, &U);

    // código
    int confTot = 0;
    for (int t = 0; t < T; t++) {
        int confTemp = 0;
        int maiorTemp = matrix[t][0];
        int sensorTemp;
        int tempMin = L;
        for (int n = 1; n < N; n++) {
            tempoMin--;
            if (matrix[t][n] > maiorTemp) {
                maiorTemp = matrix[t][n];
                sensorTemp = n;
            }
        }
    }


    return 0;
}