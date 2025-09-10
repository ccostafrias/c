#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * cifraClub(char * w) {
  char * deciphered = malloc(256 * sizeof(char));
  int sizeW = (int) strlen(w);

  for (int i = 0; i < sizeW; i++) {
    if (w[i] >= 97 && w[i] <= 122) {
      deciphered[i] = (w[i]-97-10+26)%26+97;
    } else deciphered[i] = w[i];
  }

  return deciphered;

}

int main()
{
  freopen("entradaUgaBuga.in", "r", stdin);
  freopen("saida.out", "w", stdout);

  char sentence[256];
  scanf(" %[^\n]", sentence);

  char * deciphered = cifraClub(sentence);
  printf("%s\n", deciphered);

  free(deciphered);

  return 0;
}