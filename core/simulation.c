#include "simulation.h"
#include "../utils/color.c"
#include "../utils/memory.h"
#include "../core/forest.h"
#include "../config/global.h"
#include "../config/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
      fprintf(stderr, "%s", ERROR_MEMORY);
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

void initFire(int randomX, int randomY, Element** forestMatrix) {
  forestMatrix[randomY][randomX].state += 1;
  forestMatrix[randomY][randomX].symbol = '-';
}

void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int newY = randomY + i;
      int newX = randomX + j;
      if (newY >= 0 && newY < height && newX >= 0 && newX < width) {
        Element *adjacentCell = &forestMatrix[newY][newX];
        if (adjacentCell->state != 1 && adjacentCell->degree > 0) {
          adjacentCell->state += 1;
          adjacentCell->degree -= 1;
          adjacentCell->symbol = '-';
          listPointsOnFire[*pointIndex].x = newX;
          listPointsOnFire[*pointIndex].y = newY;
          (*pointIndex)++;
        }
      }
    }
  }
}

void processFireSpread(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex) {
  size_t currentPointIndex;
  size_t newPointsOnFire;

  do {
    currentPointIndex = 0;
    newPointsOnFire = 0;  
    size_t numberOfPointsOnFire = *pointIndex;

    while (currentPointIndex < numberOfPointsOnFire) {
      Point p = listPointsOnFire[currentPointIndex];
      if (forestMatrix[p.y][p.x].degree > 0) {
        size_t oldPointIndex = *pointIndex;
        setFire(p.x, p.y, width, height, forestMatrix, listPointsOnFire, pointIndex);
        if (*pointIndex > oldPointIndex) {
          newPointsOnFire += (*pointIndex - oldPointIndex);
        }
      }
      currentPointIndex++;
    }

    for (size_t i = 0; i < numberOfPointsOnFire; i++) {
      Point p = listPointsOnFire[i];
      if (forestMatrix[p.y][p.x].degree > 0) {
        forestMatrix[p.y][p.x].degree--;
        if (forestMatrix[p.y][p.x].degree == 0) {
          forestMatrix[p.y][p.x].symbol = '@';  
        }
      }
    }

    displayMatrix(forestMatrix, width, height);

    if (newPointsOnFire == 0) {
      for (size_t i = 0; i < *pointIndex; i++) {
        if (forestMatrix[listPointsOnFire[i].y][listPointsOnFire[i].x].degree > 0) {
          newPointsOnFire++;
        }
      }
    }
  } while (newPointsOnFire > 0);
}

int randomForestCreation() {
  Element** forestMatrix = NULL;
  srand(time(NULL));
  gridWidth = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  gridHeight = (rand() % (MAX_HEIGHT - MAX_HEIGHT + 1)) + MAX_HEIGHT;
  Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  if (!listPointsOnFire) {
    fprintf(stderr, "%s", ERROR_MEMORY);
    return 1;
  }
  forestMatrix = (Element**)malloc(gridHeight * sizeof(Element*));
  if (forestMatrix == NULL) {
    fprintf(stderr, "%s", ERROR_MEMORY);
    free(listPointsOnFire);
    return 1;
  }
  // FUTUR matrix returning
  initializeMatrix(forestMatrix, gridWidth, gridHeight);

  // Todo: make another function with elements below
  do {
      getRandomPosition(&randomX, &randomY, gridWidth, gridHeight);
  } while (forestMatrix[randomY][randomX].degree == 0);
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  initFire(randomX, randomY, forestMatrix);
  size_t pointIndex = 0;
  listPointsOnFire[pointIndex].x = randomX;
  listPointsOnFire[pointIndex].y = randomY;
  pointIndex++;
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  processFireSpread(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex);
  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
  return 0;
}