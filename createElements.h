struct Element {
  char type;
  char symbol;
  unsigned short degree;
  // State will be equals to 1 if it's on fire, 0 otherwise
  unsigned short state;
  // Initialize all types that may be on our array
} ground, tree, leaf, rock, water, herb, ash, extinctAsh;

void createGroundElement() {
  ground.type = 'F';
  ground.symbol = '+';
  ground.degree = 0;
  ground.state = 0;
}

void createTreeElement() {
  tree.type = 'T';
  tree.symbol = '*';
  tree.degree = 4;
  tree.state = 0;
}

void createLeafElement() {
  leaf.type = 'L';
  leaf.symbol = ' ';
  leaf.degree = 2;
  leaf.state = 0;
}

void createRockElement() {
  rock.type = 'R';
  rock.symbol = '#';
  rock.degree = 5;
  rock.state = 0;
}

void createHerbElement() {
  herb.type = 'H';
  herb.symbol = 'x';
  herb.degree = 3;
  herb.state = 0;
}

void createWaterElement() {
  water.type = 'W';
  water.symbol = '/';
  water.degree = 0;
  water.state = 0;
}

void createAshElement() {
  ash.type = 'A';
  ash.symbol = '-';
  ash.degree = 1;
  ash.state = 0;
}

void createExtinctAshElement() {
  extinctAsh.type = 'E';
  extinctAsh.symbol = '@';
  extinctAsh.degree = 0;
  extinctAsh.state = 0;
}
