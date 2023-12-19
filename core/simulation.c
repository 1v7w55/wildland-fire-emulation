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

#define MAX_ITERATIONS 100 

/**
 * This program generates a random width and height for an output,
 * and then prints a random symbol from an array for each row and column of the output.
*/


typedef struct {
    Element** matrix;
    size_t width;
    size_t height;
} IterationHistory;

size_t iterationCount = 0;
IterationHistory* history = NULL;


void freeHistory(IterationHistory* history, size_t count, size_t width) {
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < width; j++) {
            free(history[i].matrix[j]);
        }
        free(history[i].matrix);
    }
    free(history);
}

void displayMatrix(Element** matrix, size_t width, size_t height) {
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      getColor(matrix[i][j]);
      printf("%c", matrix[i][j].symbol);
      resetColor();
    }
    // Display the previous iteration of the matrix if available
    if (iterationCount > 0) {
      for (size_t j = 0; j < width; j++) {
        printf("%c", history[iterationCount - 1].matrix[i][j].symbol);
      }
    }
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
  forestMatrix[randomY][randomX].state += 1;
  forestMatrix[randomY][randomX].symbol = '-';
}

void setFire(int randomX, int randomY, size_t width, size_t height, Element** forestMatrix, Point* listPointsOnFire, size_t* pointIndex) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int newY = randomY + i;
      int newX = randomX + j;
      if (newY >= 0 && newY < height && newX >= 0 && newX < width) {
        Element *adjacentCell = &forestMatrix[newY][newX];
        if (adjacentCell->state != 1 && adjacentCell->degree > 0) {
          adjacentCell->state += 1;
          adjacentCell->degree -= 1;
          adjacentCell->symbol = '-';
          listPointsOnFire[*pointIndex].x = newX;
          listPointsOnFire[*pointIndex].y = newY;
          (*pointIndex)++;
        }
      }
    }
  }
}

void userMenu(Element** forestMatrix, size_t width, size_t height, Point* listPointsOnFire, size_t* pointIndex, size_t* numberOfPointsOnFire, bool* displayMenu) {
  int userChoice;

  printf("Que voulez-vous faire ? \n");
  printf("1. Continuer\n");
  printf("2. Modifier la grille (PAS IMPLEMENTE)\n");
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
      // TODO: add possibility to modify grid
    case 3:
      // TODO:  add possibility to rollback
    case 4:
      // TODO: IMPLEMENT dijkstra here
      break;
    case 5:
      *displayMenu = false; 
      break;
    case 6:
      printf("Etes-vous sur de vouloir quitter la partie ? (y/n) ");
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
    displayMatrix(forestMatrix, width, height);
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

    for (size_t i = 0; i < numberOfPointsOnFire; i++) {
      Point p = listPointsOnFire[i];
      if (forestMatrix[p.y][p.x].degree > 0) {
        forestMatrix[p.y][p.x].degree--;
        if (forestMatrix[p.y][p.x].degree == 0) {
          forestMatrix[p.y][p.x].symbol = '@';  
        }
      }
    }

    if (newPointsOnFire == 0) {
      for (size_t i = 0; i < *pointIndex; i++) {
        if (forestMatrix[listPointsOnFire[i].y][listPointsOnFire[i].x].degree > 0) {
          newPointsOnFire++;
        }
      }
    }
  } while (newPointsOnFire > 0);
}

void getUserInputForSize(int *width, int *height) {
  char userChoice;
  printf("Voulez-vous choisir la taille de la forêt (O/n): ");
  scanf(" %c", &userChoice);

  if (userChoice == 'o' || userChoice == 'O') {
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
    srand(time(NULL));
    int gridWidth, gridHeight;
    getUserInputForSize(&gridWidth, &gridHeight);
    Point* listPointsOnFire = (Point*)malloc(sizeof(Point) * gridHeight * gridWidth);
    if (!listPointsOnFire) {
        fprintf(stderr, "%s", ERROR_MEMORY);
        return 1;
    }
    Element** forestMatrix = (Element**)malloc(gridHeight * sizeof(Element*));
    if (forestMatrix == NULL) {
        fprintf(stderr, "%s", ERROR_MEMORY);
        free(listPointsOnFire);
        return 1;
    }
    initializeMatrix(forestMatrix, gridWidth, gridHeight);

    unsigned short randomX, randomY;
    getRandomPosition(&randomX, &randomY, gridWidth, gridHeight);

    size_t pointIndex = 0;
    listPointsOnFire[pointIndex].x = randomX;
    listPointsOnFire[pointIndex].y = randomY;
    pointIndex++;

    displayMatrix(forestMatrix, gridWidth, gridHeight);
    bool displayMenu = true;
    size_t iterationCount = 0;

    IterationHistory* history = (IterationHistory*)malloc(MAX_ITERATIONS * sizeof(IterationHistory));
    if (history == NULL) {
        fprintf(stderr, "%s", ERROR_MEMORY);
        free(listPointsOnFire);
        freeMatrix(forestMatrix, gridHeight);
        return 1;
    }

    size_t newPointsOnFire;  // Ajout de la déclaration manquante
    do {
        size_t currentPointIndex = 0;
        newPointsOnFire = 0;  // Initialisation de la variable
        size_t numberOfPointsOnFire = pointIndex;

        if (displayMenu) {
            userMenu(forestMatrix, gridWidth, gridHeight, listPointsOnFire, &pointIndex, &numberOfPointsOnFire, &displayMenu);
        }

        if (iterationCount < MAX_ITERATIONS) {
            history[iterationCount].matrix = malloc(gridHeight * sizeof(Element*));
            for (size_t i = 0; i < gridHeight; i++) {
                history[iterationCount].matrix[i] = malloc(gridWidth * sizeof(Element));
                for (size_t j = 0; j < gridWidth; j++) {
                    history[iterationCount].matrix[i][j] = forestMatrix[i][j];
                }
            }
            history[iterationCount].width = gridWidth;
            history[iterationCount].height = gridHeight;
        }

        iterationCount++;

        initFire(randomX, randomY, forestMatrix);
        displayMatrix(forestMatrix, gridWidth, gridHeight);

        while (currentPointIndex < numberOfPointsOnFire) {
            Point p = listPointsOnFire[currentPointIndex];
            if (forestMatrix[p.y][p.x].degree > 0) {
                size_t oldPointIndex = pointIndex;
                setFire(p.x, p.y, gridWidth, gridHeight, forestMatrix, listPointsOnFire, &pointIndex);
                if (pointIndex > oldPointIndex) {
                    newPointsOnFire += (pointIndex - oldPointIndex);
                }
            }
            currentPointIndex++;
        }

        for (size_t i = 0; i < numberOfPointsOnFire; i++) {
            Point p = listPointsOnFire[i];
            if (forestMatrix[p.y][p.x].degree > 0) {
                forestMatrix[p.y][p.x].degree--;
                if (forestMatrix[p.y][p.x].degree == 0) {
                    forestMatrix[p.y][p.x].symbol = '@';  
                }
            }
        }

        if (newPointsOnFire == 0) {
            for (size_t i = 0; i < pointIndex; i++) {
                if (forestMatrix[listPointsOnFire[i].y][listPointsOnFire[i].x].degree > 0) {
                    newPointsOnFire++;
                }
            }
        }
    } while (newPointsOnFire > 0);

    printf("La propagation du feu est terminée après %ld itérations.\n", iterationCount);

    printf("Voulez-vous voir les anciennes itérations ? (O/n): ");
    char userChoice;
    scanf(" %c", &userChoice);

    if (userChoice == 'o' || userChoice == 'O') {
        for (size_t i = 0; i < iterationCount; i++) {
            printf("Ancienne itération %ld :\n", i + 1);
            displayMatrix(history[i].matrix, gridWidth, gridHeight);
        }
    }

    for (size_t i = 0; i < iterationCount && i < MAX_ITERATIONS; i++) {
        for (size_t j = 0; j < gridHeight; j++) {
            free(history[i].matrix[j]);
        }
        free(history[i].matrix);
    }
    free(history);

    free(listPointsOnFire);
    freeMatrix(forestMatrix, gridHeight);

    return 0;
}