#ifndef __AABB_H__
#define __AABB_H__

#include "geometry/geometry.h"
#include "geometry/ray.h"

/**
 * define the Axis-aligned-bounding-box
*/
struct AABB
{
    enum class AXIS {
        X = 1,
        Y = 2,
        Z = 3,
    };

    AABB() {
        min = vec3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
        max = vec3f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    }
    ~AABB() {}
    vec3f min;
    vec3f max;

    AABB upon(const AABB& other) const {
        AABB res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], other.min[i]);
            res.max[i] = std::max(max[i], other.max[i]);
        }
        return res;
    }

    AABB upon(const vec3f v) const {
        AABB res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], v[i]);
            res.max[i] = std::max(max[i], v[i]);
        }
        return res;
    }

    vec3f getCentre() const {
        return (min + max) / 2.0f;
    }

    /**
     * get who axis extend is larger.
    */
    AXIS getExtent() const {
        vec3f d = max - min;
        if(d.x > d.y && d.x > d.z) {
            return AXIS::X;
        } else if(d.y > d.z) {
            return AXIS::Y;
        } else {
            return AXIS::Z;
        }
    }

    bool intersect(const Ray& ray) const {
        float t_min_x = (min.x - ray.o.x) / ray.d.x;
        float t_min_y = (min.y - ray.o.y) / ray.d.y;
        float t_min_z = (min.z - ray.o.z) / ray.d.z;

        float t_max_x = (max.x - ray.o.x) / ray.d.x;
        float t_max_y = (max.y - ray.o.y) / ray.d.y;
        float t_max_z = (max.z - ray.o.z) / ray.d.z;

        if(ray.d.x < 0) {
            std::swap(t_max_x, t_min_x);
        }
        if(ray.d.y < 0) {
            std::swap(t_max_y, t_min_y);
        }
        if(ray.d.z < 0) {
            std::swap(t_max_z, t_min_z);
        }

        float t_enter = std::max(t_min_x, std::max(t_min_y, t_min_z));
        float t_exit = std::min(t_max_x, std::min(t_max_y, t_max_z));
        return t_exit > t_enter && t_exit >= 0;
    }

};

#endif