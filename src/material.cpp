#include "material.h"

Material::Material()
    : albedo(1, 0, 0, 0), diffuse_color(), specular_exponent(), refractive_index(1){}


Material::Material(const vec4f a, const vec3f dc, const float se, const float ri)
    :albedo(a), diffuse_color(dc), specular_exponent(se), refractive_index(ri){}


Material::~Material()
{
}

void Material::setDiffuse(const vec3f& dc) {
    diffuse_color = dc;
}
