/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define bool unsigned int

struct element {
    const char caractère;
    const short unsigned degre;
    bool etat;
};



int main()
{
    int l,L;
    //l=ligne L=colonne
    scanf("%d %d",&l,&L);
    

    
    
    char** tab = NULL;
    
    tab = (char **) malloc( l * sizeof(char*) );
    
    if(tab == NULL) return -1;
    
    
    
    for(int i=0;i<l;i++){
        
        char* ligne=NULL;
        ligne = (char *) malloc( (L+1) * sizeof(char*) );
        
        if(ligne == NULL) {
            free(tab);
            return -2;
        }
        scanf("%s",ligne);
        *(tab+i)=ligne;
        
    }
 
    printf("\n");

    for(int i=0;i<l;i++){
        for (int j=0;j<L;j++){
            //printf("Tab[%d][%d] = %c\n", i, j, *(*(tab + i) + j));
            printf("%c",*(*(tab + i) + j));
            
        }
        printf("\n");
        
    }
    return 0;
}



