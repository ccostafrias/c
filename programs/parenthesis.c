#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef int Bool;

char ** parens;
int parensLen = 0;

Bool valid_parenthesis(char * paren) {
  int len = strlen(paren), k = 0;
  
  for (int i = 0; i < len; i++) {
    if (paren[i] == '(') {
      k++;
    } else if (paren[i] == ')') {
      if (k > 0) k--;
      else return FALSE;
    }
  }

  return k > 0 ? FALSE : TRUE;
}

char * generate_paren(int num) {
  char * paren = malloc((num+1) * sizeof(char));

  for (int i = 0; i < num; i++) {
    paren[i] = '(';
  }

  if (num > 1) paren[num-1] = ')';
  paren[num] = '\0';

  return paren;
}

void testa_paren(char * paren, int k) {
  int len = strlen(paren);

  
  if (k == len-1) {
    if (valid_parenthesis(paren)) {
      strcpy(parens[parensLen++], paren);
    }
    return;
  };

  char * copy1 = malloc((len+1) * sizeof(char));
  char * copy2 = malloc((len+1) * sizeof(char));

  strcpy(copy1, paren);
  strcpy(copy2, paren);

  testa_paren(copy1, k+1);
  copy2[k] = ')';
  testa_paren(copy2, k+1);

  free(copy1);
  free(copy2);

  return;
}

int main() {
  int num; scanf("%d", &num);
  char * paren = generate_paren(2*num);
  int tempSize = 1 << (2 * (num-1));

  parens = malloc(tempSize * sizeof(char*));
  for (int i = 0; i < tempSize; i++) parens[i] = malloc((strlen(paren)+1) * sizeof(char));

  testa_paren(paren, 1);

  for (int i = 0; i < parensLen; i++) printf("%s ", parens[i]);

  for (int i = 0; i < tempSize; i++) free(parens[i]);
  free(parens);

  return 0;
}