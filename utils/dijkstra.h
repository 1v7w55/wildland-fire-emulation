#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../core/forest.h"
#include <stddef.h>

typedef struct {
    int row, col;
}Node;

Node creeNode(int row, int col);
int isValid(int row, int col, int height,int width);
int dijkstra(Element** grid,int height, int width, Node src, Node dest,char mode) ;
void menu_dijkstra(Element** grid,int height, int width) ;
void menu_burn_predict(Element** grid,int height, int width);
int burn_predict(Element** grid,int height, int width, int srcH,int srcW );
void display_way(Element** matrix, size_t width, size_t height, Node* pre, Node dest);
void menu_fire_predict(Element** grid,int height, int width);
#endif
