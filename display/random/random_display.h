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
    printf("%s",SPACER);
    for (int j = 0; j < randomWidth; j++) {
      if (matrix[i][j].degree > 1) {
        matrix[i][j].degree -= 1;
      } else if (matrix[i][j].degree == 1) {
        matrix[i][j] = ash;
      } else if (
        matrix[i][j].degree == 0
      ) else {
        matrix[i][j] = extinctAsh;
      }
      printf("%d", matrix[i][j].degree);
    }
    printf("\n");
  }
  printf("\n");
}

void initializeMatrix(Element **matrix, int randomWidth, int randomHeight) {
  for (int i = 0; i < randomHeight; i++) {
    matrix[i] = malloc(randomWidth * sizeof(Element));
  }
  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      Element element = getElementFromEnum(rand() % 5);
      matrix[i][j] = element;
    }
  }
}

void getRandomPosition(int *randomX, int *randomY, int randomWidth, int randomHeight) {
  *randomX = rand() % randomWidth;
  *randomY = rand() % randomHeight;
}

int randomDisplay() {
  // time is used to generate a different number each time we run the program, if we didnt use it, we would get the same number each time
  srand(time(NULL));
  int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  int randomHeight = (rand() % MAX_WIDTH) + MIN_WIDTH;
  // To debug only
  printf("Width: %d, Height: %d\n", randomWidth, randomHeight);
  Element **forestMatrix = malloc(randomHeight * sizeof(Element *));
  initializeMatrix(forestMatrix, randomWidth, randomHeight);
  displayMatrix(forestMatrix, randomWidth, randomHeight, 0);

  int randomX = 0;
  int randomY = 0;
  while (forestMatrix[randomY][randomX].degree == 0) {
    getRandomPosition(&randomX, &randomY, randomWidth, randomHeight);
  }
  forestMatrix[randomY][randomX].state = 1;
  
  free(forestMatrix);
  return 0;
}
