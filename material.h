#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry.h"

class Material
{
private:
    vec2f albedo;
    vec3f diffuse_color;
    float specular_exponent;

public:
    Material();
    Material(const vec2f& a, const vec3f& dc, const float se);
    ~Material();
    inline vec3f getDiffuseColor() const { return diffuse_color; }
    inline vec2f getAlbedo() const { return albedo; }
    inline float getSpecularExponent() const { return specular_exponent; }
};


#endif