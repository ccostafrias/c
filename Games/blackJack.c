#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int randomN(int min, int max) {
    return rand() % (max - min) + min;
}

void removeFrom(char **vec, const char *toRemove, int *len) {
	int start = 0;
	for (int i = 0; i < *len - 1; i++) {
		int isEqual = strcmp(vec[i], toRemove) == 0;

		if (isEqual && !start) start = 1;
		if (start) vec[i] = vec[i+1];
	}
	(*len)--; //diminui manualmente o tamanho do vetor
	vec[*len] = NULL; //limpa o que antes era o último elemento
}

char *randomCard(char **vec, int *len) {
	int index = randomN(0, *len);
	char *card = strdup(vec[index]);
	removeFrom(vec, vec[index], len);
	return card;
}

int contar(char **vec, char **ref, int len) {
	int aces = 0, sum = 0;
	for (int i = 0; i < len; i++) {
		if (vec[i] == NULL) continue;
		if (strcmp(vec[i], "A") == 0) {
			aces++;
			continue;
		}

		for (int c = 0; c < 13; c++) {
			if (strcmp(vec[i], ref[c]) == 0) {
				sum += (c >= 10) ? 10 : (c + 1);
				break;
			}
		}
	}
	for (int i = 0; i < aces; i++) {
		sum += (sum + 11 > 21) ? 1 : 11;
	}

	return sum;
}

void printCard(char **bot, char **player, int lenP, int lenB, char **cartas, int isRevealed) {
	printf("Cartas da máquina: ");
	if (!isRevealed) {
		printf("%s ? ", bot[0]);
		printf("\nPontuação do bot: %d+?\n", contar(bot, cartas, lenB-1));
	}
	else {
		for (int i = 0; i < lenB; i++) {
			printf("%s ", bot[i]);
		}
		printf("\nPontuação do bot: %d\n", contar(bot, cartas, lenB));
	}

	printf("\nSuas cartas: ");
	for (int i = 0; i < lenP; i++) {
		printf("%s ", player[i]);
	}
	printf("\nPontuação: %d", contar(player, cartas, lenP));
}

void checkWin(int pointsBot, int pointsPlayer) {
	printf("\n\n");
	if (pointsBot == 21){
		printf("Blackjack! A máquina pontuou exatamente 21!\n");
		printf("Você perdeu...");
	} else if (pointsBot > 21) {
		printf("A máquina estourou!\n");
		printf("Você ganhou!!!");
	} else if (pointsPlayer == 21){
		printf("Blackjack! Você pontuou exatamente 21!\n");
		printf("Você ganhou!!!");
	} else if (pointsPlayer > 21) {
		printf("PUTZ! Parece que você ultrapassou 21...\n");
		printf("Você perdeu...");
	} else if (pointsPlayer < pointsBot) {
		printf("A máquina te superou...\n");
		printf("Você perdeu...");
	} else if (pointsPlayer > pointsBot) {
		printf("Você superou a máquina!\n");
		printf("Você ganhou!!!");
	} else {
		printf("Ambos pontuaram %d!\n", pointsBot);
		printf("Vocês empataram!!!");
	}
}

void title() { printf("----BLACK JACK----\n\n"); }

int main() {
	setlocale(LC_ALL, "Portuguese_Brazil");

	srand(time(NULL));  // Define a semente baseada no tempo atual

	int len = 52;
	char *deck[52]; //é ponteiro pois receberá strings (vetor de tamanho variado)
	char *cartas[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

	cleanScreen();

	for (int i = 0; i < 4; i++) {
		for (int c = 0; c < 13; c++) {
			deck[i*13+c] = cartas[c];
		}	
	}

	int lenB = 2;
	char *cartasBot[10];
	cartasBot[0] = randomCard(deck, &len);
	cartasBot[1] = randomCard(deck, &len);

	int lenP = 2;
	char *cartasPlayer[10];
	cartasPlayer[0] = randomCard(deck, &len);
	cartasPlayer[1] = randomCard(deck, &len);

	int res;
	while (1) {
		title();
		printCard(cartasBot, cartasPlayer, lenP, lenB, cartas, 0);

		if (contar(cartasPlayer, cartas, lenP) >= 21) break;

		while (1) {
			printf("\n\nParar? (1)\n");
			printf("Continuar? (2)\n");
			scanf(" %d", &res);
			if (res == 1 || res == 2) break;
		}

		if (res == 2) {
			cleanScreen();
			cartasPlayer[lenP++] = randomCard(deck, &len);
		} else if (res == 1) {
			cleanScreen();
			title();
			// printf("Revelando cartas da máquina:\n\n");
			while (1) {
				int pointsBot;
				pointsBot = contar(cartasBot, cartas, lenB);
				if (pointsBot >= 16) break;
				else {
					cartasBot[lenB++] = randomCard(deck, &len);
				}
			}
			printCard(cartasBot, cartasPlayer, lenP, lenB, cartas, 1);
			break;
		}
	}

	checkWin(contar(cartasBot, cartas, lenB), contar(cartasPlayer, cartas, lenP));

	printf("\n\nFIM DE JOGO\n");
	return 0;
}