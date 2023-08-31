#include <stdio.h>
// use to add random numbers (rand())
#include <stdlib.h>     
// At each execution, the seed is set to a value obtained from the system clock,
// if we don't use srand(),the same number will be generated every time
#include <time.h>
#include "createElements.h"
#include "config.h"

void createElements() {
  createGroundElement();
  createTreeElement();
  createLeafElement();
  createHerbElement();
  createRockElement();
  createWaterElement();
  createAshElement();
  createExtinctAshElement();
}

int main() {
  createElements();
  // srand is used to generate random numbers, we need to set a seed to obtains a different number at each execution
  srand(time(NULL));
  // we create an array of elements to get a random one on the display
  struct Element elementsList[] = {ground, tree, leaf, rock, herb, water};
  int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  int randomHeight = (rand() % MAX_HEIGHT) + MIN_HEIGHT;
  printf("Width: %d, Height: %d \n", randomWidth, randomHeight);
  for (int height = 0; height < randomHeight; height++) {
    for (int width = 0; width < randomWidth; width++) {
      // (sizeof elementsList / sizeof elementsList[0]) is used to get the size of the array, because we can't get it directly
      printf("%d", elementsList[(rand() % (sizeof elementsList / sizeof elementsList[0]))].degree);
    }
    printf("\n");
  }
  return 0;
}