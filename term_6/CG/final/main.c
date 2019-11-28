#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include "shape.h"
#include "keyboard.h"
#include "texture.h"
#include "vector.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 720
#define MOUSE_SPEED 0.001
#define WALK_SPEED 0.5
#define TRUE 1
#define FALSE 0 

/* 地面 */
GLdouble ground[][3] = {
  {0, 0, 0},
  {50, 0, 0},
  {50, 0, 50},
  {0, 0, 50}
};

GLdouble g_coord[][2] = {
  {0, 10.0},
  {10.0, 10.0},
  {10.0, 0},
  {0, 0}
};

/* カメラ設定 */
vec2d_t angle = {0, 0};
vec3d_t pos = {25.0, 2.0, 25.0};       // 位置
vec3d_t look = {0.0, 2.0, 0.0};  // 向き
vec3d_t up = {0.0, 1.0, 0.0};    // 上

/* 色 */
const color_t BLACK = {0.0, 0.0, 0.0};

/* テクスチャ */
GLubyte ground_tex[TEXHEIGHT][TEXWIDTH][RGBA];
GLubyte blick_tex[TEXHEIGHT][TEXWIDTH][RGBA];

void show_params() {
  printf("pos: %.3lf, %.3lf, %.3lf\n", pos.x, pos.y, pos.z);
  printf("look: %.3lf, %.3lf, %.3lf\n", look.x, look.y, look.z);
}

void init(void)
{

  /* テクスチャ読み込み */
  readTexture("./images/tile256.raw", ground_tex);
  readTexture("./images/blick256x256.raw", blick_tex);

  /* ワード単位 */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  /* テクスチャを拡大・縮小する方法の指定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glClearColor(1.0, 1.0, 1.0, 1.0);

  /* マウスカーソル非表示 */
  glutSetCursor(GLUT_CURSOR_NONE);
}

/*
** シーンの描画
*/
static void scene(void)
{
  static const GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };  /* 材質 (色) */
  
  /* 材質の設定 */
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  
  /* アルファテスト開始 */
  glEnable(GL_ALPHA_TEST);

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);
  
  /* 床  */
  glNormal3d(0.0, 1.0, 0.0); // 法線ベクトル
  applyTexture(ground, g_coord, ground_tex);
  
  /* テクスチャマッピング終了 */
  glDisable(GL_TEXTURE_2D);

  /* アルファテスト終了 */
  glDisable(GL_ALPHA_TEST);
}

void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(pos.x, pos.y, pos.z,
	    pos.x + look.x, pos.y + look.y, pos.z + look.z,
	    up.x, up.y, up.z);

  scene();

  glutSwapBuffers();

}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  
  glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {

  if (isPush('w')) {
    pos.x += WALK_SPEED * sin(angle.x);
    pos.z += WALK_SPEED * cos(angle.x);
  }
  if (isPush('s')) {
    pos.x -= WALK_SPEED * sin(angle.x);
    pos.z -= WALK_SPEED * cos(angle.x);
  }
  if (isPush('a')) {
    pos.x += WALK_SPEED * cos(angle.x);
    pos.z -= WALK_SPEED * sin(angle.x);
  }
  if (isPush('d')) {
    pos.x -= WALK_SPEED * cos(angle.x);
    pos.z += WALK_SPEED * sin(angle.x);
  }
  glutPostRedisplay();
  glutTimerFunc(17, timer, 0);
}

void moveViewpoint(int x, int y) {
  static bool wrap = false;
  
  if (!wrap) {
    int ww = glutGet(GLUT_WINDOW_WIDTH); 
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int dx = x - ww / 2;
    int dy = y - wh / 2;
    angle.x -= dx * MOUSE_SPEED;
    angle.y -= dy * MOUSE_SPEED;

    /* 正規化 */
    if (angle.x < -M_PI) {
      angle.x += 2 * M_PI;
    } else if (angle.x > M_PI) {
      angle.x -= 2 * M_PI;
    }

    if (angle.y < -M_PI / 2) {
      angle.y = -M_PI / 2;
    }
    if (angle.y > M_PI / 2) {
      angle.y = M_PI / 2;
    }

    look.x = sin(angle.x) * cos(angle.y);
    look.y = sin(angle.y);
    look.z = cos(angle.x) * cos(angle.y);
    wrap = true;
    glutWarpPointer(ww / 2, wh / 2);
  } else {
    wrap = false;
  }

}

int main(int argc, char *argv[]) 
{
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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
