#include <stdio.h>
#include <math.h>
#include <locale.h>

int lenVec(int *arr) {
	int len = 0, k = 0;
	while (1) {
		if (arr[k] == -1) break;
		k++;
		len++;
	}
	return len;
}

float mediana(int *arr, int len) {
	for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if (len % 2) {
    	return arr[(len/2)];
    } else {
    	return ((float)arr[(len/2)-1]+(float)arr[(len/2)])/2;
    }
}

float med(int *arr, int len) {
	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	return (sum/len);
}

float var(int *arr, int len) {
	float media = med(arr, len);

	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += pow((arr[i] - media), 2);
	}
	return (sum/len);
}

float sd(int *arr, int len) {
	return sqrt(var(arr, len));
}

float min(int *arr, int len) {
	float minimum = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] < minimum) minimum = arr[i];
	}

	return minimum;
}

float max(int *arr, int len) {
	float maximum = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] > maximum) maximum = arr[i];
	}

	return maximum;
}

float betweenSd(int *arr, int len) {
	float media = med(arr, len);
	float standart = sd(arr, len);
	float min = media - standart;
	float max = media + standart;
	float between = 0;

	for (int i = 0; i < len; i++) {
		if (arr[i] >= min && arr[i] <= max) between++;
	}

	return ((between/len)*100);

}

int main () {
    setlocale(LC_ALL, "Portuguese_Brazil");

	int numbers[100], k = 0, len = 0;
	printf("CALCULADORA ESTATÍSTICA\n");
	while (1) {
		printf("Digite um número (-1) para parar: ");
		scanf(" %d", &numbers[k]);
		if (numbers[k++] == -1) break;
	}
	len = lenVec(numbers);

	float media = med(numbers, len);
	float standart = sd(numbers, len);

	printf("\n");
	printf("MÉDIA: %g\n", media);
	printf("MEDIANA: %g\n", mediana(numbers, len));
	printf("AMPLITUDE: %g\n", (max(numbers, len) - min(numbers, len)));
	printf("VARIÂNCIA: %g\n", var(numbers, len));
	printf("DESVIO PADRÃO: %g\n", standart);
	printf("DADOS NO INTERVALO (%g; %g): %g%%\n", media - standart, media + standart, betweenSd(numbers, len));

	return 0;
}