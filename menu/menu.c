#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "../core/simulation.h"
#include "../stack/stack.h"
#include "../config/global.h"
#include "../utils/memory.h"
#include "../utils/input.h"
#include "../utils/dijkstra.h"
#include "menu.h"

const size_t MAX_FILENAME_LENGTH = 100;

//Allows you to display the menu before the start of the game
void menu() {
  int gameMode;
  printf("Bienvenue dans l'emulation d'incendie en milieu forestier\n");
  do {
    printf("Veuillez choisir le mode de jeu que vous souhaitez ? \n");
    printf("\t1 - Charger une carte\n");
    printf("\t2 - Generer aleatoirement une carte\n");
    printf("\t3 - Quitter\n");
    // Read user choice
    scanf("%d", &gameMode);
    switch (gameMode) {
      case 1:
        chooseOption();
        return;
      case 2:
        randomForestCreation();
        return;
      case 3:
        leave();
        return;
      default:
        printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
  }
  leave();
  } while (1);
}

//Allows you to leave the game with player confirmation
void leave() {
  char giveUp[2];
  printf("Etes-vous sur de vouloir quitter la partie ? (y/n) ");
  fgets(giveUp, 2, stdin);
  scanf("%s", giveUp);    
  if (tolower(giveUp[0]) == 'y') {
    exit(0);
  } else {
    menu();
  }
}

void loadGrid() {
  char filename[MAX_FILENAME_LENGTH];
  int height, width;

  printf("Entrez le nom du fichier de la grille à charger (avec l'extension): ");
  scanf("%s", filename);

  Element** forestMatrix = loadGridFromFile(filename, &height, &width);
  if (forestMatrix != NULL) {
    Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * height * width);
    if (!listPointsOnFire) {
      fprintf(stderr, "%s", ERROR_MEMORY);
      freeMatrix(forestMatrix, height);
      return;
    }

    size_t pointIndex = 0;
    size_t randomX, randomY;
    do {
      getRandomPosition(&randomX, &randomY, width, height);
    } while (forestMatrix[randomY][randomX].degree == 0);

    listPointsOnFire[pointIndex].x = randomX;
    listPointsOnFire[pointIndex].y = randomY;
    pointIndex++;

    displayMatrix(forestMatrix, width, height);

    push(forestMatrix, width, height, listPointsOnFire, pointIndex);
    bool displayMenu = true;
    processFireSpread(forestMatrix, width, height, listPointsOnFire, &pointIndex, &displayMenu);

    while (forestStack != NULL) {
      pop(&forestMatrix, width, height, listPointsOnFire, &pointIndex);
    }

    free(listPointsOnFire);
    freeMatrix(forestMatrix, height);
  } else {
    printf("Échec du chargement de la grille.\n");
  }
}

void chooseOption() {
  int option;
  while (1) {
    printf("Veuillez choisir le mode d'input que vous souhaitez ? \n");
    printf("\t1 - Charger une carte à partir d'un fichier\n");
    printf("\t2 - Charger à partir du terminal\n");

    if (scanf("%d", &option) != 1) {
      printf("Entrée invalide.\n");
      while (getchar() != '\n'); 
      continue;
    }

    switch (option) {
      case 1:
        loadGrid();
        return;
      case 2:
        createElementArray();
        return;
      default:
        printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
    }
  }
}