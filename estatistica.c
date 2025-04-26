#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h> //biblioteca para o tempo
#include <stdlib.h> //biblioteca para o rand()

int randomN(int min, int max) {
    return rand() % (max - min + 1) + min;
}

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

float mad(int *arr, int len) {
	float sum = 0, media = med(arr, len);
	for (int i = 0; i < len; i++) {
		float num = arr[i] - media;
		if (num < 0) num *= -1;
		sum += num;
	}
	return sum/len;
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

float moda(int *arr, int len) {
	float actualModa = -1;
	int maxTimes = 1;
	for (int i = 0; i < len; i++) {
		int times = 0;
        for (int j = i; j < len; j++) {
            if (arr[i] == arr[j]) {
            	times++;
            }
        }
        if (times > maxTimes) {
        	maxTimes = times;
        	actualModa = arr[i];
        }
    }
    return actualModa;
}

int main () {
	srand(time(NULL)); 

	setlocale(LC_ALL, "Portuguese_Brazil");
	
	int numbers[1000], k = 0, len = 0;
	int debug = 1;
	printf("CALCULADORA ESTATÍSTICA\n");
	if (!debug) {
		while (1) {
			printf("Digite um número (-1) para parar: ");
			scanf(" %d", &numbers[k]);
			if (numbers[k++] == -1) break;
		}
	} else {
		int size = 100;
		for (int i = 0; i < size; i++) {
			numbers[i] = randomN(1, size);  
		}
		numbers[size] = -1;
		printf("NÚMEROS: \n");
		for (int i = 0; i < size; i++) {
			printf("%d ", numbers[i]);
		}
		printf("\n");
	}
	len = lenVec(numbers);

	float media = med(numbers, len);
	float standart = sd(numbers, len);
	float modah = moda(numbers, len);

	printf("\n");
	printf("TAMANHO DA AMOSTRA: %d\n", len);
	printf("MÉDIA: %g\n", media);
	printf("MEDIANA: %g\n", mediana(numbers, len));
	// if (modah == -1) printf("MODA: não há moda\n");
	if (modah != -1) printf("MODA: %g\n", modah);
	printf("AMPLITUDE: %g\n", (max(numbers, len) - min(numbers, len)));
	printf("VARIÂNCIA: %g\n", var(numbers, len));
	printf("DESVIO PADRÃO: %g\n", standart);
	printf("DESVIO MÉDIO: %g\n", mad(numbers, len));
	printf("DADOS NO INTERVALO (%g; %g): %g%%\n", media - standart, media + standart, betweenSd(numbers, len));
	printf("\nFIM\n");

	return 0;
}