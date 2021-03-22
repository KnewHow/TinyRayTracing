#ifndef __RAY_H__
#define __RAY_H__

#include "geometry.h"
#include "material/material.h"

/**
 * A result of a ray intersect with a mesh
*/
struct IntersectResult
{
    float t; // the t of the ray o + td intersect with the ray
    vec3f hitPosition; // the hit point the ray intersect with meshs
    Material material; // the material of hitpoints
    vec3f normal; // the normal of the hitpoint
};

/**
 * Define a ray with origin pointer and directory
*/

struct Ray {
    vec3f o;
    vec3f d;
    Ray(const vec3f op, const vec3f directory)
        :o(op), d(directory){}
};

#endif