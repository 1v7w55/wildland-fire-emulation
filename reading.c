#include <stdio.h>
#include <stdlib.h>

int readingInputsString() {
    int height, width;
    scanf("%d %d",&height,&width);
    //Initialize a pointer pointer
    char** tab = NULL;
    //Allocate the necessary memory to it
    tab = (char **) malloc(height * sizeof(char*));
    //Test if memory has been assigned
    if(tab == NULL) {
        return -1;
    }
    
    for(int ligne = 0;ligne < height;ligne++) {
        char* line = NULL;
        line = (char *) malloc((width + 1) * sizeof(char*));
        //Add one to the width because of the last char of every string '\0'
        if(line == NULL) {
            free(tab);
            return -2;
        }

        scanf("%s", line);
        *(tab + ligne) = line;
    }
    
    printf("\n");
    for(int ligne = 0;ligne < height;ligne++) {
        for (int colonne = 0;colonne < width;colonne++){
            //printf("tableau[%d][%d] = %c\n", i, colonne, *(*(tab + i) + colonne));
            printf("%c", *(*(tab + ligne) + colonne));
        }

        printf("\n");
    }

    return 0;
}
