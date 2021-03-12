#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <string>

#include "image.h"
#include "sphere.h"
#include "geometry.h"
#include "light.h"

class Renderer {
private:
    Image& image;
    const float fov;

    /**
     * cast ray insersect with secen, and return the color the ray pass the pixel. 
     * In this function, it will calculate the color with lights
     * 
     * @param orig the original point of the ray
     * @param d the directory of the ray
     * @param scene the scene consisted by shpere
     * @param lights the lights of the scene
     * @return if the ray intersect with the scene, return the hit point color, otherwise return the background color 
    */
    vec3f cast_ray(const vec3f& orig, const vec3f& d, const std::vector<Sphere>& scene, const std::vector<Light>& lights);
    
    /**
     * a ray intersect with a scene, it will return hit infomation with the lastest sphere
     * @param orig the ray original point
     * @param d the ray directory
     * @param spheres the spheres in the scene
     * @param hit the hit the ray hit the sphere
     * @param normal the hit point normal
     * @param material the material of the sphere
     * @return if the ray intersect with the secen, true wull be return, otherwise it will return false
    */
    bool scene_intersect(const vec3f& orig, const vec3f& d, const std::vector<Sphere>& spheres, vec3f& hit, vec3f& normal, Material& material);

public:
    /**
     * construct of renderer
     * @param m the image the render output
     * @param f the field of view 
     * @param lights the lights of the secen
    */
    Renderer(Image& m, const float f);
    ~Renderer();
    void render(const std::vector<Sphere>& sphere, const std::vector<Light>& lights);
    void output(const std::string& filepath);
};

#endif