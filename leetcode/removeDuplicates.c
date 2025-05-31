#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    int duplicates = 0;
    int s = 0;
    for (int i = 1; i < numsSize; i++) {
        if (s == 0) {
            if (nums[i] == nums[i-1]) {
                s = i;
                duplicates++;
            }
        } else {
            if (nums[i] != nums[s] && nums[i] != nums[i-1]) {
                nums[s++] = nums[i];
            } else duplicates++;
        }
    }

    return (numsSize - duplicates);
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

    // for (int i = 0; i < len; i++) {
    //     printf("%d\n", nums[i]);
    // }

    int lenFixed = removeDuplicates(nums, len);

    for (int i = 0; i < lenFixed; i++) {
        printf("%d\n", nums[i]);
    }

    return 0;
}