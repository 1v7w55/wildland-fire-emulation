#include "../core/simulation.h"
#include <stdio.h>
#define MAX_STR 100

void save_grid(Element** matrix,int height, int width){
    char nomFichier [MAX_STR];
    printf("Nom de la sauvegarede :");
    scanf("%s",nomFichier);

    FILE *fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
      fprintf(fichier, "%d %d\n", height, width);
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
            fprintf(fichier, "%c", matrix[i][j].symbol);
            }
            fprintf(fichier, "\n");
        }
    fclose(fichier);
    printf("Le fichier a bien été enregistré dans le dossier save.");

    }
    else{
        printf("Une erreur est sur venue. La sauvegarde n'a pas fonctionné.\n");
    }
    return;
}