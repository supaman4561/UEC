#include <stdio.h>
#include <GL/glut.h>
#include "texture.h"
#include "vector.h"

void readTexture(const char *filename, GLubyte out[TEXHEIGHT][TEXWIDTH][RGBA])
{
    FILE *fp;
    size_t size = TEXHEIGHT * TEXWIDTH * RGBA;

    if ((fp = fopen(filename, "rb")) != NULL) {
        fread(out, size, 1, fp);
        fclose(fp);
    } else {
        perror(filename);
    }
}

void applyTexture(GLdouble base[][3], GLdouble coord[][2], GLubyte texture[TEXHEIGHT][TEXWIDTH][RGBA]) 
{
  int i;
  /* テクスチャ割り当て */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXWIDTH, TEXHEIGHT, 0, 
	       GL_RGBA, GL_UNSIGNED_BYTE, texture);
  
  glBegin(GL_QUADS);
  for (i=0; i<4; i++) {
    glTexCoord2dv(coord[i]);
    glVertex3dv(base[i]);
  }
  glEnd();
  
}
