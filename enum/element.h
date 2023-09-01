#include "../bean/typeElement.h"

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
} ElementEnum;

// Element return based on the element in the enum
Element getElementFromEnum(ElementEnum elementEnum) {
  switch (elementEnum) {
    case GROUND:
      return ground;
    case TREE:
      return tree;
    case LEAF:
      return leaf;
    case ROCK:
      return rock;
    case WATER:
      return water;
    case HERB:
      return herb;
    case ASH:
      return ash;
    case EXTINCTASH:
      return extinctAsh;
    default:
      return ground;
  }
}