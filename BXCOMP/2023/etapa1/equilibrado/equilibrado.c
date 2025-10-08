#include <stdio.h>
#include <math.h>

int abs(int n) { return n < 0 ? -n : n; }

int main() {
  freopen("entrada.in", "r", stdin);
  freopen("saida.out", "w", stdout);

  int casos;
  scanf("%d", &casos);

  for (int caso = 0; caso < casos; caso++) {
    int tamanho; // tamanho da pirâmide
    scanf("%d", &tamanho);

    int A = ceil(tamanho/2.0); // limite inferior
    int B = tamanho*3; // limite superior
    
    int erro = 0;
    
    int somaAntiga; scanf("%d", &somaAntiga); // soma antiga vai começar com o primeiro elemento

    for (int linha = 1; linha < tamanho; linha++) { // começa em linha 1 pois a linha 0 já foi recebida em somaAntiga (apenas um elemento)
      int somaNova = 0; // inicia a soma daquela linha da pirâmide
      
      for (int coluna = 0; coluna <= linha; coluna++) {
        int num; scanf("%d", &num);
        somaNova += num; // soma cada elemento da linha
      }
      
      if (erro) continue; // se deu erro, devemos continuar percorrendo para elinar do stdin o resto da pirâmide

      int dif = abs(somaNova - somaAntiga); // dif é o valor absoluto (módulo) da diferença entre as somas: soma da linha anterior e soma da linha atual
      if (dif < A || dif > B) {
        printf("DEU RUIM!\n"); // se estiver fora dos limites, deu ruim!
        erro = 1;
        continue; // nao podemos usar break pois ainda há scanfs que devem ser computado, a fim de terminar de ler essa piramide e ir para a proxima
      }

      somaAntiga = somaNova; // a soma antiga vira a soma atual
    }

    if (!erro) printf("DEU BOM!\n"); // se, após percorrer, não houve erro, deu bom!
  }

  return 0;
}