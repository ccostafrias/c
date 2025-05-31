#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int searchInsert(int* nums, int numsSize, int target) {
    int start = 0, end = numsSize;

    while (start != end) {
        if (end <= -1) return 0;
        int mid = (start+end)/2;
        // printf("START: %d & END: %d & MID: %d\n\n", start, end, mid);
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) start = mid + 1;
        else end = mid;
    }

    return start;
}

int main() {
    char linha[1000];
    int nums[100], len = 0, i = 0, target;

    scanf(" %[^\n]", linha);
    scanf("%d", &target);

    // separar numeros
    char *token = strtok(linha, " ");
    while (token != NULL) {
        nums[i++] = atoi(token);
        token = strtok(NULL, " ");
        len++;
    }

    printf("%d", searchInsert(nums, len, target));

    return 0;
}