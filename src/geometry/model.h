#pragma once

#include <vector>
#include <array>

#include "mesh.h"
#include "AABB.h"


class Model: public Mesh {
private:
    std::string filepath;
    std::vector<vec3f> vertices;
    std::vector<vec3i> faces;
    Material material;
    AABB box;
    /**
     * Calculating ray intersectes with AABB, if they intersect, return ture, otheriwize return false
     * @param orig the original point of the ray
     * @param d the directoy of the the ray
     * @return if they intersect, return true, otherwise return false.
    */
    bool rayIntersectWithAABB(const vec3f& orig, const vec3f& d) const;
    
    /**
     * Calculating ray intersectes with the triangle, if they are interscting, return the t of the ray, otherwise return nullopt.
     * Algorithms refer: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
     * @param orig the original point of the ray
     * @param d the directoy of the the ray
     * @param tri the triangle vertex in an array
     * @return if they intersecting return the t of the ray, otherwise return nullopt
    */
    std::optional<float> rayIntersectWithTriangle(const vec3f& orig, const vec3f& d, const std::array<vec3f, 3>& tri) const;

public:
    Model(const std::string& p, const Material& m);
    ~Model();
    virtual std::optional<IntersectResult> rayIntersect(const vec3f& orig, const vec3f& d) const override;
};