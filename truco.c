#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h> //biblioteca para o tempo
#include <stdlib.h> //biblioteca para o rand()

void cleanScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void waitEnter() {
    int c;
    printf("Pressione ENTER para continuar...");
    // Limpa o buffer at� encontrar '\n'
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // Espera o ENTER real
}

int randomN(int min, int max) {
    return rand() % (max - min + 1) + min;
}

static char cards[10] = {'4', '5', '6', '7', 'Q', 'J', 'K', 'A', '2', '3'};
// naipes = diamonds, spades, hearts, clubs
static char suits[4] = {'D', 'S', 'H', 'C'};
static struct Deck *deck = NULL;

struct Card {
    char value;
    char suit;
    int vOrder;
    int sOrder;
    int isPlayed;
};

struct Deck {
    struct Card card;
    int isTaken;
};

void fillHand(struct Card *hand, int size) {
    for (int i = 0; i < size; i++) {
        int card;
        while (1) {
            // enquanto o n�mero da carta gerado for "isTaken", significa que ela j� foi pega e ser� necess�rio gerar um outro valor
            card = randomN(0, 39);
            if (!deck[card].isTaken) break;
        }
        // copia as cartas do deck para a respectiva m�o, al��em de atualizar a carta do deck para "isTaken" (foi pega)
        deck[card].isTaken = 1;
        hand[i].value = deck[card].card.value;
        hand[i].suit = deck[card].card.suit;
        hand[i].vOrder = deck[card].card.vOrder;
        hand[i].sOrder = deck[card].card.sOrder;
        hand[i].isPlayed = deck[card].card.isPlayed;
    }
}

void resetDeck() {
    for (int i = 0; i < 40; i++) {
        deck[i].isTaken = 0;
    }
}

char pickManilha(char turnCard) {
    char manilha;

    // a ordem das manilhas � sucessiva e c�clica (ex: vira 4, manilha 5 / vira 7, manilha Q / vira 3, manilha 4)
    if (turnCard == '3') manilha = '4';
    else {
        for(int i = 0; i < 10; i++) {
            // ao encontrar a respectiva carta virada no monte de cartas, a maninha � a pr�xima daquele monte
            if (cards[i] == turnCard) manilha = cards[i+1];
        }
    }

    return manilha;
}

int hasManilha(struct Card *hand, char turnCard, int handSize){
    char manilha = pickManilha(turnCard);

    for (int i = 0; i < handSize; i++) if (hand[i].value == manilha) return 1;
    
    return 0;
}

int isManilha(struct Card card, char turnCard){
    char manilha = pickManilha(turnCard);
    
    return (card.value == manilha);
}

int hasCard(struct Card *hand, struct Card ref, int handSize) {
    for (int i = 0; i < handSize; i++) {
        // se a carta de refer�ncia tiver o mesmo valor e o mesmo naipe de qualquer uma das cartas da m�o, � pq a carta de refer�ncia est� na m�o
        if (hand[i].value == ref.value && hand[i].suit == ref.suit) return 1;
    }
    
    return 0;
}

float probability(struct Card *hand, struct Card card, struct Card turnCard, int handSize) {
    int count = 0;
    char manilha = pickManilha(turnCard.value);
    for (int i = 0; i < 40; i++) {
        // se a carta que est� sendo comparada j� pertence � m�o, ela ser� pulada
        if (hasCard(hand, deck[i].card, handSize)) continue;
        // se a carta comparada for o vira, tamb�m ser� pulada
        else if (deck[i].card.value == turnCard.value && deck[i].card.suit == turnCard.suit) continue;
        // se a carta em an�lise for manilha:
        if (card.value == manilha) {
            // se a carta comparada � manilha
            if (deck[i].card.value == manilha) {
                // ganha quem tiver a maior manilha
                if (card.sOrder > deck[i].card.sOrder) count++;
            } else {
                // se a carta comparada n�o for manilha, a carta em an�lise - uma manilha - � com certeza maior
                count++;
            }
        // se a carta em an�lise n�o � manilha, s� vence se a carta comparada tamb�m n�o for manilha
        } else if (deck[i].card.value != manilha) {
            // se ambas n�o s�o manilha, ganha a maior carta
            if (card.vOrder > deck[i].card.vOrder) count++;
        }
    }

    // a probabilidade de ganhar ser� o count, que representa quantas o n�mero de cartas de que foi poss�vel ganhar, sobre 40 (total de cartas) menos as cartas da m�o (que n�o foram analisadas) e menos o vira
    float prob = (float) count / (40-handSize-1);
    return prob;
}

char getSuitSymbol(char suit) {
    switch(suit) {
        // naipes de acordo com o c�digo ASCII deles
        case 'H': return 3; // hearts
        case 'S': return 6; // spades
        case 'D': return 4; // diamonds
        case 'C': return 5; // clubs
        default: return suit;
    }
}

void fillDeck() {
    // faz um loop para cada uma das 10 cartas do truco (v = value)
    for(int v = 0; v < 10; v++) {
        // faz um loop para cada um dos naipes (s = suit)
        for(int s = 0; s < 4; s++) {
            // n�o � v�lido fazer essa declara��o direta depois que a vari�vel j� foi inicilaizada, � necess�rio fazer elemento por elemento
            deck[v * 4 + s].card.value = cards[v];
            deck[v * 4 + s].card.suit = suits[s];
            deck[v * 4 + s].card.vOrder = v;
            deck[v * 4 + s].card.sOrder = s;
            deck[v * 4 + s].card.isPlayed = 0;
            deck[v * 4 + s].isTaken = 0;
        }
    }
}

int dumbBotPlay(struct Card *hand) {
    // essa vers�o do bot s� joga cartas aleat�rias
    while (1) {
        int randIndex = randomN(0, 2);
        if (!hand[randIndex].isPlayed) return randIndex;
    }
}

void setPlayed(struct Card *hand, int index) {
    hand[index].isPlayed = 1;
}

char turnWinner(struct Card player, struct Card bot, struct Card turnCard) {
    char manilha = pickManilha(turnCard.value);
    // printf("WINNER DEBUG: %c%d %c%d %c\n", player.value, player.vOrder, bot.value, bot.vOrder, turnCard.value);
    // se a carta do player � manilha:
    if (player.value == manilha) {
        // se a carta do bot tamb�m for manilha
        if (bot.value == manilha) {
            // ganha quem tiver a maior manilha
            if (player.sOrder > bot.sOrder) return 'P';
        } else {
            return 'P';
        }
    // se a carta do bot n�o � manilha, s� vence se a carta do player tamb�m n�o for manilha
    } else if (bot.value != manilha) {
        // se ambas n�o s�o manilha, ganha a maior carta
        if (player.vOrder > bot.vOrder) return 'P';
        else if (player.vOrder == bot.vOrder) return 'D';
    }
    return 'B';
}

char roundWin(int pointsP, int pointsB) {
    if (pointsP >= 2 && pointsP != pointsB) return 'P';
    if (pointsB >= 2 && pointsB != pointsP) return 'B';
    return ' ';
}

// essa fun��o inicia um novo turno
void startTurn(int pointsP, int pointsB) {
    int handSize = 3;
    // CARTAS GERADAS ALEATORIAMENTE
    struct Card *myHand = malloc(handSize * sizeof(struct Card));
    struct Card *botHand = malloc(handSize * sizeof(struct Card));
    struct Card *turnCard = malloc(sizeof(struct Card));

    // distribui as cartas e define quem ser� o "vira"
    fillHand(myHand, handSize);
    fillHand(botHand, handSize);
    fillHand(turnCard, 1);

    // MANIPULANDO CARTAS
    // struct Card myHand[3] = {{'7', 'H', 3, 2}, {'3', 'C', 9, 3}, {'A', 'D', 7, 0}};
    // struct Card botHand[3] = {{'Q', 'H', 4, 2}, {'5', 'S', 1, 1}, {'5', 'H', 1, 2}};
    // struct Card turnCard[1] = {{'4', 'H', 0, 2}};
    resetDeck();
    
    int pointsRP = 0, pointsRB = 0;
    // essa fun��o inicia cada uma das tr�s poss�veis rodadas dentro de um turno
    void startRound() {
        cleanScreen();        
        printf("================ TRUCO ================\n");
        printf("PLACAR: Player = %d | Bot = %d\n", pointsP, pointsB);
        printf("RODADA: Player = %d | Bot = %d\n", (int) pointsRP, (int) pointsRB);
        printf("VIRA: %c%c\n\n", turnCard[0].value, getSuitSymbol(turnCard[0].suit));
        printf("Sua m�o:\n");
        for (int i = 0; i < handSize; i++) {
            if (myHand[i].isPlayed) continue;
            printf("[%d] %c%c ", i+1, myHand[i].value, getSuitSymbol(myHand[i].suit));
        }
        int indexPlayer;
        // for�a o jogador a escolher um n�mero coerente de cartas
        while (1) {
            printf("\nEscolha uma carta para jogar: ");
            scanf(" %d", &indexPlayer);
            if (indexPlayer >= 1 && indexPlayer <= 3 && !myHand[indexPlayer-1].isPlayed) {
                indexPlayer--;
                break;
            }
        }
        // define a carta escolhida pelo player como jogada, para que ele n�o possa escolher novamente
        setPlayed(myHand, indexPlayer);
        
        int indexBot;
        // l�gica do bot que vai decidir qual carta ser� jogada
        indexBot = dumbBotPlay(botHand);
        setPlayed(botHand, indexBot);
    
        printf("\nMesa:\n");
        printf("Voc� jogou: %c%c\n", myHand[indexPlayer].value, getSuitSymbol(myHand[indexPlayer].suit));
        printf("Bot jogou: %c%c\n\n", botHand[indexBot].value, getSuitSymbol(botHand[indexBot].suit));
    
        // verifica quem � o ganhador da rodada
        char winner = turnWinner(myHand[indexPlayer], botHand[indexBot], turnCard[0]);
    
        if (winner == 'P') {
            printf("Voc� pontuou!\n");
            printf("Cartas ganhadoras: %c%c > %c%c\n", myHand[indexPlayer].value, getSuitSymbol(myHand[indexPlayer].suit), botHand[indexBot].value, getSuitSymbol(botHand[indexBot].suit));
            pointsRP++;
        } else if (winner == 'B') {
            printf("O Bot pontuou...\n");
            printf("Cartas ganhadoras: %c%c > %c%c\n", botHand[indexBot].value, getSuitSymbol(botHand[indexBot].suit), myHand[indexPlayer].value, getSuitSymbol(myHand[indexPlayer].suit));
            pointsRB++;
        } else {
            printf("Empate!\n");
            printf("Cartas da rodada: %c%c = %c%c\n", botHand[indexBot].value, getSuitSymbol(botHand[indexBot].suit), myHand[indexPlayer].value, getSuitSymbol(myHand[indexPlayer].suit));
            pointsRP ++;
            pointsRB ++;
        }

        // verifica se houve um ganhador do turno j�
        char tempWinner = roundWin(pointsRP, pointsRB);
        if (tempWinner != ' ') {
            if (tempWinner == 'P') {
                printf("\nVoc� venceu a rodada!\n");
                pointsP++;
            } else if (tempWinner == 'B') {
                printf("\nO Bot venceu a rodada!\n");
                pointsB++;
            }
            // caso algu�m j� tenho ganho, � necess�rio liberar o espa�o da mem�ria dos antigos vetores e depois iniciar um novo turno
            free(myHand);
            free(botHand);
            free(turnCard);
            waitEnter();
            startTurn(pointsP, pointsB);

        } else {
            waitEnter();
            startRound();
        }
    }
    startRound();
}

void startGame() {
    int pointsP = 0, pointsB = 0;
    fillDeck();
    startTurn(pointsP, pointsB);
}

int main() {
    srand(time(NULL)); 

    setlocale(LC_ALL, "Portuguese");

    // cria dinamicamente um vetor de structs para armazenar todas as 40 cartas do truco
    deck = malloc(40 * sizeof(struct Deck));

    startGame();

    // DEBUG CARTAS
    // printf("TURN CARD: %c%c\n", turnCard[0].value, getSuitSymbol(turnCard[0].suit));
    // printf("MANILHA: %c\n", pickManilha(turnCard[0].value));
    // printf("TEM MANILHA? %d\n", hasManilha(myHand, turnCard[0].value, handSize));
    // printf("===============\n");
    // printf("PLAYER: \n");
    // for(int i = 0; i < 3; i++) {
    //     printf("%c%c, prob. = %1.f%%\n", myHand[i].value, getSuitSymbol(myHand[i].suit), probability( myHand, myHand[i], turnCard[0], handSize)*100);
    // }
    // printf("===============\n");
    // printf("BOT: \n");
    // for(int i = 0; i < 3; i++) {
    //     printf("%c%c, prob. = %1.f%%\n", botHand[i].value, getSuitSymbol(botHand[i].suit), probability(botHand, botHand[i], turnCard[0], handSize)*100);
    // }

    return 0;
}