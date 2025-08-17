#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** map(const char **ref, int len, char* (*callback)(const char *)) {
	char **vec = malloc(len*sizeof(char *));

	for (int i = 0; i < len; ++i) {	
		vec[i] = callback(ref[i]);
	}

	return vec;
}

char* upperCase(const char *word) { 
	int len = strlen(word);
	char *copy = malloc((len+1)*sizeof(char));
	strcpy(copy, word);

	for (int i = 0; i < len; ++i) {
		copy[i] = toupper(copy[i]);
	}

	return copy;
}

int main() {
	const char *words[] = {"duda", "linda", "perfeita", "maravilhosa"};
	int len = sizeof(words)/sizeof(char *);
	char **copy = map(words, len, upperCase);

	for (int i = 0; i < len; ++i) {
		printf("%s\n", copy[i]);
	}

	free(copy);

	return 0;
}