#ifndef __AABB_H__
#define __AABB_H__

#include "geometry/geometry.h"
/**
 * define the Axis-aligned-bounding-box
*/
struct AABB
{
    AABB() {
        min = vec3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
        max = vec3f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    }
    ~AABB() {}
    vec3f min;
    vec3f max;
};

#endif