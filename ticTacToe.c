#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int randomN(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void mostrarTabuleiro(char tab[3][3]) {
	for (int i = 0; i < 3; ++i){
		// if (i != 1) printf("     |     |     \n");
		printf(" %c | %c | %c \n", tab[i][0], tab[i][1], tab[i][2]);
		if (i < 2) {
			printf("---|---|---\n");
		}
	}
	printf("\n");
}

char whoWon(char tab[3][3]) {
	char compare;
	int k = 0;

	// vitória na horizontal
	for (int r = 0; r < 3; ++r) {
		compare = tab[r][0];
		if (compare == ' ') continue;
		k = 1;
		for (int c = 1; c < 3; ++c) {
			if (compare != tab[r][c]) {
				compare = ' ';
				break;
			} else k++;
			if (k == 3) return compare;
		}
	}

	// vitória na vertical
	for (int c = 0; c < 3; ++c) {
		compare = tab[0][c];
		if (compare == ' ') continue;
		k = 1;
		for (int r = 1; r < 3; ++r) {
			if (compare != tab[r][c]) {
				compare = ' ';
				break;
			} else k++;
			if (k == 3) return compare;
		}
	}

	// vitória na primeira diagonal
	compare = tab[0][0];
	k = 1;
	for (int n = 1; n < 3; ++n){
		if (compare == ' ') break;
		if (compare != tab[n][n]) {
			compare = ' ';
			break;
		} else k++;
		if (k == 3) return compare;
	}

	// vitória na segunda diagonal
	compare = tab[0][2];
	k = 1;
	for (int n = 1; n < 3; ++n){
		if (compare == ' ') break;
		if (compare != tab[n][2-n]) {
			compare = ' ';
			break;
		} else k++;
		if (k == 3) return compare;
	}

	return ' ';
}

int isOccupied(char tab[3][3], int r, int c) {
	if (tab[r][c] != ' ') return 1;
	return 0;
}

void addPiece(char tab[3][3], char piece, int c, int r) {
	tab[r][c] = piece;
}

void title() {
	printf("########## TIC TAC TOE ##########\n\n");
}

void printWin(char *text, char tab[3][3], int win, int *playing) {
	cleanScreen();
	title();
	printf("%s", (win >= 0) ? (win ? "VITÓRIA!\n\n" : "DERROTA...\n\n") : "EMPATE!\n\n");
	mostrarTabuleiro(tab);
	printf("%s", text);
	(*playing) = 0;
}

void verifyVelha(int *plays, char tab[3][3], int *playing) {
	(*plays)++;
	if (*plays == 9) {
		printWin("Deu velha! #\n\n", tab, -1, playing);
		(*playing) = 0;
	}
}

int isCoordValid(char coords[4]) {
    if (strlen(coords) != 3) return 0;
    if (!isdigit(coords[0]) || !isdigit(coords[2])) return 0;
    if (coords[1] != '-') return 0;
    
    int r = coords[0] - '0';
    int c = coords[2] - '0';

    if (r < 1 || r > 3 || c < 1 || c > 3) return 0;

    return 1;
}

void playIA(char tab[3][3], char aiPiece, char playerPiece) {
	// 1. Tentar vencer
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (!isOccupied(tab, r, c)) {
				tab[r][c] = aiPiece;
				if (whoWon(tab) == aiPiece) return;
				tab[r][c] = ' ';
			}
		}
	}

	// 2. Tentar bloquear o jogador
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (!isOccupied(tab, r, c)) {
				tab[r][c] = playerPiece;
				if (whoWon(tab) == playerPiece) {
					tab[r][c] = aiPiece;
					return;
				}
				tab[r][c] = ' ';
			}
		}
	}

	// 3. Jogar no centro
	if (!isOccupied(tab, 1, 1)) {
		tab[1][1] = aiPiece;
		return;
	}

	// 4. Jogar nas quinas
	int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
	for (int i = 0; i < 4; i++) {
		int r = corners[i][0];
		int c = corners[i][1];
		if (!isOccupied(tab, r, c)) {
			tab[r][c] = aiPiece;
			return;
		}
	}

	// 5. Jogar aleatoriamente
	int r, c;
	do {
		r = randomN(0, 2);
		c = randomN(0, 2);
	} while (isOccupied(tab, r, c));
	tab[r][c] = aiPiece;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    
	srand(time(NULL)); 

	char tab[3][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	cleanScreen();
	title();
	char piece;
	while (1) {
		printf("Deseja jogar com X ou com O? (X/O)\n");
		scanf(" %c", &piece);
		piece = toupper(piece);
		if (piece == 'X' || piece == 'O') break;
	}

	cleanScreen();
	title();
	char versus;
	while (1) {
		printf("Deseja jogar contra a máquina ou contra outro jogador? (M/J)\n");
		scanf(" %c", &versus);
		versus = toupper(versus);
		if (versus == 'M' || versus == 'J') break;
	}

	char otherPiece = (piece == 'X') ? 'O' : 'X';
	char coords[4];

	int turn = 1, plays = 0, playing = 1;

	void getCoord() {
		do {
			printf("Escolha onde jogar: (LINHA-COLUNA)\n");
			scanf(" %3s", coords);
		} while (!isCoordValid(coords) || isOccupied(tab, coords[0]-'0'-1, coords[2]-'0'-1));
	}

	if (versus == 'M') {
		while(playing) {
			cleanScreen();
			title();
			printf("Sua vez!\n\n");
			mostrarTabuleiro(tab);
			getCoord();

			addPiece(tab, piece, coords[2]-'0'-1, coords[0]-'0'-1);
			if (whoWon(tab) == piece) {
				printWin("Você venceu da máquina!\n", tab, 1, &playing);
				break;
			}

			verifyVelha(&plays, tab, &playing);
			if (!playing) break;

			playIA(tab, otherPiece, piece);
			
			if (whoWon(tab) == otherPiece) {
				printWin("Mais sorte da próxima vez...\n", tab, 0, &playing);
				break;
			}

			verifyVelha(&plays, tab, &playing);
			if (!playing) break;
		}
	} else {
		while (playing) {
			cleanScreen();
			title();
			printf("Vez do jogador nº %d!\n\n", turn);
			mostrarTabuleiro(tab);
			getCoord();

			char turnPiece = (turn == 1) ? piece : otherPiece;

			addPiece(tab, turnPiece, coords[2]-'0'-1, coords[0]-'0'-1);
			if (whoWon(tab) == turnPiece) {
				char text[100];
				sprintf(text, "Jogador nº %d ganhou!\n", turn);
				printWin(text, tab, 1, &playing);
				break;
			}
			verifyVelha(&plays, tab, &playing);
			turn = (turn % 2) + 1;
		}
	}

	return 0;
}