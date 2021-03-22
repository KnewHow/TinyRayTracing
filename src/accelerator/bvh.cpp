#include "bvh.h"

#include <algorithm>

BVHAccelerator::BVHAccelerator(const std::vector<std::shared_ptr<Primitive>>& ps)
    : primitives(ps), root(nullptr) {
    root = recursiveBuild(primitives);
}

std::shared_ptr<BVHNode> BVHAccelerator::recursiveBuild(std::vector<std::shared_ptr<Primitive>> ps) {
    AABB bounding;
    for(const std::shared_ptr<Primitive>& p: ps) 
        bounding = bounding.upon(p->getBounding());
    
    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
    if(ps.size() == 1) {
        node->left = node->right = nullptr;
        node->bounding = bounding;
        node->p = ps[0];
    } else if(ps.size() == 2) {
        node->left = recursiveBuild(std::vector<std::shared_ptr<Primitive>>{ps[0]});
        node->right = recursiveBuild(std::vector<std::shared_ptr<Primitive>>{ps[1]});
        node->bounding = node->left->bounding.upon(node->right->bounding);
    } else {
        AABB boundingCentre;
        for(const std::shared_ptr<Primitive>& p: ps) {
            boundingCentre = boundingCentre.upon(p->getBounding().getCentre());
        }
        AABB::AXIS dim = boundingCentre.getExtent();
        switch (dim)
        {
            case AABB::AXIS::X:
                std::sort(ps.begin(), ps.end(), [](std::shared_ptr<Primitive> p1, std::shared_ptr<Primitive> p2){
                    return p1->getBounding().getCentre().x < p2->getBounding().getCentre().x;
                });
                break;
            case AABB::AXIS::Y:
                std::sort(ps.begin(), ps.end(), [](std::shared_ptr<Primitive> p1, std::shared_ptr<Primitive> p2){
                    return p1->getBounding().getCentre().y < p2->getBounding().getCentre().y;
                });
                break;
            case AABB::AXIS::Z:
                std::sort(ps.begin(), ps.end(), [](std::shared_ptr<Primitive> p1, std::shared_ptr<Primitive> p2){
                    return p1->getBounding().getCentre().z < p2->getBounding().getCentre().z;
                });
                break;
        }
        auto begin = ps.begin();
        auto middle = ps.begin() + (ps.size() / 2);
        auto end = ps.end();
        auto subLeft = std::vector<std::shared_ptr<Primitive>>(begin, middle);
        auto subRight = std::vector<std::shared_ptr<Primitive>>(middle, end);

        node->left = recursiveBuild(subLeft);
        node->right = recursiveBuild(subRight);
        node->bounding = node->left->bounding.upon(node->right->bounding);
    }

    return node;
}

std::optional<IntersectResult> BVHAccelerator::intersect(const Ray& ray) {
    if(root == nullptr) {
        return std::nullopt;
    } else {
        return intersectRecursive(ray, root);
    }
}

std::optional<IntersectResult> BVHAccelerator::intersectRecursive(const Ray& ray, std::shared_ptr<BVHNode> r) {
    if(r == nullptr) {
        return std::nullopt;
    } else if(r->bounding.intersect(ray)) {
        if(r->left == nullptr && r->right == nullptr) {
            return r->p->intersect(ray);
        } else {
            auto leftR = intersectRecursive(ray, r->left);
            auto rightR = intersectRecursive(ray, r->right); 
            if(leftR.has_value() && rightR.has_value()) {
                return leftR.value().t < rightR.value().t ? leftR : rightR;
            } else if(leftR.has_value()) {
                return leftR;
            } else if(rightR.has_value()) {
                return rightR;
            }
        }
    }
    return std::nullopt;


}