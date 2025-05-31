#include <stdio.h>
#include <string.h>

int strStr(char* haystack, char* needle) {
    int lenH = strlen(haystack), lenN = strlen(needle);
    int i = 0, c = 0, s = -1;

    if (lenN > lenH) return s;

    while (i < lenH) {
        // se na i-ésima iteração não houver começado uma correlação e não for mais possível terminar de fato uma palavra (pois não cabe mais), retorna -1
        // imagine a 'haystack' = castelo e a 'needle' = telos, a partir do 't' de 'castelo' já não é mais necessário verficar, pois não cabe mais um 'telos' ali
        if (s == -1 && (i + lenN > lenH)) return -1;
        // se c for igual ao tamanho da needle, é pq foi identificado que existe um needle dentro de haystack, logo retornamos a posição em que a verificação começou
        if (c >= lenN) return s;

        // se as letras coincidirem:
        if (haystack[i] == needle[c]) {
            // caso ainda não tivesse começado uma verificação, aquele indice será o começo
            if (s == -1) s = i;
            c++;
            i++;
        } else {
        // caso as letras não coincidam, é necessário voltar para a iteração logo após a que começou na verificação anterior, pois é possível que a palavra estivesse ali no meio
        // caso não tivesse uma verificação rolando, a iteração simplesmente continua normalmente
            i = (s == -1) ? (i+1) : (s+1);
            c = 0;
            s = -1;
        }
    }

    return s;
}

int main() {
    char haystack[100], needle[100];

    scanf("%s ", haystack);
    scanf("%s", needle);

    printf("%d", strStr(haystack, needle));

    return 0;
}