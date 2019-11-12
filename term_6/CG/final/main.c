#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include "shape.h"
#include "keyboard.h"

#define TRUE 1
#define FALSE 0

typedef struct vec3d {
  GLdouble x;
  GLdouble y;
  GLdouble z;
} vec3d_t;

vec3d_t pos = {0, 1.6, 0};
vec3d_t look = {0.0, 1.6, 1.0};
vec3d_t up = {0.0, 1.0, 0.0};

GLdouble ground[][3] = {
  {0, 0, 0},
  {50, 0, 0},
  {50, 0, 50},
  {0, 0, 50}
};

const color_t BLACK = {0.0, 0.0, 0.0};

void show_params() {
  printf("pos: %.3lf, %.3lf, %.3lf\n", pos.x, pos.y, pos.z);
  printf("look: %.3lf, %.3lf, %.3lf\n", look.x, look.y, look.z);
}

void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(pos.x, pos.y, pos.z,
	    look.x, look.y, look.z,
	    up.x, up.y, up.z);
  draw_polygon3d(ground, sizeof(ground) / sizeof(ground[0]), BLACK);

  glutSwapBuffers();

}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  
  glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void timer(int value) {
  GLdouble diff_x = look.x - pos.x;
  GLdouble diff_z = look.z - pos.z;
  
  if (isPush('w')) {
    pos.x += diff_x;
    pos.z += diff_z;
    look.x += diff_x;
    look.z += diff_z;
  }
  if (isPush('s')) {
    pos.x -= diff_x;
    pos.z -= diff_z;
    look.x -= diff_x;
    look.z -= diff_z;
  }
  if (isPush('a')) {
    pos.x += diff_z;
    pos.z -= diff_x;
    look.x += diff_z;
    look.z -= diff_x;
  }
  if (isPush('d')) {
    pos.x -= diff_z;
    pos.z += diff_x;
    look.x -= diff_z;
    look.z += diff_x;
  }
  glutPostRedisplay();
  glutTimerFunc(17, timer, 0);
}

void moveViewpoint(int x, int y) {
  int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
  int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
  GLdouble theta = M_PI / cx;
  GLdouble phi = M_PI / 2 / cy;

  look.x = pos.x + sin((x - cx) * theta);
  look.z = pos.z + cos((x - cx) * theta);
  look.y = pos.y + sin((y - cy) * phi);
}

int main(int argc, char *argv[])
{
  glutInitWindowSize(500, 500);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboardDown);
  glutKeyboardUpFunc(keyboardUp);
  glutPassiveMotionFunc(moveViewpoint);
  glutTimerFunc(100, timer, 0);
  init();
  glutMainLoop();
  return 0;
}
