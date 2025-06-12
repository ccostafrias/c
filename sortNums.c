#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sortNums(int* nums, int size) {
    for (int i = 0; i < size; i++) {
        for (int c = i + 1; c < size; c++) {
            if (nums[c] >= nums[i]) continue;
            int temp = nums[c];
            nums[c] = nums[i];
            nums[i] = temp;
        }
    }
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

    sortNums(nums, len);
    
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}