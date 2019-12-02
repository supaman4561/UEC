#ifndef __SHAPE_H_
#define __SHAPE_H_

#include "vector.h"

typedef struct plane {
    vec3d_t pos;
    vec3d_t norm_direct[2];
    vec3d_t normal;
    vec2d_t length;
}plane_t;

typedef struct obb {
    vec3d_t pos;            // 位置
    vec3d_t norm_direct[3]; // 標準化方向ベクトル
    vec3d_t length;         // それぞれの長さ
}obb_t;

obb_t *init_obb(vec3d_t pos, vec3d_t norm[3], vec3d_t length);

cell_t *read_collision_data(const char *filename);

GLdouble projected_length_of_plane(plane_t plane, vec3d_t norm);

GLdouble projected_length_of_obb(obb_t obb, vec3d_t norm);

bool col_obb_plane(obb_t obb, plane_t plane, GLdouble *len);


#endif /* __SHAPE_H_ */