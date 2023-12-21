#include "dijkstra.h"
#include "../../core/simulation.h"
#include "../../utils/input.h"
#include "../../config/global.h"
#include "../../utils/color.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Cree le noeud
Node creeNode(int row, int col) {
    Node node;
    node.row = row;
    node.col = col;
    return node;
}

// Verifie si les coordonees sont dans la grilles
int isValid(int row, int col, int height,int width) {
    return ((row >= 0) && (row < height) && (col >= 0) && (col < width));
}

// Algo de dijkstra
int dijkstra(Element** grid,int height, int width, Node src, Node dest, char mode) {
    int** dist = NULL;
    dist = ( int **) malloc(height * sizeof( int*));
    if(dist == NULL) {
        return -1;
    }
    for(int ligne = 0;ligne < height;ligne++) {
        int* line = NULL;
        line = (int*) malloc(width * sizeof(int));
        if(line == NULL) {
            free(dist);
            return -1;
        }
        *(dist + ligne) = line;
    }
    
    // Tableau noeud vu
    int** vu = NULL;
    vu = ( int **) malloc(height * sizeof( int*));
    if(vu == NULL) {
        return -1;
    }
    for(int ligne = 0;ligne < height;ligne++) {
        int* line = NULL;
        line = (int*) malloc(width * sizeof(int));
        if(line == NULL) {
            free(vu);
            return -1;
        }
        *(vu + ligne) = line;
    }


    Node* pre = NULL;
    pre = (Node*)malloc(height * width * sizeof(Node));
    //node précédent pour récupérer le chemin a la fin

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dist[i][j] = INT_MAX;
            vu[i][j] = 0;
            pre[i] = creeNode(-1, -1);
        }
    }
    // Toute les distances a max et les vistes a 0
    dist[src.row][src.col] = 0;
    // dist de src a src =0
    
    int defaultburn = grid[src.row][src.col].degree;

    for (int count = 0; count < height * width - 1; count++){
        int minDist = INT_MAX;
        Node u;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((vu[i][j]==0) && (dist[i][j] < minDist)) {
                    minDist = dist[i][j];
                    u = creeNode(i, j);
                }
            }
        }
        vu[u.row][u.col] = 1;
        // Modif de la dist des noeuds adjacent au notre
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (isValid(u.row + i, u.col + j, height, width) &&
                    (vu[u.row + i][u.col + j] == 0) &&
                    (dist[u.row][u.col] != INT_MAX) &&
                    (dist[u.row][u.col] + 1 < dist[u.row + i][u.col + j])
                    ) {
                        Element *adjacentCell = &grid[u.row + i][u.col + j];
                        if (adjacentCell->degree > 0){
                            dist[u.row + i][u.col + j] = dist[u.row][u.col] + 1;
                            if ( dist[u.row + i][u.col + j] + grid[u.row + i][u.col + j].degree > defaultburn){
                                defaultburn = dist[u.row + i][u.col + j] + grid[u.row + i][u.col + j].degree;
                            }
                            pre[(u.row + i) * width + (u.col + j)] = u;
                        }
                }
            }
        }
    }
    if (mode == 'B'){
        return defaultburn-1;
    }
    else{
        if (dist[dest.row][dest.col] != INT_MAX){
            printf("Points du plus court chemin entre (%d, %d) et (%d, %d):\n", dest.row, dest.col, src.row, src.col);
            display_way(grid,height, width,pre,dest);
            printf("\nLa distance minimale depuis (%d, %d) à (%d, %d) est : %d\n", dest.row, dest.col,src.row, src.col, dist[dest.row][dest.col]);
            printf("Il faudra %d étapes pour que la case soit toalement consumé\n", dist[dest.row][dest.col] + grid[dest.row][dest.col].degree);
        }
        else{
            printf("\nIl est impossible de rejoindre les 2 points avec un chemin de feu\n");
        }

    }
    return 0;
    free(dist);
    free(vu);
    free(pre);
}

void menu_dijkstra(Element** grid,int height, int width) {
    // noeud source et noeud destination

    int srcH, srcW, destH, destW;
    printf("Votre grille actuel est :\n");
    displayMatrix(grid);

    do {
        printf("Quel sont les coordonnées du premier point ? (Sous la forme \"X Y\")\n");
        scanf("%d %d", &srcH, &srcW);
    } while(srcH < 0 || srcH >= height || srcW < 0 || srcW >= width);

    do {
        printf("Quel sont les coordonnées du second point ? (Sous la forme \"X Y\")\n");
        scanf("%d %d", &destH, &destW);
    } while(destH < 0 || destH >= height || destW < 0 || destW >= width);

    Node src = creeNode(srcH, srcW);
    Node dest = creeNode(destH, destW);
    
    dijkstra(grid, height, width, src, dest, 'W');
}

void display_way(Element** matrix, size_t width, size_t height, Node* pre, Node dest) {
    //Afficher le chemin en bleu

    int* chemin = (int *) calloc((height * width )+1, sizeof(int));

    while (dest.row != -1 && dest.col != -1) {
        printf("(%d, %d) ", dest.row, dest.col);
        chemin[dest.row * width + dest.col] = 1;
        dest = pre[dest.row * width + dest.col];
    }
    printf("\nLes espaces sont représenté par %s pour mieux voir le chemin.\n\n","%");
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if (chemin[i * width + j] == 1) {
                if (matrix[i][j].symbol == ' '){
                    printf(COLOR_BLUE "%s" COLOR_RESET,"%"); 
                    // remplace l'espace pour qu'on vois le chemin
                }
                else{
                    printf(COLOR_BLUE "%c" COLOR_RESET,matrix[i][j].symbol);
                }
            } 
            else {
                printf("%c", matrix[i][j].symbol);
            }
        }
        printf("\n");
    }
    free(chemin);
}

void menu_burn_predict(Element** grid,int height, int width) {
    int srcH, srcW;
    printf("Votre grille actuel est :\n");
    displayMatrix(grid);

    do {
        printf("Quel sont les coordonnées du premier point de feu? (Sous la forme \"X Y\")\n");
        scanf("%d %d", &srcH, &srcW);
    } while(srcH < 0 || srcH >= height || srcW < 0 || srcW >= width);

    printf("La carte sera totalement au brulée au bout de %d itération.\n",burn_predict(grid, height, width, srcH, srcW));
}

int burn_predict(Element** grid,int height, int width, int srcH,int srcW ) {
    Node src = creeNode(srcH, srcW);
    Node dest = creeNode(0, 0);
    return dijkstra(grid, height, width, src, dest, 'B');
}

void menu_fire_predict(Element** grid,int height, int width) {
    

    int shortFire = INT_MAX;
    Node shortF = creeNode(0,0);

    int bestFire = 0;
    Node bestF = creeNode(0,0);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ( grid[i][j].degree != 0){
                int res = burn_predict(grid, height, width, i, j);
                if ( res < shortFire){
                    shortFire = res;
                    shortF = creeNode(i,j);
                }
                if ( res > bestFire){
                    bestFire = res;
                    bestF = creeNode(i,j);
                }
            }
        }
    }
    printf("Le meilleur emplacement pour un point de feu qui s'éteint le plus vite est (%d %d).\n",shortF.row,shortF.col);
    printf("Le meilleur emplacement pour un point de feu qui s'éteint le plus lentement est (%d %d).\n",bestF.row,bestF.col);
}