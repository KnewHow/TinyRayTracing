#pragma once

#include <vector>
#include <array>

#include "mesh.h"
#include "boundingBox/AABB.h"
#include "accelerator/bvh.h"


class Model: public Mesh {
private:
    std::string filepath;
    std::vector<vec3f> vertices;
    std::vector<vec3i> faces;
    Material material;
    AABB box;
    std::shared_ptr<BVHAccelerator> bvh;

    /**
     * Calculating ray intersectes with the triangle, if they are interscting, return the t of the ray, otherwise return nullopt.
     * Algorithms refer: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
     * @param tay the ray contains original point and directory
     * @param tri the triangle vertex in an array
     * @return if they intersecting return the t of the ray, otherwise return nullopt
    */
    std::optional<float> rayIntersectWithTriangle(const Ray& ray, const std::array<vec3f, 3>& tri) const;
    std::optional<IntersectResult> rayIntersectOld(const Ray& ray) const;
    void constructBVH();
public:
    Model(const std::string& p, const Material& m);
    ~Model();
    virtual std::optional<IntersectResult> rayIntersect(const Ray& ray) const override;
};