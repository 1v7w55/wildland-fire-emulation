#include <stdio.h>
#include <stdlib.h>
#include "./bean/typeElement.h"

int createElementArray(){
    int height, width;
    scanf("%d %d",&height,&width);
    //Initialize a pointer pointer
    struct Element** tab = NULL;
    //Allocate the necessary memory to it
    tab = (struct Element **) malloc(height * sizeof(struct Element*));
    if(tab == NULL) {
        return -1;
    }

    for(int ligne = 0;ligne < height;ligne++) {
        struct Element* line = NULL;
        line = (struct Element*) malloc((width) * sizeof(struct Element*));
        if(line == NULL) {
            free(tab);
            return -2;
        }

        *(tab + ligne) = line;
        char * reader = NULL;
        reader = (char*) malloc((width + 1) * sizeof(char*));
        //Add one to the width because of the last char of every string '\0'
        if(reader == NULL) {
            free(tab);
            return -3;
        }

        scanf("%s", reader);
        for (int colonne = 0;colonne < width;colonne++){
            tab[ligne][colonne].symbol = *(reader + colonne);
        }

        free(reader);
    }

    //afficherGrille(tab,height,width);
    return 0;
}