// Define min & max width for the game bord
const size_t MAX_WIDTH = 10;
const size_t MIN_WIDTH = 4;
const size_t MAX_HEIGHT = 10;
const size_t MIN_HEIGHT = 4;

// Define grid size
size_t gridWidth, gridHeight;

// Define var for the coordinates of the fire
size_t pointIndex, fireSpreadStep;
unsigned short randomX, randomY;

// Define spacer
const char SPACER[] = "\t";

// Define color
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"