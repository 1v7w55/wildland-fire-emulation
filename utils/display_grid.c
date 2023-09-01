#include <stdio.h>
#include <stdlib.h>
#include "../bean/typeElement.h"

int display_grid(Element **tab,int height,int width){
    printf("\n");
    for(int ligne = 0;ligne < height;ligne++) {
        for (int colonne = 0;colonne < width;colonne++){
            printf("%c", tab[ligne][colonne].symbol);
        }

        printf("\n");
    }

    return 0;
}