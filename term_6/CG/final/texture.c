#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "list.h"
#include "vector.h"
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

cell_t *readTextureData(const char *filename) 
{
  const int MAX_STRLEN = 256;
  FILE *fp;
  cell_t *list = NULL;
  texture_t *tp;
  char *data;
  char line[MAX_STRLEN];
  int i, j;

  if ((fp = fopen(filename, "r")) != NULL) {
    while (fgets(line, MAX_STRLEN, fp) != NULL) {
      tp = (texture_t *)malloc(sizeof(texture_t));

      // テクスチャ画像
      data = strtok(line, ",");
      readTexture(data, tp->texture);
      printf("%s\n", data);

      // 角
      data = strtok(NULL, ",");
      tp->corner = atoi(data);
      printf("%d\n", tp->corner);

      // テクスチャマッピング先オブジェクト
      for (i=0;  i<(tp->corner); i++) {
        for (j=0; j<3; j++) {
          data = strtok(NULL, ",");
          tp->base[i][j] = atof(data);
          printf("%lf ", tp->base[i][j]);
        }
        printf("\n");
      }

      // テクスチャ座標
      for (i=0; i<(tp->corner); i++) {
        for (j=0; j<2; j++) {
          data = strtok(NULL, ",");
          tp->coord[i][j] = atof(data);
          printf("%lf ", tp->coord[i][j]);
        }
        printf("\n");
      }

      // 法線ベクトル
      for (i=0; i<3; i++) {
        data = strtok(NULL, ",");
        tp->up[i] = atof(data);
        printf("%lf ", tp->up[i]);
      }
      printf("\n");

      list = append_cell(list, TYPE_TEXTURE, tp);
    }
  } else {
    return NULL;
  }

  return list;
}

void applyTexture(int corner, vec3d_t base[corner], vec2d_t coord[corner], GLubyte texture[TEXHEIGHT][TEXWIDTH][RGBA]) 
{
  int i;
  /* テクスチャ割り当て */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXWIDTH, TEXHEIGHT, 0, 
	       GL_RGBA, GL_UNSIGNED_BYTE, texture);
  
  glBegin(GL_QUADS);
  for (i=0; i<corner; i++) {
    glTexCoord2dv(coord[i]);
    glVertex3dv(base[i]);
  }
  glEnd();
  
}
