#include "input.h"
#include "../core/simulation.h"
#include "../utils/input.h"
#include "../config/global.h"
#include "../core/simulation.h"
#include <stdio.h>
#include <stdlib.h>

int manualForestCreation(){
  Element** forestMatrix = NULL;
  scanf("%ld %ld",&gridHeight,&gridWidth);
  //Initialize a pointer pointer
  //Allocate the necessary memory to it
  forestMatrix = ( Element **) malloc(gridHeight * sizeof( Element*));
  if(forestMatrix == NULL) {
    return -1;
  }
  for(int i = 0;i < gridHeight;i++) {
    Element* line = NULL;
    line = ( Element*) malloc((gridWidth) * sizeof( Element*));
    if(line == NULL) {
      free(forestMatrix);
      return -2;
    }
    *(forestMatrix + i) = line;
    char* reader = NULL;
    reader = (char*) malloc((gridWidth + 1) * sizeof(char*));
    //Add one to the gridWidth because of the last char of every string '\0'
    if(reader == NULL) {
      fprintf(stderr, "%s", ERROR_MEMORY);
      free(forestMatrix);
      return -3;
    }
    //fgets(reader, gridWidth, stdin);
    scanf("%s", reader);
    for (int colonne = 0;colonne < gridWidth;colonne++){
      Element character = detectionElement(*(reader + colonne));
      //check the error code
      if (character.symbol != '!'){
        forestMatrix[i][colonne] = character ;
      }
      else {
        return -1;
      };
    }
    free(reader);
  }
  // END OF PROCESSING DATA FROM USER
  Point* points = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  setFire(0, 0, gridWidth, gridHeight, forestMatrix, points, &pointIndex);
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  processFireSpread(forestMatrix, gridWidth, gridHeight, points, &pointIndex);
  return 0;
}