#ifndef STACK_h
#define STACK_h

#include "../core/forest.h"
#include <stddef.h>

typedef struct stack {
    Element** adresseCarte;
    Point* tabCoordFeu;
    size_t nbFlames;
    int iteration; 
    struct stack *prec;
} stack;

void push(Element **map, size_t width, size_t height, Point* listPointsOnFire, size_t pointIndex);
void pop(Element ***map, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex);
void freeStackElement(stack *element, size_t height);
void restoreStateFromStackElement(Element ***map, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, stack *element);
int countStackElements(stack *s);

#endif
