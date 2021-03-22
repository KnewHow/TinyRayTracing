#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <array>

#include "primitive.h"


class Triangle: public Primitive {
    
private:
    std::array<vec3f,3> verties;
    const Material& material;

public:
    Triangle(const vec3f& v0, const vec3f& v1, const vec3f& v2, const Material& m);
    ~Triangle();
    virtual std::optional<IntersectResult> intersect(const Ray& ray) const override;
};

#endif