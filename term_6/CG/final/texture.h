#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#define TEXHEIGHT 256
#define TEXWIDTH 256
#define RGBA 4

void readTexture(const char *filename, GLubyte out[TEXHEIGHT][TEXWIDTH][RGBA]);

void applyTexture(GLdouble base[][3], GLdouble coord[][2], GLubyte texture[TEXHEIGHT][TEXWIDTH][RGBA]);

#endif
