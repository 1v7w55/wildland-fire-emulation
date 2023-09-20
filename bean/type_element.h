#ifndef FOREST_H
#define FOREST_H

/*
** This structure makes it possible to specify the characterization of the elements of the forest
** type : anagram of the letter
** symbol : symbol of the element 
** degree : degree of the element, which is the health of the element
** state : state of the element if it is on fire (1) or not (0)
*/

typedef struct {
  char type;
  char symbol;
  unsigned short degree;
  unsigned short state;
} Element;

// For each value, we assign it the characteristics described in the topic
Element ground = { 'F', '+', 0, 0 };
Element tree = { 'T', '*', 4, 0 };
Element leaf = { 'L', ' ', 2, 0 };
Element rock = { 'R', '#', 5, 0 };
Element water = { 'W', '/', 0, 0 };
Element herb = { 'H', 'x', 3, 0 };
Element ash = { 'A', '-', 1, 0 };
Element extinctAsh = { 'E', '@', 0, 0 };

#endif 