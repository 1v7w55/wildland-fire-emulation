#include "stack.h"
#include "../config/global.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

stack *forestStack = NULL;
size_t iterationCounter;

void push(Element **map, size_t width, size_t height, Point* listPointsOnFire, size_t pointIndex) {
	stack *newElement = malloc(sizeof(stack));
	if (!newElement) {
		printf("Memory allocation failed for new stack element.\n");
		return;
	}

	newElement->adresseCarte = malloc(height * sizeof(Element*));
	for (size_t i = 0; i < height; i++) {
		newElement->adresseCarte[i] = malloc(width * sizeof(Element));
		memcpy(newElement->adresseCarte[i], map[i], width * sizeof(Element));
	}

	newElement->iteration = iterationCounter;

	newElement->tabCoordFeu = malloc(pointIndex * sizeof(Point));
	memcpy(newElement->tabCoordFeu, listPointsOnFire, pointIndex * sizeof(Point));
	newElement->nbFlames = pointIndex;

	newElement->prec = forestStack;
	forestStack = newElement;
}

void pop(Element ***map, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex) {
	if (!forestStack) {
		printf("Stack is empty, cannot pop.\n");
		return;
	}

	stack *toPop = forestStack;
	forestStack = toPop->prec;

	for (size_t i = 0; i < height; i++) {
		memcpy((*map)[i], toPop->adresseCarte[i], width * sizeof(Element));
		free(toPop->adresseCarte[i]);
	}

	memcpy(listPointsOnFire, toPop->tabCoordFeu, toPop->nbFlames * sizeof(Point));
	*pointIndex = toPop->nbFlames;

	fireSpreadStep = toPop->iteration;

	free(toPop->adresseCarte);
	free(toPop->tabCoordFeu);
	free(toPop);
}

void popSecondLast(Element ***map, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex) {
	fireSpreadCompleted = false;
	if (!forestStack || !forestStack->prec) {
		printf("La pile est vide.\n");
		return;
	} 
	stack *topElement = forestStack;
	forestStack = forestStack->prec;
	freeStackElement(topElement, height);

	stack *secondLastElement = forestStack;
	forestStack = secondLastElement->prec;

	restoreStateFromStackElement(map, width, height, listPointsOnFire, pointIndex, secondLastElement);

	freeStackElement(secondLastElement, height);
}

void freeStackElement(stack *element, size_t height) {
	if (!element) {
		return;
	}
	for (size_t i = 0; i < height; i++) {
		free(element->adresseCarte[i]);
	}
	free(element->adresseCarte);
	free(element->tabCoordFeu);
	free(element);
}

int countStackElements(stack *s) {
    int count = 0;
    while (s != NULL) {
        count++;
        s = s->prec;  
    }
    return count;
}

void restoreStateFromStackElement(Element ***map, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, stack *element) {
	if (!element) {
		return;
	}

	for (size_t i = 0; i < height; i++) {
		memcpy((*map)[i], element->adresseCarte[i], width * sizeof(Element));
	}

	memcpy(listPointsOnFire, element->tabCoordFeu, element->nbFlames * sizeof(Point));
	*pointIndex = element->nbFlames;
}
