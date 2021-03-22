#ifndef __MESH_H__
#define __MESH_H__

#include <optional>

#include "geometry.h"
#include "ray.h"


/**
 * A mesh class with different geometry will intersecte with ray
*/
class Mesh {
public:
     /**
     * a ray intersect with the meth
     * @param orig the ray original point 
     * @param d the directory of the ray
     * @return if they are intersected return the result has value, otherwise return nullopt.
    */
    virtual std::optional<IntersectResult> rayIntersect(const vec3f& orig, const vec3f& d) const = 0;
};

#endif