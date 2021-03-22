#include "triangle.h"

Triangle::Triangle(const vec3f& v0, const vec3f& v1, const vec3f& v2, const Material& m)
    :material(m) 
{
    verties[0] = v0;
    verties[1] = v1;
    verties[2] = v2;
}

 Triangle::~Triangle() {}

std::optional<IntersectResult> Triangle::intersect(const Ray& ray) const {
    vec3f E1 = verties[1] - verties[0];
    vec3f E2 = verties[2] - verties[0];
    vec3f S = ray.o - verties[0];
    vec3f S1 = cross(ray.d, E2);
    vec3f S2 = cross(S, E1);
    vec3f v = vec3f(S2 * E2, S1 * S, S2 * ray.d);
    vec3f r = 1 / (S1 * E1) * v;
    if(r.x > 0 && r.y > 0 && r.z > 0 && (1 - r.y - r.z) > 0) {
        vec3f hitPoint = ray.o + r.x * ray.d;
        vec3f normal = cross(E1, E2).normalize();
        return IntersectResult{r.x, hitPoint, material, normal};
    } else {
        return std::nullopt;
    }
}

AABB Triangle::getBounding() const {
    AABB b;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            b.min[j] = std::min(b.min[j], verties[i][j]);
            b.max[j] = std::max(b.max[j], verties[i][j]);
        }
    }
    return b;
}