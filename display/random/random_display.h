#include "../../config/global.h"
#include "../../config/error_message.h"
#include "../../bean/type_element.h"
#include "../../bean/type_point.h"
#include "../../enum/element.h"

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */
 
// Freeing up memory space of the matrix
void freeMatrix(Element** matrix, size_t height) {
  for (size_t i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void getColor(int degree) {
  switch(degree) {
    case 0:
      printf("%s", COLOR_WHITE);
      return;
    case 1:
      printf("%s", COLOR_RED);
      return;
    case 2:
      printf("%s", COLOR_YELLOW);
      return;
    default:
      printf("%s", COLOR_GREEN);
      return;
  } 
}

void displayMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      getColor(matrix[i][j].degree);
      printf("%c", matrix[i][j].symbol);
      printf("%s", COLOR_RESET);
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
  printf("Etape : %ld\n", step);
  step++;
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

void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* points, size_t* pointIndex) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (randomY + i >= 0 && randomY + i < height && randomX + j >= 0 && randomX + j < width &&
        forestMatrix[randomY + i][randomX + j].state != 1 &&
        forestMatrix[randomY + i][randomX + j].degree > 0) {
        forestMatrix[randomY + i][randomX + j].state += 1;
        forestMatrix[randomY + i][randomX + j].symbol = 'F';
        points[*pointIndex].x = randomX + j;
        points[*pointIndex].y = randomY + i;
        (*pointIndex)++;
      }
    }
  }
}

int randomDisplay() {
  srand(time(NULL));
  size_t randomWidth = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  size_t randomHeight = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
  Point* points = (Point*)malloc(sizeof(Point) * randomHeight * randomWidth);
  if (!points) {
    fprintf(stderr, ERROR_MEMORY);
    return 1;
  }
  Element** forestMatrix = (Element**)malloc(randomHeight * sizeof(Element*));
  if (!forestMatrix) {
    fprintf(stderr, ERROR_MEMORY);
    free(points);
    return 1;
  }
  initializeMatrix(forestMatrix, randomWidth, randomHeight);
  // We don't want to start the fire on a element with degree 0, so we loop until we find one
  do {
      getRandomPosition(&randomX, &randomY, randomWidth, randomHeight);
  } while (forestMatrix[randomY][randomX].degree == 0);
  // TODO: We need to display this first time to see the first step of the fire, change to only call one function
  displayMatrix(forestMatrix, randomWidth, randomHeight);
  // we set the fire on the random position
  initFire(randomX, randomY, forestMatrix);
  // TODO: Same as above, we need to display this first time to see the first step of the fire
  displayMatrix(forestMatrix, randomWidth, randomHeight);
  setFire(randomX, randomY, randomWidth, randomHeight, forestMatrix, points, &pointIndex);
  // For each point in the array, we set the fire on the point and we add the new points to the array
  for (size_t i = 0; i < pointIndex; i++) {
    displayMatrix(forestMatrix, randomWidth, randomHeight);
    setFire(points[i].x, points[i].y, randomWidth, randomHeight, forestMatrix, points, &pointIndex);
    // Browse all points and removing 1 degree
    for (size_t j = 0; j < pointIndex; j++) {
      if (forestMatrix[points[j].y][points[j].x].degree > 0) {
        forestMatrix[points[j].y][points[j].x].degree--;
      }
    }
  }
  free(points);
  freeMatrix(forestMatrix, randomHeight);
  return 0;
}
