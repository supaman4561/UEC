#ifndef __VECTOR_H_
#define __VECTOR_H_

typedef GLdouble vec3d_t[3];
typedef GLdouble vec2d_t[2];

vec3d_t scalar_multiple(GLdouble s, vec3d_t vec);

GLdouble inner_product_3dv(vec3d_t a, vec3d_t b);

#endif