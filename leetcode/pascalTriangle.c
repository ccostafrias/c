int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int ** matrix = (int**) malloc(numRows*sizeof(int*));
    (*returnColumnSizes) = (int*) malloc(numRows*sizeof(int));

    for (int i = 0; i < numRows; i++) {
        matrix[i] = (int*) malloc((i+1)*sizeof(int));
        (*returnColumnSizes)[i] = i+1;
    }

    matrix[0][0] = 1;

    for(int i = 1; i < numRows; i++) {
        matrix[i][0] = 1;
        matrix[i][i] = 1;
        for (int j = 1; j < i; j++) {
            matrix[i][j] = matrix[i-1][j-1] + matrix[i-1][j];
        }
    }

    *returnSize = numRows;

    return matrix;
}