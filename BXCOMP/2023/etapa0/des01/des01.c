#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265
#define RAIO(c) c/(2*PI)
#define CIRCUM(r) 2*PI*r

int find(char s[], int n, int len) {
  if (len == 0) return 0;

  int unit = n % 10;
  int nextNumber = (n-unit)/10;
  int actualNumber = s[len-1]-'0';

  if (nextNumber == 0 && unit == actualNumber) return 1;
  else if (unit == actualNumber) {
    return find(s, nextNumber, len-1) || find(s, n, len-1);
  } else {
    return find(s, n, len-1);
  }  
}

int main() {
  freopen("entrada.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("saida.out", "w", stdout);   // opcional, redireciona stdout para arquivo

  char buffer[100];
  int casos;

  fgets(buffer, sizeof(buffer), stdin);
  sscanf(buffer, "%d", &casos);

  for (int i = 0; i < casos; i++) {
    char numVec[24];
    double raio;

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%lf", &raio);

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%s", numVec);

    int pCircum = CIRCUM(raio);
    
    if (pCircum > 40075) {
      printf("OLHA O TAMANHO DESSE PLANETA\n");
    } else {
      int achou = find(numVec, pCircum, (int)strlen(numVec));
      if (achou) {
        printf("Foguete nao tem marcha re, vamo bora fml\n");
      } else {
        printf("Ferrou, estamos no planeta errado\n");
      }
    }
  }

  return 0;
}