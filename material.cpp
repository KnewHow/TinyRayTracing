#include "material.h"

Material::Material()
    :diffuse_color(){}


Material::Material(const vec2f& a, const vec3f& dc, const float se)
    :albedo(a), diffuse_color(dc), specular_exponent(se){}


Material::~Material()
{
}
