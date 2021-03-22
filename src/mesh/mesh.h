#ifndef __MESH_H__
#define __MESH_H__

#include <optional>

#include "geometry/geometry.h"
#include "geometry/ray.h"


/**
 * A mesh class with different geometry will intersecte with ray
*/
class Mesh {
public:
     /**
     * a ray intersect with the meth
     * @param ray the ray contains original point and directory 
     * @return if they are intersected return the result has value, otherwise return nullopt.
    */
    virtual std::optional<IntersectResult> rayIntersect(const Ray& ray) const = 0;
};

#endif