#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

const char* nomes_dias[7] = {
    "Sábado",
    "Domingo",
    "Segunda-feira",
    "Terça-feira",
    "Quarta-feira",
    "Quinta-feira",
    "Sexta-feira"
};

int main() {
    setlocale(LC_ALL, "Portuguese");

    char data[16];
    int nums[3];
    int i = 0;

    scanf("%s", data);

    // separar números
    char *token = strtok(data, "/");
    while (token != NULL) {
        nums[i++] = atoi(token);
        token = strtok(NULL, "/");
    }

    int d = nums[0], m = nums[1], a = nums[2];

    if (m <= 2) {
        m += 12;
        a --;
    }

    int sum = d + 2*m + (3*(m+1)/5) + a + a/4 - a/100 + a/400 + 2;
    int res = sum % 7;

    printf("%s", nomes_dias[res]);

    return 0;
}