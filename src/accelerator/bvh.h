#ifndef __BVH_H__
#define __BVH_H__

#include <memory>
#include <vector>

#include "primitive.h"
#include ""

/**
 * A BVH tree
*/
struct BVHNode
{

    BVHNode* left;
    BVHNode* right;
    std::shared_ptr<Primitive> p;
};


/**
 * A BVH accelerator, refer: http://www.pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies.html#sec:sah
*/
class BVHAccelerator {

private:
    std::vector<std::shared_ptr<Primitive>> primitives;

};


#endif