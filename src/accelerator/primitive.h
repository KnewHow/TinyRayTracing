#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <optional>

#include "boundingBox/AABB.h"
#include "geometry/ray.h"

/**
 * A basic geometry primitive intersects with a ray.
*/

class Primitive {
public:
    /**
     * ray insersect with the primative, if they are intersecting, retunrn the intersect result, otherwise return null
     * @param ray A ray with original point and directory
     * @return if they are intersecting, retunrn the intersect result, otherwise return null
    */
    virtual std::optional<IntersectResult> intersect(const Ray& ray) const = 0;
    /**
     * Get AABB of the primitive
    */
    virtual AABB getBounding() const = 0;
};

#endif