#include <stdio.h>

float subMax(float v[], int n) {
    float globalMax = 0;
    float sufixMax = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] + sufixMax > globalMax) {
            sufixMax += v[i];
            globalMax = sufixMax;
        } else {
            if (v[i] + sufixMax > 0) {
                sufixMax += v[i];
            } else {
                sufixMax = 0;
            }
        }
    }

    return globalMax;
}

int main() {
    float v[] = {2, -3, 1.5, -1, 3, -2, -3, 3};
    int size = sizeof(v)/sizeof(v[0]);

    printf("%g", subMax(v, size));


    return 0;
}