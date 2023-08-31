#ifndef FOREST_H
#define FOREST_H
#pragma once
#include <stddef.h>
#include <time.h>

#define MAXWIDTH 10
#define MIXWIDTH 4


/*This structure makes it possible to specify the characterization of the elements of the forest*/
struct Element {
  char type;
  char symbol;
  unsigned short degree;
  unsigned short state;
};

#endif 