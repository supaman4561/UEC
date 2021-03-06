#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "keyboard.h"
#include "texture.h"
#include "vector.h"
#include "shape.h"
#include "list.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 720
#define MOUSE_SPEED 0.001
#define WALK_SPEED 0.35
#define TRUE 1
#define FALSE 0 

/* カメラ設定 */
vec2d_t angle = {0, 0};
vec3d_t cam_pos = {2.5, 2.0, 2.5};       // 位置
vec3d_t look = {1.0, 0.0, 0.0};  // 向き
vec3d_t up = {0.0, 1.0, 0.0};    // 上

/* テクスチャ */
cell_t *texture_list;

/* 光源の位置 */
GLfloat light0pos[] = { 98, 10.0, 12.5, 1.0 };

/* プレイヤーのOBB */
vec3d_t default_pos = {2.5, 2.0, 2.5};
vec3d_t norm[3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1}
};
vec3d_t length = {0.5, 2.0, 0.5};
obb_t *player;

/* collision */
cell_t *collision_list;

void init(void)
{
  /* player obb 初期化 */
  player = init_obb(default_pos, norm, length);

  /* テクスチャ読み込み */
  texture_list = readTextureData("./dat/texture.dat");

  /* コリジョン読み込み */
  collision_list = read_collision_data("./dat/collision.dat");
  
  /* ワード単位 */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  /* テクスチャを拡大・縮小する方法の指定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  /* テクスチャの繰り返し方法の指定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* 初期色 */
  glClearColor(0.5, 0.6, 0.9, 1.0);

  /* 隠面処理有効 */
  glEnable(GL_DEPTH_TEST);

  /* マウスカーソル非表示 */
  glutSetCursor(GLUT_CURSOR_NONE);

  /* 光源有効 */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* アルファ値関数設定 */
  glAlphaFunc(GL_GREATER, 0.5);
}

/*
** シーンの描画
*/
static void scene(void)
{
  static const GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };  /* 材質 (色) */
  texture_t *tp;
  cell_t *cp;

  /* 材質の設定 */
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  
  /* アルファテスト開始 */
  glEnable(GL_ALPHA_TEST);

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);
  
  /* テクスチャ描画 */
  for (cp=texture_list; cp!=NULL; cp=cp->next) {
    if ((type_t)(cp->type) == TYPE_TEXTURE) {
      tp = (texture_t *)(cp->data);
      glNormal3dv(tp->up); // 法線ベクトル
      applyTexture(tp->corner, tp->base, tp->coord, tp->texture);
    }
  }

  /* テクスチャマッピング終了 */
  glDisable(GL_TEXTURE_2D);

  /* アルファテスト終了 */
  glDisable(GL_ALPHA_TEST);
}

void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  cpy_3dv(cam_pos, player->pos);
  gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2],
	    cam_pos[0] + look[0], cam_pos[1] + look[1], cam_pos[2] + look[2],
	    up[0], up[1], up[2]);

  /* 光源の位置設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

  scene();

  glutSwapBuffers();
}

void resize(int w, int h) 
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 0.1, 150.0);
  
  glMatrixMode(GL_MODELVIEW);
}

void movePosition() 
{
  if (isPush('w')) {
    player->pos[0] += WALK_SPEED * sin(angle[0]);
    player->pos[2] += WALK_SPEED * cos(angle[0]);
  }
  if (isPush('s')) {
    player->pos[0] -= WALK_SPEED * sin(angle[0]);
    player->pos[2] -= WALK_SPEED * cos(angle[0]);
  }
  if (isPush('a')) {
    player->pos[0] += WALK_SPEED * cos(angle[0]);
    player->pos[2] -= WALK_SPEED * sin(angle[0]);
  }
  if (isPush('d')) {
    player->pos[0] -= WALK_SPEED * cos(angle[0]);
    player->pos[2] += WALK_SPEED * sin(angle[0]);
  }
  if (isPush('e')) {
    cpy_3dv(player->pos, default_pos);
  }
  if (isPush('q')) {
    free_cell(texture_list);
    free_cell(collision_list);
    exit(0);
  }
}

void moveViewpoint(int x, int y) 
{
  static bool wrap = false;
  
  if (!wrap) {
    int ww = glutGet(GLUT_WINDOW_WIDTH); 
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int dx = x - ww / 2;
    int dy = y - wh / 2;
    angle[0] -= dx * MOUSE_SPEED;
    angle[1] -= dy * MOUSE_SPEED;

    /* 正規化 */
    if (angle[0] < -M_PI) {
      angle[0] += 2 * M_PI;
    } else if (angle[0] > M_PI) {
      angle[0] -= 2 * M_PI;
    }

    if (angle[1] < -M_PI / 2) {
      angle[1] = -M_PI / 2;
    }
    if (angle[1] > M_PI / 2) {
      angle[1] = M_PI / 2;
    }

    look[0] = sin(angle[0]) * cos(angle[1]);
    look[1] = sin(angle[1]);
    look[2] = cos(angle[0]) * cos(angle[1]);
    wrap = true;
    glutWarpPointer(ww / 2, wh / 2);
  } else {
    wrap = false;
  }

}

void timer(int value) 
{
  cell_t *cp;
  plane_t *pp;
  vec3d_t tmp;
  GLdouble len;

  movePosition();
  glutPostRedisplay();
  glutTimerFunc(17, timer, 0);  /* 60fps */

  /* 自由落下 */
  player->pos[1] -= WALK_SPEED;

  /* 衝突判定 */
  for (cp=collision_list; cp!=NULL; cp=cp->next) {
    if ((type_t)(cp->type) == TYPE_PLANE) {
      pp = (plane_t *)(cp->data);
      if (col_obb_plane(*player, *pp, &len)) {
        multiply_scalar(tmp, len, pp->normal);
        add_3dv(player->pos, player->pos, tmp);
      }
    }
  }
}

int main(int argc, char *argv[]) 
{
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
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
