#include <stdio.h>
#include <stdlib.h>

int* map(const int ref[], int len, int (*callback)(int)) {
	int *vec = malloc(len*sizeof(int));

	for (int i = 0; i < len; ++i) {	
		vec[i] = callback(ref[i]);
	}

	return vec;
}

int squareN(int n) { return n*n; }

int main() {
	int numbers[] = {1, 2, 3, 4, 5, 6};
	int len = sizeof(numbers)/sizeof(int);
	int *copy = map(numbers, len, squareN);

	for (int i = 0; i < len; ++i) {
		printf("%d\n", copy[i]);
	}

	free(copy);

	return 0;
}