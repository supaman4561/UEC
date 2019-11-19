#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include "shape.h"
#include "keyboard.h"
#include "texture.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define TRUE 1
#define FALSE 0

typedef struct vec3d {
  GLdouble x;
  GLdouble y;
  GLdouble z;
} vec3d_t;

/* 地面 */
GLdouble ground[][3] = {
  {0, 0, 0},
  {50, 0, 0},
  {50, 0, 50},
  {0, 0, 50}
};

/* カメラ設定 */
vec3d_t pos = {0, 2.0, 0};       // 位置
vec3d_t look = {0.0, 2.0, 1.0};  // 向き
vec3d_t up = {0.0, 1.0, 0.0};    // 上

/* 色 */
const color_t BLACK = {0.0, 0.0, 0.0};

void show_params() {
  printf("pos: %.3lf, %.3lf, %.3lf\n", pos.x, pos.y, pos.z);
  printf("look: %.3lf, %.3lf, %.3lf\n", look.x, look.y, look.z);
}

void init(void)
{
  GLubyte ground_tex[TEXHEIGHT][TEXWIDTH][RGBA];

  /* テクスチャ読み込み */
  // readTexture("./images/ground.raw", ground_tex);
  readTexture("./images/tile256.raw", ground_tex);


  /* ワード単位 */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  /* テクスチャ割り当て */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXWIDTH, TEXHEIGHT, 0, 
    GL_RGBA, GL_UNSIGNED_BYTE, ground_tex);

  /* テクスチャを拡大・縮小する方法の指定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glClearColor(1.0, 1.0, 1.0, 1.0);
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
  
  /* １枚の４角形を描く */
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 10.0);
  glVertex3dv(ground[0]);
  glTexCoord2d(10.0, 10.0);
  glVertex3dv(ground[1]);
  glTexCoord2d(10.0, 0.0);
  glVertex3dv(ground[2]);
  glTexCoord2d(0.0, 0.0);
  glVertex3dv(ground[3]);
  glEnd();
  
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
	    look.x, look.y, look.z,
	    up.x, up.y, up.z);
  //draw_polygon3d(ground, sizeof(ground) / sizeof(ground[0]), BLACK);

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
  GLdouble v = 0.5;

  look.x = pos.x + v * sin((x - cx) * theta);
  look.z = pos.z + v * cos((x - cx) * theta);
  look.y = pos.y + v * sin((y - cy) * phi);
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
