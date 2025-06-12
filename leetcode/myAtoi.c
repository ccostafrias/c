#include <stdio.h>
#include <limits.h>

int myAtoi(char* s) {
    long int n = 0;
    int inNum = 0, signal = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            // se o sinal de + ficou implícito
            if (signal == 0) signal = 1;
            if (inNum == 0) inNum = 1;
            n *= 10;
            n += (int)(s[i]-'0');

            if (n > INT_MAX || n < INT_MIN) {
                return signal == 1 ? INT_MAX : INT_MIN;
            }
        }
        else if (inNum || signal) break;
        // lida com leading spaces
        else if (s[i] == ' ') continue;
        // sinais
        else if (s[i] == '-') signal = -1;
        else if (s[i] == '+') signal = 1;
        // caracteres inválidos
        else break;
    }

    return (int)(n * signal);
}

int main() {
    char num[100];
    int numConverted;
    
    scanf("%s", num);
    
    numConverted = myAtoi(num);

    printf("%d", numConverted);

    return 0;
}