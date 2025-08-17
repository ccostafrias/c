#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* invertVec(int* nums, int size) {
    int* inv = malloc(size*sizeof(int));
    for (int i = 0; i < size/2; i++) {
        inv[size-(i+1)] = nums[i];
        inv[i] = nums[size-(i+1)];
    }
    if (size % 2 == 1) inv[size/2] = nums[size/2];

    return inv;

}

int main() {
    char linha[1000];
    int nums[100], len = 0, i = 0;

    scanf(" %[^\n]", linha);

    char *token = strtok(linha, " ");

    while (token != NULL) {
        nums[i++] = atoi(token);
        token = strtok(NULL, " ");
        len++;
    }

    int* inv = invertVec(nums, len);
    
    for (int i = 0; i < len; i++) {
        printf("%d ", inv[i]);
    }

    free(inv);

    return 0;
}