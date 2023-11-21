#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>

extern const size_t MAX_WIDTH;
extern const size_t MIN_WIDTH;
extern const size_t MAX_HEIGHT;
extern const size_t MIN_HEIGHT;

extern size_t gridWidth, gridHeight;
extern size_t pointIndex, fireSpreadStep;
extern unsigned short randomX, randomY;

extern const char SPACER[];
extern const char ERROR_MEMORY[];

#endif 
