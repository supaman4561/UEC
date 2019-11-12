#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

bool isPush(unsigned char key);

void keyboardDown(unsigned char key, int x, int y);

void keyboardUp(unsigned char key, int x, int y);

#endif
