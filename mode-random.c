#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXWIDTH 10
#define MINWIDTH 4

struct Element {
  char type;
  char symbol;
  unsigned short degree;
  unsigned short state;
};

static struct Element elements[] = {
  {'F', '+', 0, 0},
  {'T', '*', 4, 0},
  {'L', ' ', 2, 0},
  {'R', '#', 5, 0},
  {'H', 'x', 3, 0},
  {'W', '/', 0, 0},
  {'A', '-', 1, 0},
};

int main() {
  srand(time(NULL)); 

  int randomWidth = (rand() % MAXWIDTH) + MINWIDTH;
  int randomHeight = (rand() % MAXWIDTH) + MINWIDTH;

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