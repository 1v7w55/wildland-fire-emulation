#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#include "mode-random.h"

static struct Element elements[] = {
  {'F', '+', 0, 0},
  {'T', '*', 4, 0},
  {'L', ' ', 2, 0},
  {'R', '#', 5, 0},
  {'H', 'x', 3, 0},
  {'W', '/', 0, 0},
  {'A', '-', 1, 0},
};


/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */
int main() {
  srand(time(NULL)); 

  int randomWidth = (rand() % 10) + 4;
  int randomHeight = (rand() % 10) + 4;

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