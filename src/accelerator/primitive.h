#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <optional>
#include "geometry/ray.h"

/**
 * A basic geometry primitive intersects with a ray.
*/

class Primitive {
    /**
     * ray 
    */
    virtual std::optional<IntersectResult> intersect(const Ray& ray) const = 0;
};

#endif