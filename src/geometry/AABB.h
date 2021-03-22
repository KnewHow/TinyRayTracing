#ifndef __AABB_H__
#define __AABB_H__

#include "geometry.h"
/**
 * define the Axis-aligned-bounding-box
*/
struct AABB
{
    AABB() {}
    ~AABB() {}
    vec3f min;
    vec3f max;
};

#endif