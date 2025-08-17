#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <stdlib.h>

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int isPrimo(int n, int size, int primos[]) {
	for (int i = 0; i < size && primos[i] <= sqrt(n); i++) {
		if (n % (primos[i]) == 0) return 0;
	}

	return 1;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
	int *primos;
	int n, sizePrimos = 1;

	cleanScreen();
	printf("PRIMOS AT� N\n");

	do {
		printf("At� que n�mero deseja verificar? ");
		scanf("%d", &n);
	} while (n < 2);

	//malloc() retonar um ponteiro genérico, por isso convertermos para um ponteiro int
	primos = (int *)malloc(sizeof(int));
	primos[0] = 2;

	//para cada n�mero a partir do 2, verificaremos se ele é primo ou não
	for (int i = 3; i <= n; i++) {
		if(isPrimo(i, sizePrimos, primos)) {
			// para cada novo valor adicinado, aumentado o valor do vetor em 4 bytes (valor de 1 int)
            // É EXTREMAMENTE necess�rio primeiro aumetnar o tamanho do VETOR para depois adicionar o valor
			primos = (int *)realloc(primos, (sizePrimos+1)*sizeof(int));
			// se for primo, será adicionado ao vetor para ajudar na verificacão dos próximos números, otimizando o processo
            // logo após adicionar, é preciso aumentar o tamanho do sizePrimos
			primos[sizePrimos++] = i;
		}
	}

	cleanScreen();
	printf("Primos at� %d: \n", n);

	for (int i = 0; i < sizePrimos; i++) {
		printf("%d ", primos[i]);
	}

	printf("\nTotal de primos: %d\n", sizePrimos);

	free(primos);

	return 0;
}