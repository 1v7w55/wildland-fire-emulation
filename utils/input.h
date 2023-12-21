#ifndef INPUT_H
#define INPUT_H

#include "../core/forest.h"

int manualForestCreation();
void chooseOption();
Element** loadGridFromFile(const char* filename, int* outHeight, int* outWidth);
Element** createElementArray();
void fromTerminal();
void freeGrid(Element **grid, int height);

#endif
