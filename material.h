#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry.h"

class Material
{
private:
    vec3f diffuse_color;
public:
    Material();
    Material(const vec3f& dc);
    ~Material();
    inline vec3f getDiffuseColor() const { return diffuse_color; }
};


#endif