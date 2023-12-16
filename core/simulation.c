#include "simulation.h"
#include "../utils/color.c"
#include "../utils/memory.h"
#include "../utils/input.h"
#include "../core/forest.h"
#include "../config/global.h"
#include "../config/error.h"
#include "../menu/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

void displayMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      getColor(matrix[i][j]);
      printf("%c", matrix[i][j].symbol);
      resetColor();
    }
    // DEBUG ONLY
    printf("%s", SPACER);
    for (size_t j = 0; j < width; j++) {
      printf("%d", matrix[i][j].degree);
    }
    printf("%s", SPACER);
    for (size_t j = 0; j < width; j++) {
      printf("%d", matrix[i][j].state);
    }
    // END DEBUG
    printf("\n");
  }
  // DEBUG ONLY
  printf("Etape : %ld\n", fireSpreadStep);
  fireSpreadStep++;
  // END DEBUG
  printf("\n");
}

void initializeMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    matrix[i] = malloc(width * sizeof(Element));
    if (!matrix[i]) {
      fprintf(stderr, "%s", ERROR_MEMORY);
      freeMatrix(matrix, i);
      exit(1);
    }
  }
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      Element element = getElementFromEnum(rand() % 5);
      matrix[i][j] = element;
    }
  }
}

// TODO : issue with size_t so we use unsigned short
void getRandomPosition(unsigned short* randomX, unsigned short* randomY, unsigned short width, unsigned short height) {
  *randomX = rand() % width;
  *randomY = rand() % height;
}

void initFire(int randomX, int randomY, Element** forestMatrix) {
  forestMatrix[randomY][randomX].state = 1;
  checkAsh (forestMatrix, randomX, randomY);
}

void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int newY = randomY + i;
      int newX = randomX + j;
      if (newY >= 0 && newY < height && newX >= 0 && newX < width) {
        Element *adjacentCell = &forestMatrix[newY][newX];
        if (adjacentCell->state != 1 && adjacentCell->degree > 0) {
          adjacentCell->state = 1;
          checkAsh (forestMatrix, newX, newY);
          pointOnFire(listPointsOnFire, pointIndex, newX, newY);
        }
      }
    }
  }
}

void userMenu(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, size_t* numberOfPointsOnFire, bool* displayMenu) {
  int userChoice;

  printf("Que voulez-vous faire ? \n");
  printf("1. Continuer\n");
  printf("2. Modifier la grille\n");
  printf("3. Revenir en arrière (PAS IMPLEMENTE)\n");
  printf("4. Trouver la distance entre deux points (PAS IMPLEMENTE)\n");
  printf("5. Aller directement à la fin de la propagation du feu.\n");
  printf("6. Quitter la simulation\n");
  scanf("%d", &userChoice);

  switch(userChoice) {
    case 1:
      // do nothing, then continue
      break;
    case 2:
      modifyGridElement(forestMatrix, width, height,  listPointsOnFire, pointIndex);
    case 3:
      // TODO:  add possibility to rollback
      break;
    case 4:
      // TODO: IMPLEMENT dijkstra here
      break;
    case 5:
      *displayMenu = false; 
      break;
    case 6:
      printf("Etes-vous sur de vouloir quitter la partie ? (Y/N) ");
      char confirmQuit;
      scanf(" %c", &confirmQuit); 
      if (confirmQuit == 'y' || confirmQuit == 'Y') {
          freeGrid(forestMatrix, height);
          menu();
      }
      break;
    default:
      printf("Choix non valide. Nous allons continuer.\n");
  }
}

void processFireSpread(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, bool* displayMenu) {
  size_t currentPointIndex;
  size_t newPointsOnFire;
  bool isFireInitialized = false;

  do {
    currentPointIndex = 0;
    newPointsOnFire = 0;  
    size_t numberOfPointsOnFire = *pointIndex;
    if (*displayMenu) {
      userMenu(forestMatrix, width, height, listPointsOnFire, pointIndex, &numberOfPointsOnFire, displayMenu);
    }
    if (!isFireInitialized) {
      initFire(randomX, randomY, forestMatrix);
      isFireInitialized = true;
    }
    while (currentPointIndex < numberOfPointsOnFire) {
      Point p = listPointsOnFire[currentPointIndex];
      if (forestMatrix[p.y][p.x].degree > 0) {
        size_t oldPointIndex = *pointIndex;
        setFire(p.x, p.y, width, height, forestMatrix, listPointsOnFire, pointIndex);
        if (*pointIndex > oldPointIndex) {
          newPointsOnFire += (*pointIndex - oldPointIndex);
        }
      }
      currentPointIndex++;
    }
    checkExtinctAsh(forestMatrix, listPointsOnFire, pointIndex);
    displayMatrix(forestMatrix, width, height);

    if (newPointsOnFire == 0) {
      for (size_t i = 0; i < *pointIndex; i++) {
        if (forestMatrix[listPointsOnFire[i].y][listPointsOnFire[i].x].degree > 0) {
          newPointsOnFire++;
        }
      }
    }
  } while (newPointsOnFire > 0);
  displayMatrix(forestMatrix, width, height);
}

void getUserInputForSize(int *width, int *height) {
  char userChoice;
  printf("Voulez-vous choisir la taille de la forêt (Y/N): ");
  scanf(" %c", &userChoice);

  if (userChoice == 'y' || userChoice == 'Y') {
    printf("Choissez la largeur : ");
    scanf("%d", width);
    printf("Choissez la longueur : ");
    scanf("%d", height);
  } else {
    *width = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
    *height = (rand() % (MAX_HEIGHT - MIN_HEIGHT + 1)) + MIN_HEIGHT;
  }
}

int randomForestCreation() {
  Element** forestMatrix = NULL;
  srand(time(NULL));
  int gridWidth, gridHeight;
  getUserInputForSize(&gridWidth, &gridHeight);
  Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
  if (!listPointsOnFire) {
    fprintf(stderr, "%s", ERROR_MEMORY);
    return 1;
  }
  forestMatrix = (Element**)malloc(gridHeight * sizeof(Element*));
  if (forestMatrix == NULL) {
    fprintf(stderr, "%s", ERROR_MEMORY);
    free(listPointsOnFire);
    return 1;
  }
  // FUTUR matrix returning
  initializeMatrix(forestMatrix, gridWidth, gridHeight);

  // Todo: make another function with elements below
  do {
      getRandomPosition(&randomX, &randomY, gridWidth, gridHeight);
  } while (forestMatrix[randomY][randomX].degree == 0);
  size_t pointIndex = 0;
  listPointsOnFire[pointIndex].x = randomX;
  listPointsOnFire[pointIndex].y = randomY;
  pointIndex++;
  displayMatrix(forestMatrix, gridWidth, gridHeight);
  bool displayMenu = true;
  processFireSpread(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex, &displayMenu);
  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
  return 0;
}

//Ajoute le point (XY) a la list des feux on ne fait risi il n'y est pas
void pointOnFire(Point* listPointsOnFire, size_t* pointIndex,int x,int y){
  for(int i=0;i<(*pointIndex);i++){
      if (listPointsOnFire[i].x == x && listPointsOnFire[i].y == y ){
        return;
      }
  }
  listPointsOnFire[*pointIndex].x = x;
  listPointsOnFire[*pointIndex].y = y;
  (*pointIndex)++;
  return;
}

void modifyGridElement(Element** forestMatrix, size_t width, size_t height,  Point* listPointsOnFire, size_t* pointIndex){
  printf("Votre grille actuel est :\n");
  displayMatrix(forestMatrix, width, height);

  int x,y,temp,state = 0;
  char c;

  printf("Quel sont les coordonnées de la grille voulez vous modifier ? (Sous forme \"X Y\")\n");
  scanf("%d %d",&x,&y);
  
  printf("Quel élément doit le remplacer ? (Possibilité '+', '*',' ','#','x', '/','-','@')\n");
  scanf(" %c",&c);
  
  printf("Quel température doit le remplacer ?\n");
  scanf("%d",&temp);

  printf("Quel est le statue ? (0 = éteint et 1 = allumé) \n");
  scanf("%d",&state);

  Element character = detectionElement(c);
  if (character.symbol != '!'){
    forestMatrix[y][x] = character ;
    if (temp < 0) {
      temp = 0;
    }
    forestMatrix[y][x].degree = temp;
    if (state <= 1 && state >=0){
      forestMatrix[y][x].state = state;
    }else{
      return;
    }
    //si passe de allumé a étein supprimer de la liste (TO DO)
    if (state==1){
      //ajouter x y a la list des éléments en feu
      pointOnFire(listPointsOnFire, pointIndex, x, y);
      checkAsh(forestMatrix, x, y);
    }
  }
  else{
    printf("Le charactère n'est pas valide\n");
  }
  return;
}


//Vérifie pour l'ensemebel des points de la liste listPointsOnFire si leur etat ne dois pas passer a ExtinctAsh
void checkExtinctAsh(Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex){
  for (size_t i = 0; i < (*pointIndex); i++) {
    Point p = listPointsOnFire[i];
    if (forestMatrix[p.y][p.x].degree > 0) {
      forestMatrix[p.y][p.x].degree--;
    }
    checkAsh (forestMatrix,p.x, p.y);
  }
  return;
}
//Vérifie si une cellule a une température de 2 et docn doit changé de symbole
void checkAsh (Element** forestMatrix,int x, int y){
  Element *adjacentCell = &forestMatrix[y][x];
  if (adjacentCell->degree == 1){
    adjacentCell->symbol = '-';
  }
  if (adjacentCell->degree == 0){
    adjacentCell->symbol = '@';
  }
  return;
}