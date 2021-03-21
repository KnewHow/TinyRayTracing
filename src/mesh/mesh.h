#ifndef __MESH_H__
#define __MESH_H__

#include <optional>

#include "../geometry.h"
#include "../material.h"

/**
 * A result of a ray intersect with a mesh
*/
struct IntersectResult
{
    float t; // the t of the ray o + td intersect with the ray
    vec3f hitPosition; // the hit point the ray intersect with meshs
    Material material; // the material of hitpoints
    vec3f normal; // the normal of the hitpoint
};

struct AABB // define the Axis-aligned-bounding-box
{
    vec3f min;
    vec3f max;
};


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