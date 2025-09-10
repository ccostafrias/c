#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
  int c;
  int r;
} Pos;

int insideRange(Pos coruja, Pos rex) {
  int dX = abs(coruja.c - rex.c);
  int dY = abs(coruja.r - rex.r);

  if (dX <= 2 || dY <= 2) return 1;
  else return 0;
}

int main() {
  freopen("entradaOlfato.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("saida.out", "w", stdout);

  int casos;

  int * res = malloc(casos * sizeof(int));

  scanf("%d", &casos);
  for (int c = 0; c < casos; c++) {
    Pos coruja;
    Pos rex;
    for (int r = 0; r < 7; r++) {
      char word[255];

      scanf(" %[^\n]", word);
      for (int c = 0; c < 10; c++) {
        if (word[c] == 'C') {
          coruja.c = c;
          coruja.r = r;
        } else if (word[c] == 'T') {
          rex.c = c;
          rex.r = r;
        }
      }
    }
    
    res[c] = insideRange(coruja, rex);
  }

  for (int c = 0; c < casos; c++) {
    if (res[c]) printf("Xi, ele me notou, preciso fugir antes que eu vire KFC de dinossauro!\n");
    else printf("Nao fui notada ainda hehehe\n");
  }

  free(res);
  
  return 0;
}