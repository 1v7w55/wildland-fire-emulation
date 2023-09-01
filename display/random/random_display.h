#include "../../config/global.h"
#include "../../bean/typeElement.h"
#include "../../enum/element.h"

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

void displayMatrix(Element **matrix, int randomWidth, int randomHeight, short step) {
  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      printf("%c", matrix[i][j].symbol);
    }
    printf("   ");
    for (int j = 0; j < randomWidth; j++) {
      if (matrix[i][j].degree >= 1) {
        matrix[i][j].degree -= 1;
      } else if (matrix[i][j].degree == 1) {
        matrix[i][j] = ash;
      } else if (
        matrix[i][j].degree == 0 
        && matrix[i][j].type != 'G' 
        && matrix[i][j].type != 'W' 
        && matrix[i][j].type != 'E'
      ) {
        matrix[i][j] = extinctAsh;
      }
      printf("%d", matrix[i][j].degree);
    }
    printf("\n");
  }
  printf("\n");
}

int randomDisplay() {
  // time is used to generate a different number each time we run the program, if we didnt use it, we would get the same number each time
  srand(time(NULL));
  int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  int randomHeight = (rand() % MAX_WIDTH) + MIN_WIDTH;
  // To debug only
  printf("Width: %d, Height: %d\n", randomWidth, randomHeight);
  // Create matrix with random width and height
  Element **matrix = malloc(randomHeight * sizeof(Element *));
  for (int i = 0; i < randomHeight; i++) {
    matrix[i] = malloc(randomWidth * sizeof(Element));
  }
  
  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      Element element = getElementFromEnum(rand() % 5);
      matrix[i][j] = element;
    }
  }
  // while some matrix[i][j].degree > 0, display matrix
  short step = 0;
  while (step < 6) {
    displayMatrix(matrix, randomWidth, randomHeight, step);
    step++;
  }
  free(matrix);
  return 0;
}
