#ifndef __SHAPE_H_
#define __SHAPE_H_

typedef struct color {
  GLdouble r;
  GLdouble b;
  GLdouble g;
} color_t;

void draw_circle(GLdouble x, GLdouble y, GLdouble r, int p, color_t c);

void draw_ellipse(GLdouble x, GLdouble y, GLdouble a, GLdouble b, int p, color_t c);

void draw_lines(GLdouble points[][2], int size, GLfloat width, color_t c);

#endif
