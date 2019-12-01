#include <GL/glut.h>
#include "vector.h"

GLdouble inner_product_3dv(vec3d_t a, vec3d_t b)
{
    GLdouble result=0;
    int i;

    for (i=0; i<3; i++) {
        result += a[i]*b[i];
    }

    return result;
}

void cross_product_3dv(vec3d_t ans, vec3d_t a, vec3d_t b)
{
    ans[0] = a[1]*b[2] - a[2]*b[1];
    ans[1] = a[2]*b[0] - a[0]*b[2];
    ans[2] = a[0]*b[1] - a[1]*b[0];
}


void multiply_scalar(vec3d_t ans, GLdouble s, vec3d_t vec)
{
    int i;

    for (i=0; i<3; i++) {
        ans[i] = vec[i] * s;
    }
}

void cpy_3dv(vec3d_t dist, vec3d_t src)
{
    int i;

    for (i=0; i<3; i++) {
        dist[i] = src[i];
    }
}

void add_3dv(vec3d_t ans, vec3d_t a, vec3d_t b)
{
    int i;

    for (i=0; i<3; i++) {
        ans[i] = a[i] + b[i];
    }
}

void sub_3dv(vec3d_t ans, vec3d_t a, vec3d_t b)
{
    int i;

    for (i=0; i<3; i++) {
        ans[i] = a[i] - b[i];
    }
}