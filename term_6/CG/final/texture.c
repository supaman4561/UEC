#include <stdio.h>
#include <GL/glut.h>
#include "texture.h"

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