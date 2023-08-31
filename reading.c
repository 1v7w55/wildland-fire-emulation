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
    
    for(int i = 0;i < height;i++) {
        char* line = NULL;
        line = (char *) malloc((width+1) * sizeof(char*));
        if(line == NULL) {
            free(tab);
            return -2;
        }

        scanf("%s", line);
        *(tab + i) = line;
    }
    
    printf("\n");
    for(int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++){
            //printf("tableau[%d][%d] = %c\n", i, j, *(*(tab + i) + j));
            printf("%c", *(*(tab + i) + j));
        }

        printf("\n");
    }

    return 0;
}



