#ifndef __SPHERE_H__
#define __SHPERE_H__

#include "geometry.h"
#include "material.h"



class Sphere {

private:
    vec3f center;
    float radius;
    Material material;

public:
    Sphere(const vec3f& c, float r);
    Sphere(const vec3f& c, float r, const Material& m);
    ~Sphere();

    /**
     * a ray intersect with the sphere
     * @param orig the ray original point 
     * @param d the directory of the ray
     * @param t0 the first intersect point the ray with the sphere, if they are intersected.
     * @return if they are intersected return true, otherwise return false
    */
    bool rayIntersect(const vec3f& orig, const vec3f& d, float& t0) const;
    inline vec3f getCenter() const { return center; }
    inline float getRadius() const { return radius; }
    inline Material getMaterial() const { return material; }
};

#endif