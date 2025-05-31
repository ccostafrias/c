int lengthOfLastWord(char* s) {
    int len = strlen(s), count = 0;

    for (int i = 0; i <= len; i++) {
        if (s[i] == ' ') {
            if (s[i+1] != ' ' && s[i+1] != '\0') count = 0;
        } else if (s[i] == '\0') break;
        else count++;
    }

    return count;
}