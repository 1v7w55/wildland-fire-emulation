#include <stdio.h>
#include <stdlib.h>
#include "../bean/typeElement.h"

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

int display_grid_arg2( Element **tab,int height,int width,char type1,char type2){
    printf("\n");
    for(int ligne = 0;ligne < height;ligne++) {
        if (type2 != '!'){
        display_grid(tab,ligne,width,type1);
        printf("\t");
        }
        display_grid(tab,ligne,width,type2);
        printf("\n");

    }
}
