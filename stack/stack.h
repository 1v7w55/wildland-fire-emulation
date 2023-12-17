#ifndef STACK_h
#define STACK_h

#include "../core/forest.h"
#include <stddef.h>

typedef struct stack {
	Element** adresseCarte;
	Point* tabCoordFeu;
	size_t nbFlames;
	struct stack *prec;
} stack;

extern stack *forestStack;

void push(Element **map, size_t width, size_t height);
void pop(Element ***map, size_t width, size_t height);

#endif
