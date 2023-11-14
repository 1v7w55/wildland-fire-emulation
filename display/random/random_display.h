#include "../../config/global.h"
#include "../../config/error_message.h"
#include "../../bean/type_element.h"
#include "../../bean/type_point.h"
#include "../../enum/element.h"
#include "../../utils/reset_color.h"
#include "../../utils/free_memory.h"

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

void displayMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      getColor(matrix[i][j]);
      printf("%c", matrix[i][j].symbol);
      resetColor();
    }
    // DEBUG ONLY
    printf("%s", SPACER);
    for (size_t j = 0; j < width; j++) {
      printf("%d", matrix[i][j].degree);
    }
    printf("%s", SPACER);
    for (size_t j = 0; j < width; j++) {
      printf("%d", matrix[i][j].state);
    }
    // END DEBUG
    printf("\n");
  }
  // DEBUG ONLY
  printf("Etape : %ld\n", fireSpreadStep);
  fireSpreadStep++;
  // END DEBUG
  printf("\n");
}

void initializeMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    matrix[i] = malloc(width * sizeof(Element));
    if (!matrix[i]) {
      fprintf(stderr, ERROR_MEMORY);
      freeMatrix(matrix, i);
      exit(1);
    }
  }
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      Element element = getElementFromEnum(rand() % 5);
      matrix[i][j] = element;
    }
  }
}

// TODO : issue with size_t so we use unsigned short
void getRandomPosition(unsigned short* randomX, unsigned short* randomY, unsigned short width, unsigned short height) {
  *randomX = rand() % width;
  *randomY = rand() % height;
}

// Find a way to avoid this function and set this into setFire
void initFire(int randomX, int randomY, Element** forestMatrix) {
  forestMatrix[randomY][randomX].state += 1;
  forestMatrix[randomY][randomX].symbol = 'F';
}

void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (randomY + i >= 0 && randomY + i < height && randomX + j >= 0 && randomX + j < width &&
        forestMatrix[randomY + i][randomX + j].state != 1 &&
        forestMatrix[randomY + i][randomX + j].degree > 0) {
        forestMatrix[randomY + i][randomX + j].state += 1;
        forestMatrix[randomY + i][randomX + j].symbol = 'F';
        listPointsOnFire[*pointIndex].x = randomX + j;
        listPointsOnFire[*pointIndex].y = randomY + i;
        (*pointIndex)++;
      }
    }
  }
}

int randomDisplay() {
  Element** forestMatrix = NULL;
  srand(time(NULL));
  // By default and for developpment, we wanna get a random width and height
  gridWidth = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  gridHeight = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  // TODO: Ask user if he wants to set a custom width and height
  Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  if (!listPointsOnFire) {
    fprintf(stderr, ERROR_MEMORY);
    return 1;
  }
  forestMatrix = (Element**)malloc(gridHeight * sizeof(Element*));
  if (forestMatrix == NULL) {
    fprintf(stderr, ERROR_MEMORY);
    free(listPointsOnFire);
    return 1;
  }
  initializeMatrix(forestMatrix, gridWidth, gridHeight);
  // We don't want to start the fire on a element with degree 0, so we loop until we find one
  do {
      getRandomPosition(&randomX, &randomY, gridWidth, gridHeight);
  } while (forestMatrix[randomY][randomX].degree == 0);
  // TODO: We need to display this first time to see the first fireSpreadStep of the fire, change to only call one function
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  // we set the fire on the random position
  initFire(randomX, randomY, forestMatrix);
  // TODO: Same as above, we need to display this first time to see the first fireSpreadStep of the fire
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  setFire(randomX, randomY, gridWidth, gridHeight, forestMatrix, listPointsOnFire, &pointIndex);
  // For each point in the array, we set the fire on the point and we add the new listPointsOnFire to the array
  for (size_t i = 0; i < pointIndex; i++) {
    displayMatrix(forestMatrix, gridWidth, gridHeight);
    setFire(listPointsOnFire[i].x, listPointsOnFire[i].y, gridWidth, gridHeight, forestMatrix, listPointsOnFire, &pointIndex);
    // Browse all listPointsOnFire and removing 1 degree
    for (size_t j = 0; j < pointIndex; j++) {
      if (forestMatrix[listPointsOnFire[j].y][listPointsOnFire[j].x].degree > 0) {
        forestMatrix[listPointsOnFire[j].y][listPointsOnFire[j].x].degree--;
      }
    }
  }
  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
  return 0;
}
