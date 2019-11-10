#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
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

/**
 * x : 中心のx座標
 * y : 中心のy座標
 * a : xの最大値
 * b : yの最大値
 * p : 辺の数(なめらかさ)
 * c : 色
 */
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

/**
 * points : 点集合
 * size : pointsの含む点の数
 * width : 線の太さ
 * c : 色
 */
void draw_lines(GLdouble points[][2], int size, GLfloat width, color_t c) {
  int i;
  glColor3d(c.r, c.b, c.g);
  glLineWidth(width);
  glBegin(GL_LINE_LOOP);
  for (i=0; i<size; i++) {
    glVertex2d(points[i][0], points[i][1]);
  }
  glEnd();
}
