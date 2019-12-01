#include <GL/glut.h>
#include "vector.h"

vec3d_t scalar_multiple(GLdouble s, vec3d_t vec) 
{
    int i;

    for(i=0; i<3; i++) {
        vec[i] *= s;
    }

    return vec;
}

GLdouble inner_product_3dv(vec3d_t a, vec3d_t b)
{
    GLdouble result=0;
    int i;

    for(i=0; i<3; i++) {
        result += a[i]*b[i];
    }

    return result;
}
