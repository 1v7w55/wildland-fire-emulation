Element detectionElement(char symbol){
    switch ((char) symbol) {
    case '+':
        return ground;
    case '*':
        return tree;
    case ' ':
        return leaf;
    case '#':
        return rock;
    case 'x':
        return herb;
    case '/':
        return water;
    case '-':
        return ash;
    case '@':
        return extinctAsh; 
    default:
        printf("Le caractère %c est interdis.",symbol);
        //In case the user inputs a char not possible
        Element error = { '!', '!', 0, 0 };
        return error;
    }
}