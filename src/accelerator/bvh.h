#ifndef __BVH_H__
#define __BVH_H__

#include <memory>
#include <vector>
#include <optional>

#include "primitive.h"
#include "boundingBox/AABB.h"

/**
 * A BVH tree
*/
struct BVHNode
{
    BVHNode() {
        bounding = AABB();
        left = nullptr;
        right = nullptr;
        p = nullptr;
    }
    ~BVHNode() {

    }
    AABB bounding;
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    std::shared_ptr<Primitive> p;
};


/**
 * A BVH accelerator, refer: http://www.pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies.html#sec:sah
*/
class BVHAccelerator {

    BVHAccelerator(const std::vector<std::shared_ptr<Primitive>>& ps);
    ~BVHAccelerator();
    std::optional<IntersectResult> intersect(const Ray& ray);
private:
    std::shared_ptr<BVHNode> recursiveBuild(std::vector<std::shared_ptr<Primitive>> ps);
    std::optional<IntersectResult> intersectRecursive(const Ray& ray, std::shared_ptr<BVHNode> r);
    const std::vector<std::shared_ptr<Primitive>>& primitives;
    std::shared_ptr<BVHNode> root;
};


#endif