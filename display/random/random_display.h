#ifndef RANDOM_DISPLAY_H
#define RANDOM_DISPLAY_H

#include "../../config/global.h"
#include "../../bean/type_element.h"
#include "../../bean/type_point.h"
#include <stdio.h>
#include <stdlib.h>


void freeMatrix(Element** matrix, size_t height);
void displayMatrix(Element** matrix, size_t width, size_t height);
void initializeMatrix(Element** matrix, size_t width, size_t height);
void getRandomPosition(unsigned short* randomX, unsigned short* randomY, unsigned short width, unsigned short height);
void initFire(int randomX, int randomY, Element** forestMatrix);
void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* points, size_t* pointIndex);
int randomDisplay();

#endif