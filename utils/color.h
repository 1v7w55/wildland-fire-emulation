#ifndef COLOR_H
#define COLOR_H

#include "../core/forest.h"

// Define color
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

void getColor(Element element);
void resetColor();

#endif
