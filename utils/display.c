#include "display.h"
#include <stdio.h>

// Définitions des fonctions pour l'affichage
int display_grid( Element **tab,int height,int width,char type1){
  for (int colonne = 0;colonne < width;colonne++){
    switch ((char) type1){
    case 'S':
      printf("%c", tab[height][colonne].symbol);
      break;
    case 's':
      printf("%d", tab[height][colonne].state);
      break;
    case 'd':
      printf("%d", tab[height][colonne].degree);
      break;
    case 't':
      printf("%c", tab[height][colonne].type);
      break;
    default:
      printf("Il y a une erreur");
      return -1;
    }
  }
  return 0;
}
