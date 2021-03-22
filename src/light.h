#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "geometry/geometry.h"

class Light {
private:
    vec3f point;
    float intensity;
public:
    Light(const vec3f& p, const float i);
    ~Light();
    inline vec3f getPoint() const { return point; }
    inline float getIntensity() const { return intensity; }
};

#endif