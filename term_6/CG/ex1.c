#include <stdio.h>
#include <GL/glut.h>

#include "shape.h"

const color_t BLACK = {0.0, 0.0, 0.0};
const color_t WHITE = {1.0, 1.0, 1.0};
const color_t ORANGE = {1.0, 0.5, 0.0};

double BODY[][2] = {
  {210.0, 100.0},
  {300.0, 100.0}, 
  {290.0, 200.0},
  {370.0, 180.0},
  {390.0, 270.0},
  {360.0, 290.0},
  {340.0, 250.0},
  {300.0, 260.0},
  {340.0, 410.0},
  {330.0, 370.0},
  {390.0, 330.0},
  {410.0, 360.0},
  {340.0, 410.0},
  {300.0, 410.0}, 
  {270.0, 370.0},
  {180.0, 350.0}, 
  {150.0, 275.0},
  {190.0, 375.0},
  {160.0, 390.0},
  {100.0, 300.0},
  {150.0, 275.0},
  {200.0, 290.0},
  {190.0, 230.0},
  {110.0, 200.0},
  {120.0, 120.0}, 
  {150.0, 130.0},
  {150.0, 180.0},
  {200.0, 180.0}
};
  
void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);

  draw_lines(BODY, sizeof(BODY) / sizeof(BODY[0]), 2.0, BLACK);
  draw_ellipse(250, 250, 30, 50, 20, ORANGE);
  draw_ellipse(250, 250, 22.5, 37.5, 20, WHITE);
  draw_ellipse(250, 250, 15, 25, 20, ORANGE);
  draw_ellipse(250, 250, 7.5, 12.5, 20, WHITE);


  glFlush();

}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glLoadIdentity();
  glOrtho(0, (GLdouble)w, (GLdouble)h, 0, -1.0, 1.0);
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
  glutInitWindowSize(500, 500);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
