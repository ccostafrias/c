#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int cap = 2;

void fib(int n, long long int** seq, int* len) {
    if (*len >= n) return;

    if (*len >= cap) {
        cap *= 2;
        long long int* temp = realloc(*seq, cap * sizeof(long long int));
        if (temp == NULL) {
            perror("Erro ao realocar memória");
            free(*seq);
            exit(EXIT_FAILURE);
        }
        *seq = temp; 
    }
    (*seq)[(*len)] = (*seq)[(*len)-1] + (*seq)[(*len)-2];
    (*len)++;
    fib(n, seq, len);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    long long int* nums = malloc(cap*sizeof(long long int));
    int n, len = 2;
    nums[0] = 1;
    nums[1] = 1;


    scanf("%d", &n);

    fib(n, &nums, &len);

    printf("Sequência de Fibonacci até o a%d: \n", n);
    for (int i = 0; i < len; i++) {
        printf("%lld ", nums[i]);
    }

    if (n > 1) printf("\nAproximação para o número áureo: %g\n", (double)nums[len-1]/nums[len-2]);

    free(nums);

    return 0;
}