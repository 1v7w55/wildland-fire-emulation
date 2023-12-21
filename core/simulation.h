#ifndef SIMULATION_H
#define SIMULATION_H

#include "forest.h"
#include <stddef.h>
#include <stdbool.h>

void displayMatrix(Element** matrix);
void displayStep(size_t fireSpreadStep);
void initializeMatrix(Element** matrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex);
void getRandomPosition(size_t* randomX, size_t* randomY, size_t width, size_t height);
void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex);
int randomForestCreation();
void modifyGridElement(Element** forestMatrix, size_t width, size_t heigh,  Point* listPointsOnFire, size_t* pointIndex);
void pointOnFire(Point* listPointsOnFire, size_t* pointIndex,int x,int y);
void checkExtinctAsh(Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex);
void checkAsh (Element** forestMatrix,int x, int y);
void processFireSpread(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, bool* displayMenu);

#endif
