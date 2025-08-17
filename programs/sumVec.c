#include <stdio.h>
#include <locale.h>

int sumVec(int v[], int index, int sum) {
    if (index == 0) return sum;

    int value = v[index-1];
    if (value >= 0) sum += value;
    return sumVec(v, index-1, sum);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    int v[] = {-1, -1, -1, -2};
    int s = sizeof(v)/sizeof(v[0]);

    printf("Soma de v: %d\n", sumVec(v, s, 0));

    return 0;
}