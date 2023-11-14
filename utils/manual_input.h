#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bean/typeElement.h"
#include "./display_grid.h"

void freeMatrix(Element** matrix, size_t height) {
  for (size_t i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

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
        printf("Le caractère '%c' est interdis.",symbol);

        //In case the user inputs a char not possible
        Element error = { '!', '!', 0, 0 };
        return error;
    }


}

int createElementArray(){
    int height, width;
    scanf("%d %d",&height,&width);
    printf("\n");
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

        scanf("%[^\n]", reader);
        printf("1");
        printf("%s",reader);
        printf("1");
        for (int colonne = 0;colonne < width;colonne++){
            Element character = detectionElement(*(reader + colonne));
            //check the error code
            if (character.symbol != '!'){
                tab[ligne][colonne] = character ;
            }

            else{
                return -1;
            }
            
        }

        free(reader);
    }

    //display_grid_arg2(tab,height,width,'S','d');
    return 0;
}


int readFile(){

    int check=0;
    char chemin[150] = "./saves/";
    FILE *userInupts ;
    
    while (check == 0)
    {
        printf("Entrez le nom de vore fichier mis dans le dossier save (avec l'extention): ");
        char nameFile[100];
        scanf("%s",nameFile);
        //strcat(chemin, nameFile);
        snprintf(chemin,sizeof(chemin),"./saves/%s",nameFile);
        //On ouvre le fichier
        userInupts = fopen(chemin,"r");
        
        if (userInupts == NULL){
            check=0;
            printf("Erreur lors de l'ouverture du fichier\n");
            printf("Le chemin %s n'existe pas.\n",chemin);
    
        } else {
            check=1;
        }

    }

    int height, width;
    
    int result = fscanf(userInupts,"%d %d",&height,&width);
    if (result == EOF){
        printf("Erreur lors de la lecture du fichier");
        return -1;
    }
    
    Element** tab = NULL;
    //Allocate the necessary memory to it
    tab = ( Element **) malloc(height * sizeof( Element*));
    if(tab == NULL) {
        return -1;
    }
    
    for(int ligne = 0;ligne < height+1;ligne++) {
        char * reader = NULL;
        reader = (char*) malloc((width + 1) * sizeof(char*));
        //Add one to the width because of the last char of every string '\0'
        if(reader == NULL) {
            return -3;
        }

        fgets(reader,width+2,userInupts);
        if (ligne==0){
            continue;
        }
        Element* line = NULL;
        line = ( Element*) malloc((width) * sizeof( Element*));
        if(line == NULL) {
            free(tab);
            return -2;
        }

        *(tab + ligne-1) = line;
        
        for (int colonne = 0;colonne < width;colonne++){
            Element character = detectionElement(*(reader + colonne));
            //check the error code
            if (character.symbol != '!'){
                tab[ligne-1][colonne] = character ;
            }

            else{
                return -1;
            }
            
        
        }
        free(reader);
        
    }
    result = fclose(userInupts);
    if (result == EOF){
        printf("Erreur lors de la fermeture du fichier");
        return -1;
    }
    //freeMatrix(tab,height);
    //display_grid_arg2(tab, height, width, 'S','d');

    return 0;
}