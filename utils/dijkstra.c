#include "dijkstra.h"
#include "../core/simulation.h"
#include "../utils/input.h"
#include "../config/global.h"
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
    return (row >= 0) && (row < height) && (col >= 0) && (col < width);
}

// Algo de dijkstra
void dijkstra(Element** grid,int height, int width, Node src, Node dest) {
    int** dist = NULL;
    //Allocate the necessary memory to it
    dist = ( int **) malloc(height * sizeof( int*));
    if(dist == NULL) {
        return;
    }
    for(int ligne = 0;ligne < height;ligne++) {
        int* line = NULL;
        line = (int*) malloc(width * sizeof(int));
        if(line == NULL) {
            free(dist);
            return;
        }
        *(dist + ligne) = line;
    }
    
    // Tableau noeud vu

    int** vu = NULL;
    //Allocate the necessary memory to it
    vu = ( int **) malloc(height * sizeof( int*));
    if(vu == NULL) {
        return;
    }
    for(int ligne = 0;ligne < height;ligne++) {
        int* line = NULL;
        line = (int*) malloc(width * sizeof(int));
        if(line == NULL) {
            free(vu);
            return;
        }
        *(vu + ligne) = line;
    }

    // Toute les distances a max et les vistes a 0
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dist[i][j] = INT_MAX;
            vu[i][j] = 0;
        }
    }

    // dist de src a src =0
    dist[src.row][src.col] = 0;

    for (int count = 0; count < height * width - 1; count++){
        int minDist = INT_MAX;
        Node u;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (vu[i][j] == 0 && dist[i][j] < minDist) {
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
                    vu[u.row + i][u.col + j] == 0 &&
                    dist[u.row][u.col] != INT_MAX &&
                    dist[u.row][u.col] + 1 < dist[u.row + i][u.col + j]
                    ) {
                        Element *adjacentCell = &grid[u.row + i][u.col + j];
                        if (adjacentCell->degree > 0){
                            dist[u.row + i][u.col + j] = dist[u.row][u.col] + 1;
                        }
                    
                }
            }
        }
    }    

    printf("La distance minimale depuis (%d, %d) à (%d, %d) est : %d\n",src.row, src.col, dest.row, dest.col, dist[dest.row][dest.col]);
}

int debug_dijkstra() {
    int height,width;
    Element** grid = loadGridFromFile("test44", &height, &width);

    // noeud source et noeud destination
    int srcH,srcW,destH,destW =0;
    scanf("%d %d",&srcH,&srcW);
    scanf("%d %d",&destH,&destW);
    Node src = creeNode(srcH, srcW);
    Node dest = creeNode(destH, destW);
    displayMatrix(grid, width, height);

    dijkstra(grid,height, width, src, dest);

    return 0;
}