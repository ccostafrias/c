#include <stdio.h>
#include <string.h>

int count_padrao(char codigo[], int len) {
  int inPadrao = 0;
  int count = 0;
  int max = 0;

  for (int letra = 0; letra < len-1; letra++) {
    // Para achar o padrao, basta ver se o proximo e diferente do atual. Se for diferente:
    if (codigo[letra] != codigo[letra+1]) {
      if (!inPadrao) {
        inPadrao = 1; // Inicia o padrao
        count++; // Conta o PRIMEIRO caracter do padrao
      }
      count++;
    } else if (inPadrao) { 
      if (count > max) max = count; // se esse padrao atual for MAIOR que o maior padrao
      count = 0;
      inPadrao = 0;
     } // Se for diferente, termina o padrao
  }

  return max;
}

int main() {
  int casos; scanf("%d", &casos);

  for (int caso = 0; caso < casos; caso++) {
    char codigo[1001]; scanf("%s", codigo); // STRING MAXIMA = 1000 CARACTERES
    int len = strlen(codigo);

    int corrupcao = count_padrao(codigo, len);
    int corrupcao_impar = corrupcao % 2 == 0 ? corrupcao - 1 : corrupcao; // CONVERTE UMA POSSIVEL CORRUPCAO PAR PARA IMPAR

    if (corrupcao_impar < 5) printf("Fala, Coruja!"); // SEM CORRUPCAO
    else if (corrupcao_impar < 7) printf("Duo e Simon querem ficar juntos na SJr!!"); // BAIXA
    else if (corrupcao_impar <= 9) printf("O Simon esta feliz com a SJr!"); // MEDIA
    else printf("O Duo esta feliz com a SJr!"); // ALTA
    if (caso != casos-1) printf("\n");
  }

  return 0;
}