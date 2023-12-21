#include "forest.h"
#include <stdio.h>

// For each value, we assign it the characteristics described in the topic
Element ground = { 'F', '+', 0, 0 };
Element tree = { 'T', '*', 4, 0 };
Element leaf = { 'L', ' ', 2, 0 };
Element rock = { 'R', '#', 5, 0 };
Element water = { 'W', '/', 0, 0 };
Element herb = { 'H', 'x', 3, 0 };
Element ash = { 'A', '-', 1, 0 };
Element extinctAsh = { 'E', '@', 0, 0 };

Element detectionElement(char symbol) {
  switch (symbol) {
    case '+':
      return ground;
    case '*':
      return tree;
    case ' ':
      return leaf;
    case '#':
      return rock;
    case 'x':
      return herb;
    case '/':
      return water;
    case '-':
      return ash;
    case '@':
      return extinctAsh; 
    default:
      printf("Le caractère %c est interdit.\n", symbol);
      Element error = { '!', '!', 0, 0 };
      return error;
  }
}

// Element return based on the element in the enum
Element getElementFromEnum(int elementEnum) {
switch (elementEnum) {
  case GROUND:
    return ground;
  case TREE:
    return tree;
  case LEAF:
    return leaf;
  case ROCK:
    return rock;
  case WATER:
    return water;
  case HERB:
    return herb;
  case ASH:
    return ash;
  case EXTINCTASH:
    return extinctAsh;
  default:
    return ground; 
  }
}
