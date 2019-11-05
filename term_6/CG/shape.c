#include <GL/glut.h>
#include <math.h>
#include "shape.h"

/**
 * x : 中心のx座標
 * y : 中心のy座標
 * p : 辺の数(なめらかさ)
 * c : 色
 */
void draw_circle(GLdouble x, GLdouble y, GLdouble r, int p, color_t c) {
  int i;
  glColor3d(c.r, c.b, c.g);
  glBegin(GL_POLYGON);
  for (i=0; i<p; i++) {
    glVertex2d(x + r*cos(2 * M_PI / p * i),
	       y + r*sin(2 * M_PI / p * i));
  }
  glEnd();
}

void draw_ellipse(GLdouble x, GLdouble y, GLdouble a, GLdouble b, int p, color_t c) {
  int i;
  glColor3d(c.r, c.b, c.g);
  glBegin(GL_POLYGON);
  for (i=0; i<p; i++) {
    glVertex2d(x + a*cos(2 * M_PI / p * i),
	       y + b*sin(2 * M_PI / p * i));
  }
  glEnd();
}
