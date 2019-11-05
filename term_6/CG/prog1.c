#include <stdio.h>
#include <GL/glut.h>

#include "shape.h"

#define MAXPOINTS 100      /* 記憶する点の数　　 */
GLint point[MAXPOINTS][2]; /* 座標を記憶する配列 */
int pointnum = 0;          /* 記憶した座標の数　 */
int rubberband = 0;

void display(void)
{
  int i;
  
  glClear(GL_COLOR_BUFFER_BIT);

  color_t red = {1.0, 0.0, 0.0};
  color_t green = {0.0, 1.0, 0.0};
  draw_circle(50, 50, 20, 20, red);
  draw_ellipse(50, 50, 10, 40, 20, green);
  
  glFlush();

}

void resize(int w, int h) {
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();

  /* スクリーン上の座標系をマウスの座標系に一致させる */
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{ 
  switch (button) {
  case GLUT_LEFT_BUTTON:
    /* ボタンを操作した位置を記録する */
    point[pointnum][0] = x;
    point[pointnum][1] = y;
    if (state == GLUT_UP) {
      /* ボタンを押した位置から離した位置まで線を引く */
      glColor3d(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2iv(point[pointnum - 1]);
      glVertex2iv(point[pointnum]);
      glEnd();
      glFlush();

      rubberband=0;
    }
    else {
    }
    if (pointnum < MAXPOINTS-1) ++pointnum;
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  default:
    break;
  }

}

void motion(int x, int y) {
  static GLint savepoint[2];

  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);
  if (rubberband) {
    /* 以前のラバーバンドを消す */
    glVertex2iv(point[pointnum - 1]);
    glVertex2iv(savepoint);
  }
  /* 新しいラバーバンドを描く */
  glVertex2iv(point[pointnum - 1]);
  glVertex2i(x, y);
  glEnd();

  glFlush();

  /* 論理演算機能 OFF */
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  /* 今描いたラバーバンドの端点を保存 */
  savepoint[0] = x;
  savepoint[1] = y;
 
  /* 今描いたラバーバンドは次のタイミングで消す */
  rubberband = 1;
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 240);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  init();
  glutMainLoop();
  return 0;
}
