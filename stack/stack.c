#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

stack *forestStack = NULL;

void push(Element **map, size_t width, size_t height) {
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

	newElement->prec = forestStack;
	forestStack = newElement;
}

void pop(Element ***map, size_t width, size_t height) {
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

	free(toPop->adresseCarte);
	free(toPop);
}
