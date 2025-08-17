#include <stdio.h>
#include <locale.h>

double media(double* notas, int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += notas[i];
    }
    return soma / n;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int n_alunos;
    double notas[100];

    FILE* arquivo = fopen("notas.txt", "r");

    if (arquivo == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO!");
        return 1;
    }

    fscanf(arquivo, "%d", &n_alunos);
    printf("Número de alunos lido do arquivo: %d\n\n", n_alunos);

    // --- CÓDIGO CORRIGIDO ---
    for (int i = 0; i < n_alunos; i++) {
        // 1. Primeiro, leia o valor do arquivo e guarde em notas[i]
        fscanf(arquivo, "%lf", &notas[i]);

        // 2. Agora, com o valor correto já armazenado, imprima-o para verificar
        //    (melhorei a mensagem para ficar mais claro)
        printf("Nota lida para o aluno %d: %.2f\n", i + 1, notas[i]);
    }

    // A chamada para a função media() usará o array 'notas' já preenchido corretamente.
    printf("\nA média da sala foi %g\n", media(notas, n_alunos));

    fclose(arquivo);

    return 0;
}