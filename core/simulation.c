#include "simulation.h"
#include "../utils/color.c"
#include "../utils/memory/memory.h"
#include "../utils/input.h"
#include "../core/forest.h"
#include "../config/global.h"
#include "../config/error.h"
#include "../menu/menu.h"
#include "../utils/dijkstra/dijkstra.h"
#include "../utils/save.h"
#include "../stack/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
 */

void displayStep(){
  printf("Etape %ld :\n", fireSpreadStep);
}

void displayMatrix(Element** matrix) {
  for (size_t i = 0; i < gridHeight; i++) {
    for (size_t j = 0; j < gridWidth; j++) {
      getColor(matrix[i][j]);
      printf("%c", matrix[i][j].symbol);
      resetColor();
    }
    printf("\n");
  }
  printf("\n");
}

void initializeMatrix(Element** matrix) {
  for (size_t i = 0; i < gridHeight; i++) {
    matrix[i] = malloc(gridWidth * sizeof(Element));
    if (!matrix[i]) {
      fprintf(stderr, "%s", ERROR_MEMORY);
      freeMatrix(matrix, i);
      exit(1);
    }
  }
  for (size_t i = 0; i < gridHeight; i++) {
    for (size_t j = 0; j < gridWidth; j++) {
      Element element = getElementFromEnum(rand() % 5);
      matrix[i][j] = element;
    }
  }
  push(matrix, gridWidth, gridHeight, listPointsOnFire, pointIndex);
}

void getRandomPosition() {
  randomX = rand() % gridWidth;
  randomY = rand() % gridHeight;
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

void initFire(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex) {
  do {
    getRandomPosition();
  } while (forestMatrix[randomY][randomX].degree == 0);

  if (forestMatrix[randomY][randomX].state != 1) {
    forestMatrix[randomY][randomX].state = 1;
    checkAsh(forestMatrix, randomX, randomY);
    pointOnFire(listPointsOnFire, pointIndex, randomX, randomY);
  }
}

int userMenu(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, bool* displayMenu, stack **forestStack) {
  int userChoice;

  printf("Que voulez-vous faire ? \n");
  printf("1. Continuer\n");
  printf("2. Modifier la grille\n");
  printf("3. Revenir en arrière\n");
  printf("4. Trouver la distance entre deux points\n");
  printf("5. Aller directement à la fin de la propagation du feu\n");
  printf("6. Sauvgarder la partie dans un fichier\n");
  printf("7. Calculer le nombre d'itération nécessaire\n");
  printf("8. Trouver le meilleur point de départ de l'incendie\n");
  printf("9. Quitter la simulation\n");
  scanf("%d", &userChoice);

  switch(userChoice) {
    case 1:
      // Do nothing
      break;
    case 2:
      modifyGridElement(forestMatrix, width, height, listPointsOnFire, pointIndex);
      break;
   case 3: 
      if (*forestStack != NULL && countStackElements(*forestStack) >= 2) {
        pop(&forestMatrix, width, height, listPointsOnFire, pointIndex);
      }
      break;
    case 4:
      menu_dijkstra(forestMatrix, height, width);
      break;
    case 5:
      *displayMenu = false; 
      break;
    case 6:
      save_grid(forestMatrix, height, width);
      break;
    case 7:
      menu_burn_predict(forestMatrix, height, width);
      break;
    case 8:
      menu_fire_predict(forestMatrix, height, width);
      break;
    case 9:
      printf("Etes-vous sur de vouloir quitter la partie ? (y/N) ");
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
  return userChoice;
}

void processFireSpread(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, bool* displayMenu) {
  size_t currentPointIndex;
  size_t newPointsOnFire;
  int userChoice = 0; 
  bool isFireInitialized = false; 
  bool fireSpreadCompleted = false;

  do {
    currentPointIndex = 0;
    newPointsOnFire = 0;
    size_t numberOfPointsOnFire = *pointIndex;

    if (*displayMenu) {
      userChoice = userMenu(forestMatrix, width, height, listPointsOnFire, pointIndex, displayMenu, &forestStack);

      if (userChoice == 3) {
        if (forestStack != NULL) {
          if (fireSpreadStep > 0) fireSpreadStep--;
            if (!hasUserRolledBack) {
              pop(&forestMatrix, width, height, listPointsOnFire, pointIndex);
              hasUserRolledBack = true;
            }
          displayMatrix(forestMatrix);
          displayStep();
        } else {
          pop(&forestMatrix, width, height, listPointsOnFire, pointIndex);
        }
      }
    }

    if (!fireSpreadCompleted && (userChoice == 1 || userChoice == 5)) {
      if (!isFireInitialized) {
        for (size_t i = 1; i < *pointIndex; i++) {
          listPointsOnFire[i - 1] = listPointsOnFire[i];
        }
        (*pointIndex)--;

        initFire(forestMatrix, width, height, listPointsOnFire, pointIndex);
        isFireInitialized = true;
        displayMatrix(forestMatrix);
        displayStep();
        if (*displayMenu) {
          userChoice = userMenu(forestMatrix, width, height, listPointsOnFire, pointIndex, displayMenu, &forestStack);
        }
      }

      if (isFireInitialized || userChoice == 5) {
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
        fireSpreadStep++;
        displayMatrix(forestMatrix);
        displayStep();
        push(forestMatrix, width, height, listPointsOnFire, *pointIndex);
      }
    }

    if (newPointsOnFire == 0) {
      fireSpreadCompleted = true;
      *displayMenu = true;
      for (size_t i = 0; i < *pointIndex; i++) {
        if (forestMatrix[listPointsOnFire[i].y][listPointsOnFire[i].x].degree > 0) {
          newPointsOnFire++;
          fireSpreadCompleted = false;
        }
      }
    }
  } while (!fireSpreadCompleted || userChoice != 9);
}

void getUserInputForSize() {
  char userChoice;
  printf("Voulez-vous choisir la taille de la forêt (O/n): ");
  scanf(" %c", &userChoice);

  if (userChoice == 'O' || userChoice == 'o') {
    printf("Choissez la largeur : ");
    scanf("%zu", &gridWidth);
    printf("Choissez la longueur : ");
    scanf("%zu", &gridHeight); 
  } else {
    gridWidth = (rand() % (MAX_WIDTH - MIN_WIDTH + 1)) + MIN_WIDTH;
    gridHeight = (rand() % (MAX_HEIGHT - MIN_HEIGHT + 1)) + MIN_HEIGHT;
  }
}

int randomForestCreation() {
  Element** forestMatrix = NULL;
  srand(time(NULL));
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

  initializeMatrix(forestMatrix);

  size_t pointIndex = 0;
  listPointsOnFire[pointIndex].x = randomX;
  listPointsOnFire[pointIndex].y = randomY;
  pointIndex++;
  fireSpreadStep = 0;
  displayMatrix(forestMatrix);
  displayStep();

  push(forestMatrix, gridWidth, gridHeight, listPointsOnFire, pointIndex);

  bool displayMenu = true;
  processFireSpread(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex, &displayMenu);

  while (forestStack != NULL) {
    printf("e");

    pop(&forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex);
  } 

  free(listPointsOnFire);
  freeMatrix(forestMatrix, gridHeight);
  return 0;
}

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

//Fonction de modifcation de grille
void modifyGridElement(Element** forestMatrix, size_t width, size_t height,  Point* listPointsOnFire, size_t* pointIndex){
  printf("Votre grille actuelle est :\n");
  displayMatrix(forestMatrix);

  int x,y,temp,state = 0;
  char c;

  printf("Quelles sont les coordonnées de la grille que vous souhaitez modifier ? (Sous forme \"X Y\")\n");
  scanf("%d %d",&x,&y);
  
  printf("Quel élément doit le remplacer ? (Possibilité '+', '*',' ','#','x', '/','-','@')\n");
  scanf(" %c",&c);
  
  printf("Quelle température doit le remplacer ?\n");
  scanf("%d",&temp);

  printf("Quel est le statut ? (0 = éteint et 1 = allumé) \n");
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
    } else {
      return;
    }
    if (state == 1) {
      pointOnFire(listPointsOnFire, pointIndex, x, y);
      checkAsh(forestMatrix, x, y);
    }
    push(forestMatrix, width, height, listPointsOnFire, *pointIndex);
  }
  else {
    printf("Le caractère n'est pas valide\n");
  }
  return;
}

//Vérifie pour l'ensemeble des points de la liste listPointsOnFire si leur etat ne dois pas passé a ExtinctAsh
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

//Vérifie si une cellule a une température de 2 et donc doit changer de symbole
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