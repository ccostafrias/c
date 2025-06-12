void invertVec(char* nums, int size) {
    for (int i = 0; i < size/2; i++) {
        char temp = nums[size-(i+1)];
        nums[size-(i+1)] = nums[i];
        nums[i] = temp;
    }
}

char* addBinary(char* a, char* b) {
    int lenA = strlen(a), lenB = strlen(b), k = 0, acc = 0;
    int bigger = lenA > lenB ? lenA : lenB;
    char* binary = malloc((bigger+2)*sizeof(char));

    while (k < lenA || k < lenB || acc != 0) {
        int digitA = k >= lenA ? 0 : a[lenA - (k+1)]-'0';
        int digitB = k >= lenB ? 0 : b[lenB - (k+1)]-'0';
        int sum = digitA + digitB + acc;
        binary[k++] = (sum % 2)+'0';
        acc = sum / 2;
    }

    invertVec(binary, k);
    binary[k] = '\0';

    return binary;
}