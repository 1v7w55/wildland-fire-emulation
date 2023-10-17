#include "../bean/type_element.h"
#include "./display_grid.h"
#include "./detect_element.h"

int createElementArray(){
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
      fprintf(stderr, ERROR_MEMORY);
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
  Point* points = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  setFire(0, 0, gridWidth, gridHeight, forestMatrix, points, &pointIndex);
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  for (size_t i = 0; i < pointIndex; i++) {
    displayMatrix(forestMatrix, gridWidth, gridHeight);
    setFire(points[i].x, points[i].y, gridWidth, gridHeight, forestMatrix, points, &pointIndex);
    for (size_t j = 0; j < pointIndex; j++) {
      if (forestMatrix[points[j].y][points[j].x].degree > 0) {
          forestMatrix[points[j].y][points[j].x].degree--;
      }
    }
  }
  return 0;
}