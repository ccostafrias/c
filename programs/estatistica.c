#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h> //biblioteca para o tempo
#include <stdlib.h> //biblioteca para o rand()
#include <ctype.h>

int randomN(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int lenVec(float *arr) {
	int len = 0, k = 0;
	while (1) {
		if (arr[k] == -1) break;
		k++;
		len++;
	}
	return len;
}

void sort(float* arr, int len) {
	for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

float mediana(float *arr, int len) {
    if (len % 2) return arr[(len/2)];

    return ((float)arr[(len/2)-1]+(float)arr[(len/2)])/2;
}

float med(float *arr, int len) {
	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	return (sum/len);
}

float var(float *arr, int len) {
	float media = med(arr, len);

	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += pow((arr[i] - media), 2);
	}
	return (sum/len);
}

float sd(float *arr, int len) {
	return sqrt(var(arr, len));
}

float mad(float *arr, int len) {
	float sum = 0, media = med(arr, len);
	for (int i = 0; i < len; i++) {
		float num = arr[i] - media;
		if (num < 0) num *= -1;
		sum += num;
	}
	return sum/len;
}

float min(float *arr, int len) {
	float minimum = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] < minimum) minimum = arr[i];
	}

	return minimum;
}

float max(float *arr, int len) {
	float maximum = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] > maximum) maximum = arr[i];
	}

	return maximum;
}

float betweenSd(float* nums, int len) {
	float media = med(nums, len);
	float standart = sd(nums, len);
	float min = media - standart;
	float max = media + standart;
	float between = 0;

	for (int i = 0; i < len; i++) {
		if (nums[i] >= min && nums[i] <= max) between++;
	}

	return ((between/len)*100);
}

float betweenLimits(float* nums, int len, float LI, float LS) {
	int between = 0;

	for (int i = 0; i < len; i++) {
		if (nums[i] >= LI && nums[i] <= LS) between++;
	}

	return ((between/len) * 100);
}

float moda(float *arr, int len) {
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

float quantil(float* nums, float p, int size) {
	int k = p*(size+1);
	float alpha = p*(size+1)-k;
	float n0 = k != 0 ? nums[k-1] : nums[0];
	float n1 = k != size ? nums[k] : nums[size-1];
	float q = n0 + alpha*(n1-n0);

	return q;
}

void addNum(float *arr, float v, int w, int *k) {
	int start = *k;
	while (*k < (start + w)) {
		arr[*k] = v;
		(*k)++;
	}
}

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int main () {
	srand(time(NULL)); 

	setlocale(LC_ALL, "Portuguese_Brazil");

	cleanScreen();
	
	float numbers[1000];
	int k = 0, len = 0;
	int debug = 1;

	printf("CALCULADORA ESTATÍSTICA\n");

	if (!debug) {
		char ans;
		printf("USAR PESOS? (S/N) ");
		scanf(" %c", &ans);
		ans = toupper(ans);

		while (1) {
			int weight = 1;
			float value;
			printf("Digite um número (-1) para parar: ");
			scanf(" %f", &value);
			if (value == -1.0) break;
			if (ans == 'S') {
				printf("Respectivo peso: ");
				scanf(" %d", &weight);
			}
			addNum(numbers, value, weight, &k);
		}
	} else {
		int size = 100;
		for (int i = 0; i < size; i++) {
			numbers[i] = randomN(1, size);  
		}
		numbers[size] = -1;
		printf("NÚMEROS: \n");
		for (int i = 0; i < size; i++) {
			printf("%g ", numbers[i]);
			k++;
		}
		printf("\n");
	}
	len = k;

	sort(numbers, len);
	float media = med(numbers, len);
	float standart = sd(numbers, len);
	float modah = moda(numbers, len);
	float q1 = quantil(numbers, 0.25, len);
	float q3 = quantil(numbers, 0.75, len);
	float IQR = q3 - q1;
	float LI = q1 - (1.5*IQR);
	float LS = q3 + (1.5*IQR);

	printf("\n");
	printf("TAMANHO DA AMOSTRA: %d\n", len);
	printf("X(1): %g\n", min(numbers, len));
	printf("Q1%%: %g\n", q1);
	printf("MEDIANA: %g\n", mediana(numbers, len));
	printf("Q3%%: %g\n", q3);
	printf("X(%d): %g\n", len, max(numbers, len));
	printf("DENTRO DOS LIMITES (%g; %g): %g%%\n", LI, LS, betweenLimits(numbers, len, LI, LS));
	printf("AMPLITUDE: %g\n", (max(numbers, len) - min(numbers, len)));
	printf("MÉDIA: %g\n", media);
	if (modah != -1) printf("MODA: %g\n", modah);
	printf("VARIÂNCIA: %g\n", var(numbers, len));
	printf("DESVIO PADRÃO: %g\n", standart);
	printf("DESVIO MÉDIO: %g\n", mad(numbers, len));
	printf("DADOS NO INTERVALO (%g; %g): %g%%\n", media - standart, media + standart, betweenSd(numbers, len));
	printf("\nFIM\n");

	return 0;
}