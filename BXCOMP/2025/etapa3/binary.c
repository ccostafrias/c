#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_vec(int * vec, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", vec[i]);
  }
}

void avalia(int * vec, int size, int start) {
  int lastIndice = start+3 >= size ? size-1 : start+3;
  int dist = (lastIndice-start+1), temp;

  //se o ultimo digito do binario eh 1, eh um numero impar, entao invertemos ele
  if (vec[lastIndice] == 1) {
    for (int i = 0; i < dist/2; i++) {
      temp = vec[start+i];
      vec[start+i] = vec[lastIndice-i];
      vec[lastIndice-i] = temp; 
    }
  }
}

int bin_to_dec(int * vec, int size) {
  int sum = 0;
  
  for (int i = 0; i < size; i++) {
    // BINARIO: 1101 = 1*2^0 + 0*2^1 + 1*2^2 + 1*2^3 (da direita pra esquerda SEMPRE)
    sum += vec[size-1-i] * pow(2, i);
  }

  return sum;
}

void print_num_to_char(int num) {
  if (num == 0) return;
  
  int unit = num % 10;
  int nextNum = (num - unit) / 10;
  print_num_to_char(nextNum);
  if (unit != 0) printf("%c", unit+'A'-1);
}

int main() {
  int casos;
  scanf("%d", &casos);

  for (int caso = 0; caso < casos; caso++) {
    char codigo[256]; scanf("%s", codigo);
    int len = strlen(codigo), livre = 0;
    int * binarios = (int*) malloc(len*sizeof(int));

    // insere somente quem for 0 ou 1
    for (int i = 0; i < len; i++) {
      int actual = codigo[i] - '0';
      if (actual == 0 || actual == 1) {
        binarios[livre++] = actual;
      }
    }

    // print_vec(binarios, livre); printf("\n");

    // para cada quadra, faz a avaliacao
    for (int k = 0; k < livre; k += 4) {
      avalia(binarios, livre, k);
    }

    // print_vec(binarios, livre); printf("\n");

    // transform o vetor de binarios em um decimal
    int decimal = bin_to_dec(binarios, livre);
    // printf("DECIMAL = %d", decimal);
    print_num_to_char(decimal);
  }

  return 0;
}