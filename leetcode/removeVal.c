#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int removeElement(int* nums, int numsSize, int val) {
    int elements = 0, s = -1;
    for (int i = 0; i < numsSize; i++) {
        if (s == -1) {
            if (nums[i] == val) {
                s = i;
                elements++;
            }
        } else {
            if (nums[i] != val) {
                nums[s++] = nums[i];
            } else elements++;
        }
    }

    return (numsSize - elements);
}

int main() {
    char linha[1000];
    int nums[100];
    int len = 0, i = 0, element;

    scanf(" %d", &element);
    scanf(" %[^\n]", linha);

    char *token = strtok(linha, " ");

    while (token != NULL) {
        nums[i++] = atoi(token);
        token = strtok(NULL, " ");
        len++;
    }

    // for (int i = 0; i < len; i++) {
    //     printf("%d\n", nums[i]);
    // }

    int lenFixed = removeElement(nums, len, element);

    for (int i = 0; i < lenFixed; i++) {
        printf("%d\n", nums[i]);
    }

    return 0;
}