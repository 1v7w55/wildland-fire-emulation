#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../core/forest.h"

typedef struct {
    int row, col;
}Node;

Node creeNode(int row, int col);
int isValid(int row, int col, int height,int width);
void dijkstra(Element** grid,int height, int width, Node src, Node dest) ;
int debug_dijkstra() ;

#endif
