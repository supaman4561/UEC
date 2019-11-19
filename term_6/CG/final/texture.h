#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#define TEXHEIGHT 256
#define TEXWIDTH 256
#define RGBA 4

void readTexture(const char *filename, GLubyte out[TEXHEIGHT][TEXWIDTH][RGBA]);

#endif