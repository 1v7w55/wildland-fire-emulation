#include "global.h"
#include "../stack/stack.h"

const size_t MAX_WIDTH = 10;
const size_t MIN_WIDTH = 4;
const size_t MAX_HEIGHT = 10;
const size_t MIN_HEIGHT = 4;

size_t gridWidth, gridHeight;
size_t pointIndex, fireSpreadStep;

size_t iterationCounter;
Element** forestMatrix = NULL;
Point* listPointsOnFire = NULL;
size_t pointIndex = 0;
size_t randomX, randomY;

const size_t MAX_FILENAME_LENGTH = 100;

stack *forestStack = NULL;

bool fireSpreadCompleted = false;
bool hasUserRolledBack = false;

const char SPACER[] = "\t";
const char ERROR_MEMORY[] = "Memory allocation failed.\n";
