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

void processFireSpread(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex) {
    displayMatrix(forestMatrix, width, height);
    setFire(randomX, randomY, width, height, forestMatrix, listPointsOnFire, pointIndex);
  
    for (size_t i = 0; i < *pointIndex; i++) {
        setFire(listPointsOnFire[i].x, listPointsOnFire[i].y, width, height, forestMatrix, listPointsOnFire, pointIndex);
        displayMatrix(forestMatrix, width, height);
        for (size_t j = 0; j < *pointIndex; j++) {
            if (forestMatrix[listPointsOnFire[j].y][listPointsOnFire[j].x].degree > 0) {
                forestMatrix[listPointsOnFire[j].y][listPointsOnFire[j].x].degree--;
            }
        }
    }
}

int randomForestCreation() {
  Element** forestMatrix = NULL;
  srand(time(NULL));
  // By default and for developpment, we wanna get a random width and height
  gridWidth = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  gridHeight = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  // TODO: Ask user if he wants to set a custom width and height
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
  processFireSpread(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex);
  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
  return 0;
}