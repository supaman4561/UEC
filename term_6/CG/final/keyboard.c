#include <stdbool.h>
#include "keyboard.h"

bool keys[128] = {false};

bool isPush(unsigned char key) {
  return keys[key];
}

void keyboardDown(unsigned char key, int x, int y) {
  keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
  keys[key] = false;
}
