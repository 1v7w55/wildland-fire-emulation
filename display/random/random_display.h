#include "../../config/global.h"
#include "../../bean/element.h"
#include "../../enum/element.h"

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

int randomDisplay() {
  // time is used to generate a different number each time we run the program, if we didnt use it, we would get the same number each time
  srand(time(NULL));
  int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  int randomHeight = (rand() % MAX_WIDTH) + MIN_WIDTH;
  // To debug only
  printf("Width: %d, Height: %d\n", randomWidth, randomHeight);
  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      Element element = getElementFromEnum(rand() % 5);
      // Returning the symbol of the element directly to the output
      printf("%c", element.symbol);
    }
    printf("\n");
  }
}