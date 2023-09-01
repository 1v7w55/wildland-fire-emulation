#ifndef FOREST_H
#define FOREST_H
#include <stddef.h>
#include <time.h>


// Define width
#define MAXWIDTH 10
#define MINWIDTH 4


// This structure makes it possible to specify the characterization of the elements of the forest
/*
** type : anagram of the letter
** symbol : symbol of the element 
** degree : degree of the element
** state : state of the element if it is on fire or not
*/
struct Element {
  char type;
  char symbol;
  unsigned short degree;
  unsigned short state;
};

#endif 