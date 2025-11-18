#include <stdio.h>
#include <stdlib.h>

void merge(int numbers[], int start, int mid, int end) {
  int lenLeft = mid - start + 1, lenRight = end - mid;
  int iLeft = 0, iRight = 0, iFinal = start;

  int * left = (int*) malloc(lenLeft * sizeof(int));
  int * right = (int*) malloc(lenRight * sizeof(int));

  for (int i = 0; i < lenLeft; i++)
    left[i] = numbers[start + i];

  for (int i = 0; i < lenRight; i++)
    right[i] = numbers[mid + 1 + i];

  while (iLeft < lenLeft && iRight < lenRight) {
    if (left[iLeft] < right[iRight]) {
      numbers[iFinal++] = left[iLeft++];

    } else {
      numbers[iFinal++] = right[iRight++];

    }
  }

  while (iLeft < lenLeft)
    numbers[iFinal++] = left[iLeft++];

  while (iRight < lenRight)
    numbers[iFinal++] = right[iRight++];

  free(left);
  free(right);
}

void merge_sort(int * numbers, int start, int end) {
  if (start >= end) {
    return;
  }

  int mid = (start + end) / 2;
  merge_sort(numbers, start, mid);
  merge_sort(numbers, mid+1, end);

  merge(numbers, start, mid, end);
}

void print_vec(int * vec, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");
}

int main() {
  freopen("numbers.txt", "r", stdin);
  
  int len; scanf("%d", &len);
  int * numbers = (int*) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    scanf("%d", &numbers[i]);
  }

  print_vec(numbers, len);
  merge_sort(numbers, 0, len-1);
  print_vec(numbers, len);

  free(numbers);

  return 0;
}