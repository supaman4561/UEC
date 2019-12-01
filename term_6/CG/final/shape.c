#include <stdio.h> /* debug */
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <math.h>
#include "vector.h"
#include "shape.h"

obb_t *init_obb(vec3d_t pos, vec3d_t norm[3], vec3d_t length)
{
    obb_t *new;
    int i;

    new = (obb_t *)malloc(sizeof(obb_t));
    if (new != NULL) {
        cpy_3dv(new->pos, pos);
        for (i=0; i<3; i++) {
            cpy_3dv(new->norm_direct[i], norm[i]);
        }
        cpy_3dv(new->length, length);
    }

    return new;
}

/* ベクトルnormに投影した時のplaneの長さ */
GLdouble projected_length_of_plane(plane_t plane, vec3d_t norm)
{
    GLdouble result=0;
    vec3d_t target;
    int i;

    for (i=0; i<2; i++) {
        multiply_scalar(target, plane.length[i], plane.norm_direct[i]);    
        result += fabs(inner_product_3dv(target, norm));
    }

    return result;
}

/* ベクトルnormに投影した時のobbの長さ */
GLdouble projected_length_of_obb(obb_t obb, vec3d_t norm)
{
    GLdouble result=0;
    vec3d_t target;
    int i;

    for (i=0; i<3; i++) {
        multiply_scalar(target, obb.length[i], obb.norm_direct[i]);    
        result += fabs(inner_product_3dv(target, norm));
    }

    return result;
}

/* OBBと平面の衝突判定 */
bool col_obb_plane(obb_t obb, plane_t plane, GLdouble *len) 
{
    vec3d_t sep; /* 分離軸 */
    vec3d_t tmp; 
    GLdouble ra, rb, dist; /* 投影時長さ, 二点間距離 */
    int i;

    /* planeによる分離軸 */
    for (i=0; i<2; i++) {
        cpy_3dv(sep, plane.norm_direct[i]);
        ra = plane.length[i];
        rb = projected_length_of_obb(obb, sep);
        sub_3dv(tmp, obb.pos, plane.pos);
        dist = fabs(inner_product_3dv(tmp, sep));
        if (dist > (ra + rb)) {
            return false;
        }
    }

    /* planeの法線ベクトルによる分離 */
    cross_product_3dv(sep, plane.norm_direct[0], plane.norm_direct[1]);
    rb = projected_length_of_obb(obb, sep);
    sub_3dv(tmp, obb.pos, plane.pos);
    dist = fabs(inner_product_3dv(tmp, sep));

    /* 戻す距離を計算 */
    if (len != NULL) {
        if (dist > 0) {
            *len = rb - fabs(dist);
        } else {
            *len = rb + fabs(dist);
        }
    }

    if (dist > rb) {
        return false;
    }

    return true;
}