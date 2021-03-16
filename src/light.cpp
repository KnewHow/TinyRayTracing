#include "light.h"

Light::Light(const vec3f& p, const float i)
    :point(p), intensity(i){}

Light::~Light(){}