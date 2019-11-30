#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include "vector.h"
#include "list.h"

#define TEXHEIGHT 256
#define TEXWIDTH 256
#define RGBA 4

typedef struct tag {
    GLubyte texture[TEXHEIGHT][TEXWIDTH][RGBA];
    int corner;
    vec3d_t base[4];
    vec2d_t coord[4];
    vec3d_t up;
}texture_t;

void readTexture(const char *filename, GLubyte out[TEXHEIGHT][TEXWIDTH][RGBA]);

cell_t *readTextureData(const char *filename);

void applyTexture(int corner, vec3d_t base[corner], vec2d_t coord[corner], GLubyte texture[TEXHEIGHT][TEXWIDTH][RGBA]);

#endif
