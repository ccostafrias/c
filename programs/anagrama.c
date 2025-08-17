#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MIN(a, b) ((a < b) ? a : b)

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void removeArr(char *arr, int c, int *len) {
	//a partir do �ndice recebido, todos os elementos ser�o deslocados para a esquerda
	for (int i = c; i < *len - 1; ++i) {
		arr[i] = arr[i+1];
	}

	//diminui o tamanho do vetor
	(*len)--;
	//acrescenta o d�gito que finaliza a string
	arr[*len] = '\0';
}

void ordenar(char *arr, char *ordened) {
	int size = strlen(arr);
	int k = 0;

	while (size > 0) {
		int min, c = 0;
		for (int i = 0; i < size; i++) {
			//retornar� o valor em ASCII, para que possamos comparar
			//ex: 65 (A) � menor que 74 (J)
			//% 32 � necess�rio pois entre o 'A' (65) e o 'a' (97) h� 32 caracteres
			int realLetter = (arr[i] - 'A') % 32;
			//como � o in�cio do looping, a primeira letra acaba sendo a menor
			if (i == 0) min = realLetter;
			else {
				min = MIN(min, realLetter);
				//c ser� definido como o �ndice onde foi achada a menor letra
				if (min == realLetter) c = i;
			}
		}

		//k servir� como um contador para ordenar toda menor letra que vier do loop
		ordened[k] = arr[c];
		//a menor letra ser� removida da arr de refer�ncia
		removeArr(arr, c, &size);
		k++;
	}

	ordened[k] = '\0'; // como � um vetor muito longo, finalizamos ele com '\0'
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

	char **words;

	//aloca espa�o na mem�ria para dois vetores (char *)
	words = (char **)malloc(2*sizeof(char *));

	//cada vetor (char *) alocar� espa�o na mem�ria para 100 d�gitos (char)
	words[0] = (char *)malloc(100*sizeof(char));
	words[1] = (char *)malloc(100*sizeof(char));

	cleanScreen();
	printf("VERIFICADOR DE ANAGRAMAS\n");

	printf("Digite a primeira palavra: ");
	//*words = words[0]
	scanf("%s", *words);

	printf("Digite a segunda palavra: ");
	//*(words+1) = words[1]
	scanf("%s", *(words+1));

	int size1 = strlen(words[0]);
	char word1Ref[size1], word1Ordened[size1];
	//copiar em 1ref o vetor words[0], para n�o modific�-lo diretamente
	strcpy(word1Ref, words[0]);

	int size2 = strlen(words[1]);
	char word2Ref[size2], word2Ordened[size2];
	//copiar em 2ref o vetor words[1], para n�o modific�-lo diretamente
	strcpy(word2Ref, words[1]);

	ordenar(word1Ref, word1Ordened);
	ordenar(word2Ref, word2Ordened);

	if (strcmp(word1Ordened, word2Ordened) == 0) {
		printf("\n%s e %s s�o anagramas entre si!\n", words[0], words[1]);
	} else {
		printf("\n%s e %s n�o s�o anagramas entre si...\n", words[0], words[1]);
	}

	printf("\nFIM\n");

	return 0;
}