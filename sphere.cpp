#include "sphere.h"

#include <cmath>

Sphere::Sphere(const vec3f& c, float r)
    :center(c), radius(r){}

Sphere::Sphere(const vec3f& c, float r, const Material& m)
    :center(c), radius(r), material(m) {}

Sphere::~Sphere(){}

bool Sphere::rayIntersect(const vec3f& orig, const vec3f& d, float& t0) const {
    vec3f L = center - orig;
    float tca = L * d;
    float d2 = L * L - tca * tca;
    if(d2 > radius * radius) return false;
    float thc = sqrtf(radius * radius - d2);
    t0 = tca - thc;
    float t1 = tca + thc;
    if(t0 < 0) t0 = t1;
    if(t0 < 0)  return false;
    return true;
}