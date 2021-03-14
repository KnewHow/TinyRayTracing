#include "material.h"

Material::Material()
    :diffuse_color(){}


Material::Material(const vec4f a, const vec3f dc, const float se, const float ri)
    :albedo(a), diffuse_color(dc), specular_exponent(se), refractive_index(ri){}


Material::~Material()
{
}
