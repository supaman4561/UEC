#ifndef __DRAW_H_
#define __DRAW_H_

void draw_circle(GLdouble x, GLdouble y, GLdouble r, int p, color_t c);

void draw_ellipse(GLdouble x, GLdouble y, GLdouble a, GLdouble b, int p, color_t c);

void draw_lines(GLdouble points[][2], int size, GLfloat width, color_t c);

void draw_polygon3d(GLdouble points[][3], int size, color_t c);

#endif