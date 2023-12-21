#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>
#include <stdbool.h>
#include "../core/forest.h"
#include "../stack/stack.h"

extern const size_t MAX_WIDTH;
extern const size_t MIN_WIDTH;
extern const size_t MAX_HEIGHT;
extern const size_t MIN_HEIGHT;

extern size_t gridWidth, gridHeight;
extern size_t pointIndex, fireSpreadStep;
extern size_t randomX, randomY;

extern const size_t MAX_FILENAME_LENGTH;

extern stack *forestStack;

extern size_t iterationCounter;
extern Element** forestMatrix;
extern Point* listPointsOnFire;
extern size_t pointIndex;

extern bool fireSpreadCompleted;
extern bool hasUserRolledBack;

extern const char SPACER[];
extern const char ERROR_MEMORY[];

#endif 
