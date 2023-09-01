#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "heading_menu.h"
#include "../display/random/random_display.h"


void menu() {
    int gameMode;
    char firstname[100];

    printf("Comment t'appelles-tu ? \n");
    fgets(firstname, 100, stdin);
    firstname[strcspn(firstname, "\n")] = '\0';
    printf("Salut %s, enchante de te rencontrer ! \n", firstname);
    printf("Bienvenue dans l'emulation d'incendie en milieu forestier\n");

    // Utilisez une boucle pour permettre à l'utilisateur de choisir le mode de jeu.
    while (1) {
        printf("Veuillez choisir le mode de jeu que vous souhaitez ? \n");
        printf("\t1 - Charger une carte\n");
        printf("\t2 - Generer aleatoirement une carte\n");
        printf("\t3 - Quitter\n");
        
        // Lire le choix de l'utilisateur
        scanf("%d", &gameMode);

        switch (gameMode) {
            case 1:
                // Code pour le mode 1 (Charger une carte)
                printf("3");

            case 2:
                randomDisplay();
                return;
            case 3:
                quitter();
                return; // Sortir de la fonction menu() après avoir quitté.
            default:
                printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
        }
    }
}

void quitter() {
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
