#include <ctype.h>
#include <stdio.h>
#include "./starting_menu.h"
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
        createElementArray();
      case 2:
        randomDisplay();
        return;
      case 3:
        leave();
        return;
      default:
        printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
  }
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
