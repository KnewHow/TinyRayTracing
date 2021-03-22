#ifndef __SPHERE_H__
#define __SHPERE_H__

#include "geometry/geometry.h"
#include "material/material.h"
#include "mesh.h"


class Sphere: public Mesh {

private:
    vec3f center;
    float radius;
    Material material;

public:
    Sphere(const vec3f& c, float r);
    Sphere(const vec3f& c, float r, const Material& m);
    ~Sphere();

   
    std::optional<IntersectResult> rayIntersect(const vec3f& orig, const vec3f& d) const override;
    inline vec3f getCenter() const { return center; }
    inline float getRadius() const { return radius; }
    inline Material getMaterial() const { return material; }
};

#endif