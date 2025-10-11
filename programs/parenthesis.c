#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Bool;

Bool valid_parenthesis(char * paren) {
  int len = strlen(paren), k = 0;
  // int * pilha = malloc(len * sizeof(int));
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

  for (int i = 1; i < num-1; i++) {
    paren[i] = '(';
  }

  paren[0] = '(';
  if (num > 1) paren[num-1] = ')';
  paren[num] = '\0';
  return paren;
}

Bool testa_paren(char * paren, int k) {
  int len = strlen(paren);
  if (k == len-1) return FALSE;
}

int main() {
  int num; scanf("%d", &num);
  char * paren = generate_paren(num);

  Bool isValidParen = valid_parenthesis(paren);
  printf("parentesis: %s\n", paren);
  printf("eh valido: %s\n", isValidParen ? "SIM" : "NAO");

  return 0;
}