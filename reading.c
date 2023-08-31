#include <stdio.h>
#include <stdlib.h>

int main() {
    int height, width;
    scanf("%d %d",&height,&width);
    char** tab = NULL;
    tab = (char **) malloc(height * sizeof(char*));
    if(tab == NULL) {
        return -1;
    }
    
    for(int ligne = 0;ligne < height;ligne++) {
        char* line = NULL;
        line = (char *) malloc((width+1) * sizeof(char*));
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
