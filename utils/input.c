#include "input.h"
#include "../core/simulation.h"
#include "../utils/input.h"
#include "../config/global.h"
#include "../core/simulation.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 150
#define MAX_FILENAME_LENGTH 100

void freeGrid(Element **grid, int height) {
  for (int i = 0; i < height; i++) {
    free(grid[i]);
  }
  free(grid);
}

Element *parseLine(char *line, int width) {
  Element *row = malloc(width * sizeof(Element));
  if (row == NULL) {
    return NULL;
  }

  for (int i = 0; i < width; i++) {
    row[i] = detectionElement(line[i]);
    if (row[i].symbol == '!') {
      free(row);
      return NULL;
    }
  }
  return row;
}

int loadGridFromFile(Element ***grid) {
  char path[MAX_PATH_LENGTH] = "./saves/";
  char fileName[MAX_FILENAME_LENGTH];
  FILE *file;

  printf("Vous pouvez ajouter votre fichier de sauvegarde au dossier save du programme. Si cela n'est pas déjà fait.\n");
  do {
    printf("Entrez le nom de votre fichier mis dans le dossier save (avec l'extension): ");
    scanf("%s", fileName);
    snprintf(path, sizeof(path), "./saves/%s", fileName);
    file = fopen(path, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        printf("Le chemin %s n'existe pas.\n", path);
    }
  } while (file == NULL);

  int height, width;
  if (fscanf(file, "%d %d", &height, &width) != 2) {
    printf("Erreur lors de la lecture du fichier\n");
    fclose(file);
    return -1;
  }

  *grid = (Element **) malloc(height * sizeof(Element *));
  if (*grid == NULL) {
    fclose(file);
    return -1;
  }

  for (int i = 0; i < height; i++) {
    char *line = malloc((width + 2) * sizeof(char));
    if (line == NULL) {
        fclose(file);
        freeGrid(*grid, i);
        return -1;
    }

    fgets(line, width + 2, file);
    if (i == 0) {
        free(line);
        continue;
    }

    (*grid)[i-1] = parseLine(line, width);
    if ((*grid)[i-1] == NULL) {
      fclose(file);
      freeGrid(*grid, i);
      free(line);
      return -1;
    }
    free(line);
  }

  if (fclose(file) == EOF) {
    freeGrid(*grid, height);
    printf("Erreur lors de la fermeture du fichier\n");
    return -1;
  }

  return 0;
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
    line = ( Element*) malloc((width) * sizeof( Element*));
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
    //printf("%s",reader);

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