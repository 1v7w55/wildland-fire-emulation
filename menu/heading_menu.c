/**
 * @file heading_menu.c
 * @brief The set of functions used for the menu
 * @version 1.0 01/09/2023
 * Projet C - ESIEA
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
//#include "heading_menu.h"
#include "../display/random/random_display.h"


// Allows you to display the menu before the start of the game
void menu() {
    int gameMode;
    int quit = 0;
    printf("Bienvenue dans l'emulation d'incendie en milieu forestier\n");
    while (!quit) { 
        printf("Veuillez choisir le mode de jeu que vous souhaitez ? \n");
        printf("\t1 - Charger une carte\n");
        printf("\t2 - Generer aleatoirement une carte\n");
        printf("\t3 - Besoin d'aide\n");
        printf("\t4 - Quitter\n");
        // Read user choice
        scanf("%d", &gameMode);
        switch (gameMode) {
            case 1:
                // Sacha's code here
                break; 
            case 2:
                randomDisplay();
                break;
            case 3:
                printf("blabal");    
                menu;
            case 4:
                quit = 1; 
                break; 
            default:
                printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
        }
    }
}

// Allows you to leave the game with player confirmation
void leave() {
    char giveUp[2];
    printf("Etes-vous sur de vouloir quitter la partie ? (y/n) ");
    scanf("%1s", giveUp); 
    if (tolower(giveUp[0]) == 'y') {
        exit(0);
    } else {
        menu();
    }
}
