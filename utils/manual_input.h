#include <stdio.h>
#include <stdlib.h>
#include "../bean/typeElement.h"
#include "./display_grid.h"

Element detectionElement(char symbol){
    switch ((char) symbol)
    {
    case '+':
        return ground;
    case '*':
        return tree;
    case ' ':
        return leaf;
    case '#':
        return rock;
    case 'x':
        return herb;
    case '/':
        return water;
    case '-':
        return ash;
    case '@':
        return extinctAsh;
    default:
        printf("Le caractère %c est interdis.",symbol);

        //In case the user inputs a char not possible
        Element error = { '!', '!', 0, 0 };
        return error;
    }


}

int createElementArray(){
    int height, width;
    scanf("%d %d",&height,&width);
    //Initialize a pointer pointer
    Element** tab = NULL;
    //Allocate the necessary memory to it
    tab = ( Element **) malloc(height * sizeof( Element*));
    if(tab == NULL) {
        return -1;
    }

    for(int ligne = 0;ligne < height;ligne++) {
         Element* line = NULL;
        line = ( Element*) malloc((width) * sizeof( Element*));
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

        //fgets(reader, width, stdin);
        scanf("%s", reader);
        for (int colonne = 0;colonne < width;colonne++){
            Element character = detectionElement(*(reader + colonne));
            //check the error code
            if (character.symbol != '!'){
                tab[ligne][colonne] = character ;
            }

            else
            {
                return -1;
            }
            
        }

        free(reader);
    }

    //display_grid_and_degree(tab,height,width);
    display_grid_arg2(tab,height,width,'s','t');
    return 0;
}