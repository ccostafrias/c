#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

const char * ESQ = "ESQUERDA";
const char * DIR = "DIREITA";

typedef struct {
  int hasSaida;
  int direcoes[1000];
  int sizeDir;
} Caminho;

int main() {
  freopen("entradaBagre.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("saida.out", "w", stdout);

  int SIZE_ESQ = strlen(ESQ);
  int SIZE_DIR = strlen(DIR);

  int casos;
  scanf("%d", &casos);
  Caminho * res = malloc(casos * sizeof(Caminho));

  for (int c = 0; c < casos; c++) {
    res[c].sizeDir = 0;

    int words;
    scanf(" %d", &words);

    for (int w = 0; w < words; w++) {
      int esqIndex = 0;
      int dirIndex = 0;
      int hasEsq = 0;
      int hasDir = 0;

      char word[255];
      scanf(" %[^\n]", word);
      int lenW = strlen(word);

      for (int l = 0; l < lenW; l++) {
        char actualChar = word[l]; 

        if (actualChar == ESQ[esqIndex]) esqIndex++;
        else if (actualChar == ESQ[0]) esqIndex = 1;
        else esqIndex = 0;

        if (actualChar == DIR[dirIndex]) dirIndex++;
        else if (actualChar == DIR[0]) dirIndex = 1;
        else dirIndex = 0;

        if (esqIndex == SIZE_ESQ && !hasEsq) {
          hasEsq = 1;
        } else if (dirIndex == SIZE_DIR && !hasDir) {
          hasDir = 1;
        }
      }

      if((hasDir || hasEsq) && !(hasDir && hasEsq)) {
        res[c].hasSaida = 1;
        res[c].direcoes[res[c].sizeDir++] = hasDir ? 1 : -1;
      } else {
        res[c].hasSaida = 0;
        break;
      }
    }
    
  }

  for (int c = 0; c < casos; c++) {
    if (res[c].hasSaida) {
      for (int i = 0; i < res[c].sizeDir; i++) {
        if (res[c].direcoes[i] == 1) printf("DIREITA ");
        else printf("ESQUERDA ");
      }
      
      printf("ESPERE POR NOS CORUJINHA!!!\n");
    }
    else printf("Ahn? Acho que escolhemos o tunel errado...\n");
  }

  free(res);
  
  return 0;
}