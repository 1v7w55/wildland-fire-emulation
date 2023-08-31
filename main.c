#include <stdio.h>
// use to add random numbers (rand())
#include <stdlib.h>     
// At each execution, the seed is set to a value obtained from the system clock,
// if we don't use srand(),the same number will be generated every time
#include <time.h>
#include "createElements.h"

int main() {
  createElements();
  // srand is used to generate random numbers, we need to set a seed to obtains a different number at each execution
  srand( time( NULL ) );
  // we create an array of elements to get a random one on the display
  struct Element elementsList[] = {ground, tree, leaf, rock, herb, water};
  int randomWidth = (rand() % 10) + 4;
  int randomHeight = (rand() % 10) + 4;
  printf("Width: %d, Height: %d \n", randomWidth, randomHeight);
  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      printf("%c", elementsList[(rand() % (sizeof elementsList / sizeof elementsList[0]))].symbol);
      //DEBUG to display degree only
      // printf("%d", elementsList[(rand() % (sizeof elementsList / sizeof elementsList[0]))].degree);
    }

    printf("\n");
  }
  return 0;
}