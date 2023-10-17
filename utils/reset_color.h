void getColor(Element element) {
  if (element.state == 0 && element.degree > 0) {
    printf("%s", COLOR_GREEN);
    return;
  } else  if(element.state == 1) {
    printf("%s", COLOR_RED);
    return;
  }
}

void resetColor() {
  printf("%s", COLOR_RESET);
};