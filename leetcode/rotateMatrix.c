void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int colSize = *matrixColSize;
    int camadas = matrixSize/2;

    for (int camada = 0; camada < camadas; camada++) {
        int left = camada, top = camada;
        int right = colSize - camada - 1, bottom = colSize - camada - 1;

        for (int i = left; i < right; i++) {
            int offset = i - left;
            int temp = matrix[top][left+offset];

            matrix[top][left+offset] = matrix[bottom-offset][left];
            matrix[bottom-offset][left] = matrix[bottom][right-offset];
            matrix[bottom][right-offset] = matrix[top+offset][right];
            matrix[top+offset][right] = temp;
        }
    }
}