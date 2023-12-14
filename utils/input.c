#include "input.h"
#include "../core/simulation.h"
#include "../utils/input.h"
#include "../config/global.h"
#include "../core/simulation.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeGrid(Element **grid, int height) {
  for (int i = 0; i < height; i++) {
    free(grid[i]);
  }
  free(grid);
}

Element *parseLine(char *line, int width) {
  Element *row = malloc(width * sizeof(Element));
  if (row == NULL) {
    printf("Erreur d'allocation mémoire dans parseLine.\n");
    return NULL;
  }
  for (int i = 0; i < width; i++) {
    row[i] = detectionElement(line[i]);
    if (row[i].symbol == '!') {
      printf("Erreur de détection de l'élément. Caractère '%c' non reconnu.\n", line[i]);
      free(row);
      return NULL;
    }
  }
  return row;
}

Element** loadGridFromFile(const char* filename, int* outHeight, int* outWidth) {
  char path[150];
  snprintf(path, sizeof(path), "./saves/%s", filename);

  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Erreur lors de l'ouverture du fichier '%s'.\n", path);
    return NULL;
  }

  int height, width;
  if (fscanf(file, "%d %d\n", &height, &width) != 2) {
    printf("Erreur lors de la lecture des dimensions du fichier.\n");
    fclose(file);
    return NULL;
  }

  Element **grid = (Element **)malloc(height * sizeof(Element *));
  if (grid == NULL) {
    fclose(file);
    return NULL;
  }

  for (int i = 0; i < height; i++) {
    char *line = malloc((width + 2) * sizeof(char));
    if (line == NULL) {
      fclose(file);
      freeGrid(grid, i);
      return NULL;
    }

    if (fgets(line, width + 2, file) == NULL) {
      fclose(file);
      freeGrid(grid, i);
      free(line);
      return NULL;
    }
    line[strcspn(line, "\n")] = 0;
    grid[i] = parseLine(line, width);
    if (grid[i] == NULL) {
      fclose(file);
      freeGrid(grid, i);
      free(line);
      return NULL;
    }
    free(line);
  }
  fclose(file);
  *outHeight = height;
  *outWidth = width;
  return grid;
}

int createElementArray(){
  int height, width;
  scanf("%d %d",&height,&width);
  printf("\n");
  //Initialize a pointer pointer
  Element** tab = NULL;
  //Allocate the necessary memory to it
  tab = ( Element **) malloc(height * sizeof( Element*));
  if(tab == NULL) {
    return -1;
  }
  for(int ligne = 0;ligne < height;ligne++) {
    Element* line = NULL;
    line = (Element*) malloc(width * sizeof(Element));
    if(line == NULL) {
      free(tab);
      return -2;
    }
    *(tab + ligne) = line;
    char * reader = NULL;
    reader = (char*) malloc((width + 1) * sizeof(char*));
    //Add one to the width because of the last char of every string '\0'
    if(reader == NULL) {
      free(tab);
      return -3;
    }
    fgets(reader, width, stdin);
    scanf("%s", reader);

    for (int colonne = 0;colonne < width;colonne++){
      Element character = detectionElement(*(reader + colonne));
      //check the error code
      if (character.symbol != '!'){
        tab[ligne][colonne] = character ;
      }
    }
    free(reader);
  }
  return 0;
}

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
    line = (Element*) malloc(gridWidth * sizeof(Element));
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
    scanf("%s", reader);
    for (int colonne = 0;colonne < gridWidth;colonne++){
      Element character = detectionElement(*(reader + colonne));
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
  // To do: change var declaration because it's useless
  bool displayMenu = true;
  processFireSpread(forestMatrix, gridWidth, gridHeight, points, &pointIndex, &displayMenu);
  return 0;
}