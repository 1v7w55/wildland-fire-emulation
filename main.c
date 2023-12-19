/**
 * @file main.c
 * @brief project lead
 * @version 1.0 01/09/2023
 * Projet C - ESIEA
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./menu/menu.h"
#include "./config/global.h"
#include "./config/error.h"

const size_t MAX_WIDTH = 10;
const size_t MIN_WIDTH = 4;
const size_t MAX_HEIGHT = 10;
const size_t MIN_HEIGHT = 4;

size_t gridWidth, gridHeight;
size_t pointIndex, fireSpreadStep;
size_t randomX, randomY;

bool fireSpreadCompleted = false;
bool hasUserRolledBack = false;
const char SPACER[] = "\t";
const char ERROR_MEMORY[] = "Memory allocation failed.\n";

void displayLogo() {
    printf("\n");
    printf("██╗    ██╗██╗██╗     ██████╗ ██╗      █████╗ ███╗   ██╗██████╗     ███████╗██╗██████╗ ███████╗\n");
    printf("██║    ██║██║██║     ██╔══██╗██║     ██╔══██╗████╗  ██║██╔══██╗    ██╔════╝██║██╔══██╗██╔════╝\n");
    printf("██║ █╗ ██║██║██║     ██║  ██║██║     ███████║██╔██╗ ██║██║  ██║    █████╗  ██║██████╔╝█████╗  \n");
    printf("██║███╗██║██║██║     ██║  ██║██║     ██╔══██║██║╚██╗██║██║  ██║    ██╔══╝  ██║██╔══██╗██╔══╝  \n");
    printf("╚███╔███╔╝██║███████╗██████╔╝███████╗██║  ██║██║ ╚████║██████╔╝    ██║     ██║██║  ██║███████╗\n");
    printf(" ╚══╝╚══╝ ╚═╝╚══════╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝\n");
}

void afficherBienvenue() {
    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  Bienvenue sur notre projet d'émulation d'incendie, \"Wildland Fire Emulation\".              ║\n");
    printf("║  Ce projet consiste à simuler la propagation d'un incendie au sein d'un milieu forestier,   ║\n");
    printf("║  où chaque parcelle représente différents éléments tels que: de l'herbe, un arbre,          ║\n");
    printf("║  de la pierre, de l'eau, de la feuille, etc...                                              ║\n");
    printf("║  Choisissez votre génération préférée !                                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

int main() {
    srand(time(NULL)); 
    displayLogo();
    afficherBienvenue();
    menu();
    return 0;
}
