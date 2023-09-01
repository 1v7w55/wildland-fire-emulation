#include "../../config/global.h"
#include "../../bean/type_element.h"
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
    // To debug, uncomment the following lines
    printf("%s",SPACER);
    for (int j = 0; j < randomWidth; j++) {
      printf("%d", matrix[i][j].degree);
    }
    printf("%s",SPACER);
    for (int j = 0; j < randomWidth; j++) {
      printf("%d", matrix[i][j].state);
    }
    // to this line
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

void initFire(int randomX,int randomY, int randomWidth, int randomHeight, Element **forestMatrix) {
  forestMatrix[randomY][randomX].state += 1;
  forestMatrix[randomY][randomX].symbol = 'F';
}

void setFire(int randomX,int randomY, int randomWidth, int randomHeight, Element **forestMatrix) {
  // create a list of coordinates 
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
      if(
        // we check if the position is out of bounds
        randomY - 1 + i < 0 
        || randomY - 1 + i >= randomHeight 
        || randomX - 1 + j < 0 
        || randomX - 1 + j >= randomWidth
        // we also need to check if the element has already been set on fire
        || forestMatrix[randomY - 1 + i][randomX - 1 + j].state == 1
        // last check, if element .degree == 0, we dont set it on fire
        || forestMatrix[randomY - 1 + i][randomX - 1 + j].degree == 0
        ){
        continue;
      }
      // if the point has degre > 0 and is not already on fire, we set it on fire
      forestMatrix[randomY - 1 + i][randomX - 1 + j].state += 1;
      forestMatrix[randomY - 1 + i][randomX - 1 + j].symbol = 'F';
    }
  } 
}

int randomDisplay() {
  // time is used to generate a different number each time we run the program, if we didnt use it, we would get the same number each time
  srand(time(NULL));
  unsigned int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  unsigned int randomHeight = (rand() % MAX_WIDTH) + MIN_WIDTH;
  Element **forestMatrix = malloc(randomHeight * sizeof(Element *));
  initializeMatrix(forestMatrix, randomWidth, randomHeight);
  
  do {
    getRandomPosition(&randomX, &randomY, randomWidth, randomHeight);
    // Do avoid fire on a position where there is no possibility (degree == 0), we keep generating a new random position until we find one that has a degree > 0
  } while (forestMatrix[randomY][randomX].degree == 0);

  displayMatrix(forestMatrix, randomWidth, randomHeight, 0);
  initFire(randomX, randomY, randomWidth, randomHeight, forestMatrix);
  
  displayMatrix(forestMatrix, randomWidth, randomHeight, 1);
  setFire(randomX, randomY, randomWidth, randomHeight, forestMatrix);
  
  displayMatrix(forestMatrix, randomWidth, randomHeight, 2);
  
  free(forestMatrix);
  return 0;
}
