#include <stdio.h>
// use to add random numbers (rand())
#include <stdlib.h>     
// At each execution, the seed is set to a value obtained from the system clock,
// if we don't use srand(),the same number will be generated every time
#include <time.h>

struct Element {
  char type;
  char symbol;
  unsigned short degree;
  // State will be equals to 1 if it's on fire, 0 otherwise
  unsigned short state;
  // Initialize all types that may be on our array
} ground, tree, leaf, rock, water, herb, ash, extinctAsh;

void createGroundElement() {
  ground.type = 'F';
  ground.symbol = '+';
  ground.degree = 0;
  ground.state = 0;
}

void createTreeElement() {
  tree.type = 'T';
  tree.symbol = '*';
  tree.degree = 4;
  tree.state = 0;
}

void createLeafElement() {
  leaf.type = 'L';
  leaf.symbol = ' ';
  leaf.degree = 2;
  leaf.state = 0;
}

void createRockElement() {
  rock.type = 'R';
  rock.symbol = '#';
  rock.degree = 5;
  rock.state = 0;
}

void createHerbElement() {
  herb.type = 'H';
  herb.symbol = 'x';
  herb.degree = 3;
  herb.state = 0;
}

void createWaterElement() {
  water.type = 'W';
  water.symbol = '/';
  water.degree = 0;
  water.state = 0;
}

void createAshElement() {
  ash.type = 'A';
  ash.symbol = '-';
  ash.degree = 1;
  ash.state = 0;
}

void createExtinctAshElement() {
  extinctAsh.type = 'E';
  extinctAsh.symbol = '@';
  extinctAsh.degree = 0;
  extinctAsh.state = 0;
}

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