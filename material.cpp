#include "material.h"

Material::Material()
    :diffuse_color(){}


Material::Material(const vec3f& dc)
    :diffuse_color(dc){}


Material::~Material()
{
}
