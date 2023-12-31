#include "input.h"
#include "../core/simulation.h"
#include "../utils/input.h"
#include "../config/global.h"
#include "../core/simulation.h"
#include "../stack/stack.h"
#include "./memory/memory.h"
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

  if (fscanf(file, "%ld %ld\n", &gridHeight, &gridWidth) != 2) {
    printf("Erreur lors de la lecture des dimensions du fichier.\n");
    fclose(file);
    return NULL;
  }

  Element **grid = (Element **)malloc(gridHeight * sizeof(Element *));
  if (grid == NULL) {
    fclose(file);
    return NULL;
  }

  for (int i = 0; i < gridHeight; i++) {
    char *line = malloc((gridWidth + 2) * sizeof(char));
    if (line == NULL) {
      fclose(file);
      freeGrid(grid, i);
      return NULL;
    }

    if (fgets(line, gridWidth + 2, file) == NULL) {
      fclose(file);
      freeGrid(grid, i);
      free(line);
      return NULL;
    }
    line[strcspn(line, "\n")] = 0;
    grid[i] = parseLine(line, gridWidth);
    if (grid[i] == NULL) {
      fclose(file);
      freeGrid(grid, i);
      free(line);
      return NULL;
    }
    free(line);
  }
  fclose(file);
  *outHeight = gridHeight;
  *outWidth = gridWidth;
  return grid;
}

void processForestMatrix(Element** forestMatrix) {
  size_t pointIndex = 0;
  Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  if (!listPointsOnFire) {
    fprintf(stderr, "Erreur d'allocation mémoire pour les points de feu.\n");
    freeMatrix(forestMatrix, gridHeight);
    return;
  }

  size_t randomX = rand() % gridWidth;
  size_t randomY = rand() % gridHeight;
  listPointsOnFire[pointIndex].x = randomX;
  listPointsOnFire[pointIndex].y = randomY;
  pointIndex++;

  displayMatrix(forestMatrix);

  bool displayMenu = true;
  fireSpreadStep = 0;
  processFireSpread(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex, &displayMenu);

  while (forestStack != NULL) {
    pop(&forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex);
  } 

  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
}

void fromTerminal() {
  forestMatrix = createElementArray();
  if (forestMatrix != NULL) {
    processForestMatrix(forestMatrix);
  }
}

Element** createElementArray() {
  printf("Entrez les dimensions (longueur largeur) suivies de la grille :\n");

  if (scanf("%zu %zu", &gridHeight, &gridWidth) != 2) {
    fprintf(stderr, "Erreur de lecture des dimensions.\n");
    return NULL;
  }
  getchar(); 

  Element **tab = (Element **) malloc(gridHeight * sizeof(Element *));
  if (tab == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    return NULL;
  }

  char *lineBuffer = (char *) malloc((gridWidth + 2) * sizeof(char));
  if (lineBuffer == NULL) {
    free(tab);
    fprintf(stderr, "Erreur d'allocation mémoire pour lineBuffer.\n");
    return NULL;
  }

  for (size_t ligne = 0; ligne < gridHeight; ligne++) {
    if (fgets(lineBuffer, gridWidth + 2, stdin) == NULL) {
      free(lineBuffer);
      for (size_t i = 0; i < ligne; i++) {
        free(tab[i]);
      }
      free(tab);
      fprintf(stderr, "Erreur de lecture de la grille.\n");
      return NULL;
    }

    tab[ligne] = (Element *) malloc(gridWidth * sizeof(Element));
    if (tab[ligne] == NULL) {
      free(lineBuffer);
      for (size_t i = 0; i < ligne; i++) {
        free(tab[i]);
      }
      free(tab);
      fprintf(stderr, "Erreur d'allocation mémoire pour une ligne de la grille.\n");
      return NULL;
    }

    for (size_t colonne = 0; colonne < gridWidth; colonne++) {
      tab[ligne][colonne] = detectionElement(lineBuffer[colonne]);
    }
  }

  free(lineBuffer);
  printf("\n");
  return tab;
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
  fireSpreadStep = 0;
  processFireSpread(forestMatrix, gridWidth, gridHeight, points, &pointIndex, &displayMenu);
  return 0;
}