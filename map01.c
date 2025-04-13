#include <stdio.h>

void map(int vec[], int len, int (*callback)(int)) {
	for (int i = 0; i < len; ++i) {	
		vec[i] = callback(vec[i]);
	}
}

void copyVec(int orig[], int dest[], int len) {
	for (int i = 0; i < len; ++i) {
		dest[i] = orig[i];
	}
}

int squareN(int n) { return n*n; }

int main() {
	int numbers[] = {1, 2, 3, 4, 5, 6};
	int len = sizeof(numbers)/sizeof(int);
	int copy[len];

	copyVec(numbers, copy, len);
	map(copy, len, squareN);

	for (int i = 0; i < len; ++i) {
		printf("%d\n", copy[i]);
	}

	return 0;
}