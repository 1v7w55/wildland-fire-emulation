// Freeing up memory space of the matrix
void freeMatrix(Element** matrix, size_t height) {
  for (size_t i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}