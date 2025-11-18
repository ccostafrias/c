#include <stdio.h>
#include <stdlib.h>

int find_max(int * numbers, int len) {
  int max = numbers[0];
  for (int i = 1; i < len; i++) {
    if (numbers[i] > max) {
      max = numbers[i];
    }
  }
  return max;
}

// variável global que indica qual dígito estamos ordenando
static int TENZY = 1;

int index_digit(int number) {
    return (number / TENZY) % 10;
}

void counting_place(
    int * numbers,
    int len,
    int *countArray,
    int lenCountArray,
    int (*getIndex)(int)
) {
    int * tempNumbers = (int*) malloc(len * sizeof(int));

    for (int i = 0; i < len; i++) {
        tempNumbers[i] = numbers[i];
        countArray[getIndex(tempNumbers[i])]++;
    }

    for (int i = 1; i < lenCountArray; i++)
        countArray[i] += countArray[i-1];

    for (int i = len - 1; i >= 0; i--) {
        int index = getIndex(tempNumbers[i]);
        int currCount = countArray[index] - 1;

        numbers[currCount] = tempNumbers[i];
        countArray[index]--;
    }

    free(tempNumbers);
}

void radix_sort(int * numbers, int len, int maxNumber) {
    int * buckets = (int*) malloc(10 * sizeof(int));

    for (TENZY = 1; TENZY <= maxNumber; TENZY *= 10) {
        for (int i = 0; i < 10; i++) buckets[i] = 0;
        counting_place(numbers, len, buckets, 10, index_digit);
    }

    free(buckets);
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
  for (int i = 0; i < len; i++) scanf("%d", &numbers[i]);
  int maxNumber = find_max(numbers, len);

  print_vec(numbers, len);
  radix_sort(numbers, len, maxNumber);
  print_vec(numbers, len);

  free(numbers);

  return 0;
}