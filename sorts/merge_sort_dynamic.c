#include <stdio.h>
#include <stdlib.h>

int * merge_sort(const int numbers[], int start, int end) {
  int len = end - start + 1;
  int * finalNumbers = (int*) malloc(len * sizeof(int));

  if (len == 1) {
    finalNumbers[0] = numbers[start];
    return finalNumbers;
  }

  int mid = (start + end) / 2;
  int * left = merge_sort(numbers, start, mid);
  int * right = merge_sort(numbers, mid+1, end);

  int lenLeft = mid - start + 1, lenRight = end - mid;
  int iLeft = 0, iRight = 0, iFinal = 0;

  while (iFinal != len) {
    if (iLeft >= lenLeft) {
      finalNumbers[iFinal] = right[iRight++];
    } else if (iRight >= lenRight) {
      finalNumbers[iFinal] = left[iLeft++];
    } else if (left[iLeft] < right[iRight]) {
      finalNumbers[iFinal] = left[iLeft++];
    } else {
      finalNumbers[iFinal] = right[iRight++];
    }
    
    iFinal++;
  }

  free(left);
  free(right);

  return finalNumbers;
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

  int * merged = merge_sort(numbers, 0, len-1);

  print_vec(numbers, len);
  print_vec(merged, len);

  free(numbers);
  free(merged);

  return 0;
}