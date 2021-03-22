#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <string>
#include <memory>

#include "image.h"
#include "mesh/mesh.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "light.h"

class Renderer {
private:
    Image& image;
    const Image& env;
    const float fov;
    int ray_trace_times;

    /**
     * calculate the reflect ray from input I and normal
     * @param I the input ray
     * @param normal the normal of current ray hit the surface
     * @return the reflect ray from current ray input and normal
     */ 
    vec3f reflect(const vec3f& I, const vec3f& N);

    /**
     * calculate the refract ray with light, normal and refractive_index, then return the refract ray if refraction happen.
     * @param I the incident ray, it is must unit vector
     * @param N the normal of current plane, it's must unit vector
     * @param refractive_index the refractive_index the ray will enter
     * @return the ray refractive vector in next media.
    */
    vec3f refract(const vec3f& I, const vec3f& N, const float& refractive_index);
    
    
    /**
     * cast ray insersect with secen, and return the color the ray pass the pixel. 
     * In this function, it will calculate the color with lights
     * 
     * @param orig the original point of the ray
     * @param d the directory of the ray
     * @param scene the scene consisted by shpere
     * @param lights the lights of the scene
     * @param depth the depth the ray recursive to search reflection ray, defalut is 0
     * @return if the ray intersect with the scene, return the hit point color, otherwise return the background color 
     * 
    */
    vec3f cast_ray(const vec3f& orig, const vec3f& d, const std::vector<std::shared_ptr<Mesh>>& scene, const std::vector<Light>& lights, std::size_t depth = 0);
    
    /**
     * a ray intersect with a scene, it will return hit infomation with the lastest mesh
     * @param orig the ray original point
     * @param d the ray directory
     * @param mesh the mesh in the scene
     * @param hit the hit the ray hit the mesh
     * @param normal the hit point normal
     * @param material the material of the mesh
     * @return if the ray intersect with the secen, true wull be return, otherwise it will return false
    */
    bool scene_intersect(const vec3f& orig, const vec3f& d, const std::vector<std::shared_ptr<Mesh>>& scene, vec3f& hit, vec3f& normal, Material& material);

public:
    /**
     * construct of renderer
     * @param m the image the render output
     * @param f the field of view 
     * @param lights the lights of the secen
    */
    Renderer(Image& m, const float f, const Image& e);
    ~Renderer();
    void render(const std::vector<std::shared_ptr<Mesh>>& scene, const std::vector<Light>& lights);
    void output(const std::string& filepath);
    void setRayTraceTimes(const int& t);
};

#endif