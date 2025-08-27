#include <stdio.h>
#include <stdlib.h>

int muitoPerto(int v[], int len) {
  int foundNave = 0;
  int distSaida = 1;
  int distMeteoro = 0;
  int meteoros = 0;

  for (int i = len - 1; i >= 0; i--) {
    int actualNum = v[i];
    // printf("%d\n", actualNum);

    if (!foundNave) {
      if (actualNum == 2) {
        foundNave = 1;
        meteoros = 0;
      } else {
        if (actualNum == 1) meteoros++;
        if (meteoros >= 2) return 1;
        distSaida++;
      }
    } else {
      distMeteoro++;
      if (actualNum == 1) {
        meteoros++;
        break;
      }
    }
  }

  return distMeteoro < distSaida && meteoros > 0 ? 1 : 0;
}

int main() {
  freopen("entrada1.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("saida.out", "w", stdout);   // opcional, redireciona stdout para arquivo

  int casos;

  scanf("%d", &casos); // lê o primeiro número (5)

  for (int i = 0; i < casos; i++) {
    int v[10];

    for (int i = 0; i < 10; i++) {
      scanf("%d", &v[i]);
    }

    int passou = muitoPerto(v, 10);

    if (!passou) {
      printf("Explorador do espaço para base alpha, conseguimos passar pela chuva de meteoros!\n");
    } else {
      printf("Nu, vou tascar um beijo numa pedra do espaço se eu entrar ai, paia.\n");
    }
  }

  return 0;
}