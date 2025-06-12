#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numWords(const char* s, char sep) {
    int len = strlen(s), words = 0, inWord = 0;
    // printf("LEN: %d\n", len);

    for (int i = 0; i <= len; i++) {
        if (s[i] != sep && s[i] != '\0') inWord = 1;
        else if (inWord) {
            inWord = 0;
            words++;
        }
    }

    return words;
}

char** wordsSplited(const char* s, int words, char sep) {
    char** matrix = malloc(words*sizeof(char*));
    int len = strlen(s), word = 0, inWord = 0, iWord = 0;

    for (int i = 0; i <= len; i++) {
        if (s[i] != sep && s[i] != '\0') {
            if (inWord == 0) {
                matrix[word] = malloc((len+1)*sizeof(char));
                iWord = 0;
                inWord = 1;
            }
            matrix[word][iWord++] = s[i];
        } else if (inWord) {
            inWord = 0;
            matrix[word][iWord] = '\0';
            word++;
        }
    }

    return matrix;
}

int main() {
    char s[1024] = {0};

    scanf("%[^\n]", s);

    int nWords = numWords(s, ' ');
    if (nWords <= 0) {
        printf("No words to read\n");
        return 0;
    }
    // printf("N-WORDS: %d\n", nWords);
    char** words = wordsSplited(s, nWords, ' ');

    // print das palavras
    for (int i = 0; i < nWords; i++) {
        printf("%s\n", words[i]);
    }
    
    // free
    for (int i = 0; i < nWords; i++) {
        free(words[i]);
    }

    free(words);

    return 0;
}