#ifndef FOREST_H
#define FOREST_H

/*
** This structure makes it possible to specify the characterization of the elements of the forest
** type : anagram of the letter
** symbol : symbol of the element 
** degree : degree of the element, which is the health of the element
** state : state of the element if it is on fire (1) or not (0)
*/

typedef struct {
    char type;
    char symbol;
    unsigned short degree;
    unsigned short state;
} Element;

/*
** Point is use to store coordinates because we need to know where the fire is
*/

typedef struct Point {
    int x;
    int y;
} Point;

extern Element ground, tree, leaf, rock, water, herb, ash, extinctAsh;

// Creation of an enum for faster access to random generation
typedef enum {
    GROUND,
    TREE,
    LEAF,
    ROCK,
    WATER,
    HERB,
    ASH,
    EXTINCTASH
} ElementType;

Element detectionElement(char symbol);
Element getElementFromEnum(int elementEnum);

#endif 
