#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "./config/global.h"
#include "./bean/element.h"

// Initialize values for individual elements
static struct Element elements[] = {
  // Floor
  {'F', '+', 0, 0},
  // Tree
  {'T', '*', 4, 0},
  // Leaf
  {'L', ' ', 2, 0},
  // Rock
  {'R', '#', 5, 0},
  // Herb
  {'H', 'x', 3, 0},
  // Water
  {'W', '/', 0, 0},
  // Ash
  {'A', '-', 1, 0},
  // Extinct ash
  {'E', '@', 0, 0}
};

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

int main() {
  srand(time(NULL)); 

  int randomWidth = (rand() % MAX_WIDTH) + MIN_WIDTH;
  int randomHeight = (rand() % MAX_WIDTH) + MIN_WIDTH;

  printf("Width: %d, Height: %d\n", randomWidth, randomHeight);

  for (int i = 0; i < randomHeight; i++) {
    for (int j = 0; j < randomWidth; j++) {
      struct Element element = elements[rand() % (sizeof elements / sizeof elements[0])];
      printf("%c", element.symbol);
    }
    printf("\n");
  }

  return 0;
}