#include <stdio.h>
#include <locale.h>

double fatorial(int n) {
	if (n == 0) return 1;
	int fat = n;
	for (int i = n - 1; i > 1; i--) {
		fat *= i;
	}

	return fat;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

	int depth;
	while (1) {
		printf("Escolha a precisão: ");
		scanf("%d", &depth);

		if (depth > 0) break;
	}

	//precisão máxima = 33
	double euler = 0;
	for (int i = 0; i <= depth; i++) {
		//famosa expansão de Taylor
		double sum = (1.0/fatorial(i));
		euler += sum;
	};
	printf("Número de Euler = %lf\n", euler);

	return 0;
}