#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry.h"

class Material
{
private:
    vec4f albedo;
    vec3f diffuse_color;
    float specular_exponent;
    float refractive_index;

public:
    Material();
    Material(const vec4f a, const vec3f dc, const float se, const float ri);
    ~Material();
    inline vec3f getDiffuseColor() const { return diffuse_color; }
    inline vec4f getAlbedo() const { return albedo; }
    inline float getSpecularExponent() const { return specular_exponent; }
    inline float getRefractiveIndex() const { return refractive_index; }
};


#endif