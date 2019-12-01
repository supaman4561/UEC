#ifndef __VECTOR_H_
#define __VECTOR_H_

typedef GLdouble vec3d_t[3];
typedef GLdouble vec2d_t[2];

GLdouble inner_product_3dv(vec3d_t a, vec3d_t b);

void cross_product_3dv(vec3d_t ans, vec3d_t a, vec3d_t b);

void multiply_scalar(vec3d_t ans, GLdouble s, vec3d_t vec);

void cpy_3dv(vec3d_t dist, vec3d_t src);

void add_3dv(vec3d_t ans, vec3d_t a, vec3d_t b);

void sub_3dv(vec3d_t ans, vec3d_t a, vec3d_t b);

#endif