#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

	int depth = 35;
	// while (1) {
	// 	printf("Escolha a precis�o: ");
	// 	scanf("%d", &depth);

	// 	if (depth > 0) break;
	// }

	long double euler = 0.0L, fat = 1.0L;
	for (int i = 0; i <= depth; i++) {
		//famosa expans�o de Taylor
		if (i > 0) fat *= i;
		euler += 1.0L / fat;
	}
	
	printf("N�mero de Euler = %.16lf\n", (double)euler);

	return 0;
}